//Isaiah Jones & MacKenzie Richards
#include <iostream>
#include "otherScenarios.h"
#include <random>
#include <queue>
#include "scenario1.h"
#include "struct.h"

using namespace std;

int main(){ 
    long long seedValue;
    cout << "What seed value do you want to use? \n";
    cin >> seedValue;
    mt19937_64 seed(seedValue); //Gets the seed value used for random number generation
    //Sets the distributions of values to be randomly generated
    uniform_int_distribution<long long> values1(1000000,1000000000000);
    uniform_int_distribution<int> values2(0, 249);
    queue <node> q1; // queue for FIFO scheduling scenario1
    queue <node> q2; // queue for FIFO scheduling scenario2
    queue <node> q3; // queue for FIFO scheduling scenario3
    queue <node> q4; // queue for FIFO scheduling scenario4

    int total = 40; // baseline memory used is 40
    int i = 0;
    int processMemReq[40];//array to store process memory requirements

    for(int i = 0; i < 40; i++){
        processMemReq[i] = 1; // initialize all the values of to be at least 1
    }
    while(total != 10000){//run until total memory is 10,000
        if(i == 40){// if you go through all the processes and not 10,000 - restart at beginning
            i = 0;
        }
        int value = values2(seed);
        processMemReq[i] = processMemReq[i] + value;
        total = total + value;
        
        if(total > 10000){// if it gets greater than 10,000 break out of the loop
            break;
        } 
        i++;
    }
    while(total > 10000){//subtract one from the last accessed process memory requirements until the total memory is 10,000
        processMemReq[i] = processMemReq[i] - 1;
        total = total -1;
    }
    
    for(int i = 0; i < 40; i++){ //put values of each process into a node which is stored in a queue
        int processID = (i+1);
        long long serviceTime = values1(seed);
        int processMem = processMemReq[i];
        q1.push(node(serviceTime, processMem, processID)); //add each process to a queue, making it FIFO scheduling
        q2.push(node(serviceTime, processMem, processID)); //add each process to a queue, making it FIFO scheduling
        q3.push(node(serviceTime, processMem, processID)); //add each process to a queue, making it FIFO scheduling
        q4.push(node(serviceTime, processMem, processID)); //add each process to a queue, making it FIFO scheduling
    }
    scenario1(q1,3);
    
    otherScenarios(q2,3,10000,2);

    otherScenarios(q3,3,5000,3);

    otherScenarios(q4,3,1000,4);

    cout << "Processing Done - Check result files for the results" << endl;
}
