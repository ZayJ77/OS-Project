#include <iostream>
#include <random>
#include <queue>
#include <chrono>
#include "struct.h"
using namespace std;

int main(){
    bool runSim = true;
    int choice;
    int *p[10000];
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

    while(runSim != false){
        cout << "What Senario would you like to run? \n";
        cout << "Please enter 1, 2, 3, 4, or 5 to exit \n";
        cin >> choice;


        switch(choice){
        case 1: {
            auto start = chrono::steady_clock::now();


            for(int i = 0; i < 40; i++){
                processMemReq[i] = 1;

            }


            while(p){ //P will never be false but just to get it to run I think
                if(i == 40){
                    i = 0;
                }

                for (int i = 0; i < 10000; i++) {
                    p[i] = (int*)malloc(25000 * sizeof(int));
                    uintptr_t value = (uintptr_t )p;

                    value = values2(seed);
                    processMemReq[i] = processMemReq[i] + value;
                    total = total + value;
                }


                if(total > 10000){
                    break;
                }
                i++;

                for (int i = 0; i < 10000; i++) {
                    free(p[i]);
                }
            }
            auto end = chrono::steady_clock::now();





                while(total > 10000){
                    processMemReq[i] = processMemReq[i] - 1;
                    total = total -1;
                }

                for(int i = 0; i < 40; i++){
                    int processID = (i+1);
                    cout << "Process ID: " << processID << "\n";
                    long long serviceTime = values1(seed);
                    cout << "Service Time: " << serviceTime << "\n";
                    int processMem = processMemReq[i];
                    cout << "Memory Size: " << processMem << "\n\n";
                    q.push(node(serviceTime, processMem, processID)); //add each process to a queue, making it FIFO scheduling

                }
                cout << "Total Memory Utilized: " << total << "\n";
                cout << "Elapsed time in nanoseconds : "
                << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
                << " ns\n\n";
                break;
            }
            case 2:{
                cout << "Coming Soon...\n\n";
                break;
            }

            case 3:{
                cout << "Coming Soon...\n\n";
                break;
            }

            case 4:{
                cout << "Coming Soon...\n\n";
                break;
            }

            case 5:{
                cout << "GoodBye!\n";
                runSim = false;
                break;
            }

        }

    }

}
