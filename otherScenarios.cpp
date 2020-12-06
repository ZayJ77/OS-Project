//Daniel Kantor & MacKenzie Richards
#include "otherScenarios.h"
#include "processor1.h"
#include "processor2.h"
#include "processor3.h"
#include "processor4.h"
#include "struct.h"
#include <fstream>
#include <chrono>

//varibles to keep track if proccesors are full
bool processorFull1Other = false;
bool processorFull2Other = false;
bool processorFull3Other = false;
bool processorFull4Other = false;

//the structs that we pass to the processors so the processes can be worked on
data temp1Other(0,0,0,0,0);
data temp2Other(0,0,0,0,0);
data temp3Other(0,0,0,0,0);
data temp4Other(0,0,0,0,0);

//queues to keep track of data to be output to a file at end of execution
queue<int> IDNumberOther;
queue<long> outputServiceTimeOther;
queue<int> memoryRequirementsOther;

//Queue for processes loaded in memory
queue<node> loadedOther;

int startArray[40]; //array to keep track of where in memory the process starts
int endArray[40]; //array to keep track of where in memory the process end 
int startNumber = -1;
int processesCompleted = 0;

int my_malloc(int memoryBlock[], node temp, int size){//method to malloc the processes
    int memory = temp.memoryReq;
    int consecutive = 0;
    int start = 0;
    bool solution = false;
    if(size < temp.memoryReq){//if the process is too large to ever fit in memory then note it by returning -2
        return -2;
    }
    for(int i = 0; i < size; i++){//iterate through the entire array of memory
        if(memoryBlock[i] == 0){//if the value in the array is 0 then increase the value of consecutive 0's
            consecutive++;
            if(consecutive == 1){// if its the beginning of the count of consecutive this is where the start of the process is put in memory
                start = i;
            }
        }
        else{
            consecutive = 0; //if the value isnt 0 then there is no consecutive memory locations open so reset the value 
        }
        if(consecutive == memory){//if there is enough consecutive 0's in memory to equal the size of the process then you found the solution
            solution = true;
            break;
        }
    }
    if(solution == true){
        loadedOther.push(temp);// load the process into memory
        for(int i = start; i < start + memory; i++){//change all the values from the start of memory to the end of the process to 1 to indicate those memory slots are taken
            memoryBlock[i] = 1;
        }
        return start;
    }
    else{
        return -100; // if no memory slots are found indicate it by returning -100
    }
}
void my_free(int memoryBlock[], int start, data temp){// method to to free the processes
    int memory = temp.memReq;
    for(int i = start; i < start + memory; i++){//when freeing the process start from where the process begins in memory until where the process ends in memory and change the values back to 0 
        memoryBlock[i] = 0;                     // to indicate that the slots are open
    }
}

queue<node> try_malloc(int memoryBlock[], queue<node> processes, int size){
    while(startNumber != -100){ // while you can find memory slots for processes
        while(processes.empty() == false){ // while the processes queue isn't empty
            node temp = processes.front();
            startNumber = my_malloc(memoryBlock, temp, size);// try to malloc the process
            if(startNumber != -100){//if you find memory for the process store its start value and end value and remove the process from the waiting processes queue
                startArray[temp.processID-1] = startNumber;
                endArray[temp.processID-1] = startNumber + temp.memoryReq;
                processes.pop();
            }
            if(processes.empty() == true){//if the queue is empty set start equal to -100 to exit while loop
                startNumber = -100;
            }
            if(startNumber == -100){//if you can't find a slot in memory for the process then break out of the loop
                break;
            }
        }
    }
    startNumber = -1;//reset the value of startNumber for next time and return the waiting queue
    return processes;
}

