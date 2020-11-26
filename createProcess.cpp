//Daniel Kantor, Isaiah Jones & MacKenzie Richards
#include <iostream>
#include <random>
#include <queue>
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
    queue <node> q; // queue for FIFO scheduling
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

    for(int i = 0; i < 40; i++){
        int processID = (i+1);
        cout << "Process ID " << processID << "\n";
        long long serviceTime = values1(seed);
        cout << "Service Time " << serviceTime << "\n";
        int processMem = processMemReq[i];
        cout << "Memory Size " << processMem << "\n";        
        q.push(node(serviceTime, processMem, processID)); //add each process to a queue, making it FIFO scheduling
    }

    
}
