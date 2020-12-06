//Daniel Kantor & MacKenzie Richards
#include "scenario1.h"
#include "processor1.h"
#include "processor2.h"
#include "processor3.h"
#include "processor4.h"
#include "struct.h"
#include <fstream>
#include <chrono>

//varibles to keep track if proccesors are full
bool processorFull1 = false;
bool processorFull2 = false;
bool processorFull3 = false;
bool processorFull4 = false;
//variables to keep track if the last four processes in the system are completed, to keep track of turnaround time
bool finish1 = false;
bool finish2 = false;
bool finish3 = false;
bool finish4 = false;
//the structs that we pass to the processors so the processes can be worked on
data temp1(0,0,0,0,0);
data temp2(0,0,0,0,0);
data temp3(0,0,0,0,0);
data temp4(0,0,0,0,0);

//queues to keep track of data to be output to a file at end of execution
queue<int> IDNumber;
queue<long> outputServiceTime;
queue<int> memoryRequirements;


queue<node> loaded;
int i = 0; // variable to keep track of which process to free
int completedProcess = 0;
void scenario1(queue<node> processes, long speed){
    auto start = chrono::steady_clock::now(); // start the clock
    int *ptr[40];
    for(int i = 0; i < 40; i++){
        node temp = processes.front();
        int memSize = temp.memoryReq; //get the memory requirments of the process
        int *memPtr = (int*)malloc(memSize*1000);  // allocate memory for the process 
        ptr[i] = memPtr;
        loaded.push(temp); // indicate the process is loaded into memory
        processes.pop();
    }
    while(completedProcess != 40){//will continue running while one these queues have something in them
        if(processorFull1 == true){
            if(temp1.remainingServiceTime > 0){
                temp1 = processor1(speed, temp1.remainingServiceTime, temp1.processID, temp1.serviceTime, temp1.memReq);
            }
            else{
                free(ptr[i]);
                i = i +1;
                completedProcess++;
                processorFull1 = false;//signal process is done
            }
        }
        else{
            if(!loaded.empty()){
                node temp = loaded.front();
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                int memRequire = temp.memoryReq;
                IDNumber.push(ID);
                outputServiceTime.push(processServiceTime);
                memoryRequirements.push(memRequire);
                loaded.pop();
                processorFull1 = true;//signal that the processor is now running a process
                temp1 = processor1(0, processServiceTime, ID, processServiceTime, memRequire); 
            }
        }
        if(processorFull2 == true){
            if(temp2.remainingServiceTime > 0){
                temp2 = processor2(speed, temp2.remainingServiceTime, temp2.processID, temp2.serviceTime, temp2.memReq);
            }
            else{
                free(ptr[i]);
                i = i +1;           
                completedProcess++;
                processorFull2 = false;//signal process is done
            }
        }
        else{
            if(!loaded.empty()){
                node temp = loaded.front();
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                int memRequire = temp.memoryReq;
                IDNumber.push(ID);
                outputServiceTime.push(processServiceTime);
                memoryRequirements.push(memRequire);
                loaded.pop();
                processorFull2 = true;//signal that the processor is now running a process
                temp2 = processor2(0, processServiceTime, ID, processServiceTime, memRequire); 
            }
        }
        if(processorFull3 == true){
            if(temp3.remainingServiceTime > 0){
                temp3 = processor3(speed, temp3.remainingServiceTime, temp3.processID, temp3.serviceTime, temp3.memReq);
            }
            else{
                free(ptr[i]);
                i = i +1;         
                completedProcess++;
                processorFull3 = false;//signal process is done
            }
        }
        else{
            if(!loaded.empty()){
                node temp = loaded.front();
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                int memRequire = temp.memoryReq;
                IDNumber.push(ID);
                outputServiceTime.push(processServiceTime);
                memoryRequirements.push(memRequire);
                loaded.pop();
                processorFull3 = true;//signal that the processor is now running a process
                temp3 = processor3(0, processServiceTime, ID, processServiceTime, memRequire); 
            }
        }
        if(processorFull4 == true){
            if(temp4.remainingServiceTime > 0){
                temp4 = processor4(speed, temp4.remainingServiceTime, temp4.processID, temp4.serviceTime, temp4.memReq);
            }
            else{
                free(ptr[i]);
                i = i +1;          
                completedProcess++;
                processorFull4 = false;//signal process is done
            }
        }
        else{
            if(!loaded.empty()){
                node temp = loaded.front();
                long processServiceTime = temp.serviceTime;
                int ID = temp.processID;
                int memRequire = temp.memoryReq;
                IDNumber.push(ID);
                outputServiceTime.push(processServiceTime);
                memoryRequirements.push(memRequire);
                loaded.pop();
                processorFull4 = true;//signal that the processor is now running a process
                temp4 = processor4(0, processServiceTime, ID, processServiceTime, memRequire); 
            }
        }
    }

    auto end = chrono::steady_clock::now(); // end clock

    
    //The code used to output all the data collected to a file called scenario1.txt
    ofstream results("scenario1Results.txt");
    long long totalServiceTime = 0;
    results << "Total time to compute in nanoseconds: " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << endl;
    int i = 0;
    while(i < 40){
        results << "\n";
        results << "ID Number: " << IDNumber.front() << "\n";
        results << "Service Time: " << outputServiceTime.front() << " cycles\n";
        results << "Memory Requirements: " << memoryRequirements.front() << "KB \n";
        IDNumber.pop();
        outputServiceTime.pop();
        memoryRequirements.pop();
        i++;
    }

    long long averageServiceTime = totalServiceTime/40;
    results << endl <<  "Average Service Time: " << averageServiceTime << endl;

    results.close();

}