void otherScenarios(queue<node> processes, long speed, int size, int scenario){
    int memoryBlock[size];//create an array the size of the memory block
    for(int i = 0; i < size; i++){ //Initialize the memory block to start empty (0 = empty, 1 = full)
        memoryBlock[i] = 0; 
    }
    processes = try_malloc(memoryBlock, processes, size); // malloc all the processes possible

    auto start = chrono::steady_clock::now(); // start the clock
    while(processesCompleted < 40){//while you haven't finished all the proccesses keep going
        if(processorFull1Other == true){
            if(temp1Other.remainingServiceTime > 0){//if there is still time on the process keep running it 
                temp1Other = processor1(speed, temp1Other.remainingServiceTime, temp1Other.processID, temp1Other.serviceTime, temp1Other.memReq);
            }
            else{
                int start = startArray[temp1Other.processID-1];
                my_free(memoryBlock, start, temp1Other);//free the process when done
                processesCompleted++;
                processorFull1Other = false;//signal process is done
            }
        }
        else{
            if(!processes.empty()){//check if processes is empty and if it isn't try mallocing after a process is freed
                processes = try_malloc(memoryBlock, processes, size);
            }
            if(!loadedOther.empty()){//code needed to put a process onto a processor to run
                node temp = loadedOther.front();
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                int memRequire = temp.memoryReq;
                IDNumberOther.push(ID);
                outputServiceTimeOther.push(processServiceTime);
                memoryRequirementsOther.push(memRequire);
                loadedOther.pop();
                processorFull1Other = true;//signal that the processor is now running a process
                temp1Other = processor1(0, processServiceTime, ID, processServiceTime, memRequire); 
            }
        }
        if(processorFull2Other == true){
            if(temp2Other.remainingServiceTime > 0){//if there is still time on the process keep running it 
                temp2Other = processor2(speed, temp2Other.remainingServiceTime, temp2Other.processID, temp2Other.serviceTime, temp2Other.memReq);
            }
            else{
                int start = startArray[temp2Other.processID-1];
                my_free(memoryBlock, start, temp2Other);//free process when done            
                processesCompleted++;
                processorFull2Other = false;//signal process is done
            }
        }
        else{
            if(!processes.empty()){//check if processes is empty and if it isn't try mallocing after a process is freed
                processes = try_malloc(memoryBlock, processes, size);
            }
            if(!loadedOther.empty()){//code needed to put a process onto a processor to run
                node temp = loadedOther.front();
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                int memRequire = temp.memoryReq;
                IDNumberOther.push(ID);
                outputServiceTimeOther.push(processServiceTime);
                memoryRequirementsOther.push(memRequire);
                loadedOther.pop();
                processorFull2Other = true;//signal that the processor is now running a process
                temp2Other = processor2(0, processServiceTime, ID, processServiceTime, memRequire); 
            }
        }
        if(processorFull3Other == true){
            if(temp3Other.remainingServiceTime > 0){//if there is still time on the process keep running it 
                temp3Other = processor3(speed, temp3Other.remainingServiceTime, temp3Other.processID, temp3Other.serviceTime, temp3Other.memReq);
            }
            else{
                int start = startArray[temp3Other.processID-1];
                my_free(memoryBlock, start, temp3Other);//free process when done      
                processesCompleted++;
                processorFull3Other = false;//signal process is done
            }
        }
        else{
            if(!processes.empty()){//check if processes is empty and if it isn't try mallocing after a process is freed
                processes = try_malloc(memoryBlock, processes, size);
            }
            if(!loadedOther.empty()){//code needed to put a process onto a processor to run
                node temp = loadedOther.front();
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                int memRequire = temp.memoryReq;
                IDNumberOther.push(ID);
                outputServiceTimeOther.push(processServiceTime);
                memoryRequirementsOther.push(memRequire);
                loadedOther.pop();
                processorFull3Other = true;//signal that the processor is now running a process
                temp3Other = processor3(0, processServiceTime, ID, processServiceTime, memRequire); 
            }
        }
        if(processorFull4Other == true){
            if(temp4Other.remainingServiceTime > 0){//if there is still time on the process keep running it 
                temp4Other = processor4(speed, temp4Other.remainingServiceTime, temp4Other.processID, temp4Other.serviceTime, temp4Other.memReq);
            }
            else{
                int start = startArray[temp4Other.processID-1];
                my_free(memoryBlock, start, temp4Other);//free process when done            
                processesCompleted++;
                processorFull4Other = false;//signal process is done
            }
        }
        else{
            if(!processes.empty()){//check if processes is empty and if it isn't try mallocing after a process is freed
                processes = try_malloc(memoryBlock, processes, size);
            }
            if(!loadedOther.empty()){//code needed to put a process onto a processor to run
                node temp = loadedOther.front();
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                int memRequire = temp.memoryReq;
                IDNumberOther.push(ID);
                outputServiceTimeOther.push(processServiceTime);
                memoryRequirementsOther.push(memRequire);
                loadedOther.pop();
                processorFull4Other = true;//signal that the processor is now running a process
                temp4Other = processor4(0, processServiceTime, ID, processServiceTime, memRequire); 
            }
        }
    }

    auto end = chrono::steady_clock::now(); // end clock
    
    //The code used to output all the data collected to a file 
    if(scenario == 2){
        ofstream results("scenario2Results.txt");
        results << "Total time to compute in nanoseconds: " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << endl;
        int i = 0;
        long long totalServiceTime = 0;

        while(i < 40){
            totalServiceTime = totalServiceTime + outputServiceTimeOther.front();
            results << "\n";
            results << "ID Number: " << IDNumberOther.front() << "\n";
            results << "Service Time: " << outputServiceTimeOther.front() << " cycles\n";
            results << "Memory Requirements: " << memoryRequirementsOther.front() << "KB \n";
            if(startArray[i] == -2){
                results << "Memory Requirements greater than system total memory" << endl;
            }
            else{
                results << "Array Index's Located (Memory Location): " << startArray[i] << " - " << endArray[i] -1 << endl;
            }
            IDNumberOther.pop();
            outputServiceTimeOther.pop();
            memoryRequirementsOther.pop();
            i++;
        }

        long long averageServiceTime = totalServiceTime/40;
        results << endl <<  "Average Service Time: " << averageServiceTime << endl;

        results.close();

        processesCompleted = 0; // reset the value of processes completed back to the for when the file is run again
    }
    if(scenario == 3){
        ofstream results("scenario3Results.txt");
        results << "Total time to compute in nanoseconds: " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << endl;
        int i = 0;
        long long totalServiceTime = 0;

        while(i < 40){
            totalServiceTime = totalServiceTime + outputServiceTimeOther.front();
            results << "\n";
            results << "ID Number: " << IDNumberOther.front() << "\n";
            results << "Service Time: " << outputServiceTimeOther.front() << " cycles\n";
            results << "Memory Requirements: " << memoryRequirementsOther.front() << "KB \n";
            if(startArray[i] == -2){
                results << "Memory Requirements greater than system total memory" << endl;
            }
            else{
                results << "Array Index's Located (Memory Location): " << startArray[i] << " - " << endArray[i] -1 << endl;
            }
            IDNumberOther.pop();
            outputServiceTimeOther.pop();
            memoryRequirementsOther.pop();
            i++;
        }

        long long averageServiceTime = totalServiceTime/40;
        results << endl <<  "Average Service Time: " << averageServiceTime << endl;

        results.close();

        processesCompleted = 0; // reset the value of processes completed back to the for when the file is run again

    }
    if(scenario == 4){
        ofstream results("scenario4Results.txt");
        results << "Total time to compute in nanoseconds: " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << endl;
        int i = 0;
        long long totalServiceTime = 0;

        while(i < 40){
            totalServiceTime = totalServiceTime + outputServiceTimeOther.front();
            results << "\n";
            results << "ID Number: " << IDNumberOther.front() << "\n";
            results << "Service Time: " << outputServiceTimeOther.front() << " cycles\n";
            results << "Memory Requirements: " << memoryRequirementsOther.front() << "KB \n";
            if(startArray[i] == -2){
                results << "Memory Requirements greater than system total memory" << endl;
            }
            else{
                results << "Array Index's Located (Memory Location): " << startArray[i] << " - " << endArray[i] -1 << endl;
            }
            IDNumberOther.pop();
            outputServiceTimeOther.pop();
            memoryRequirementsOther.pop();
            i++;
        }

        long long averageServiceTime = totalServiceTime/40;
        results << endl <<  "Average Service Time: " << averageServiceTime << endl;

        results.close();

        processesCompleted = 0; // reset the value of processes completed back to the for when the file is run again

    }
}


