//Daniel Kantor, Isaiah Jones & MacKenzie Richards
#include <iostream>
#include <random>
using namespace std;

int main(){ 
    long long seedValue;
    cout << "What seed value do you want to use? \n";
    cin >> seedValue;

    mt19937_64 seed(seedValue); //Gets the seed value used for random number generation
    //Sets the distributions of values to be randomly generated
    uniform_int_distribution<long long> values1(1000000,1000000000000);
    uniform_int_distribution<int> values2(0, 9960);
    int secondBound = 9960;
    int total = 0;
    for (int i = 0; i < 40; i++) {
        long long serviceTime = values1(seed);
        int memoryReq = values2(seed) + 1;
        total = total + memoryReq;
        int processID = (i+1);
        values2 = uniform_int_distribution<int>(0, secondBound - memoryReq + 1); //update bound for next process to be generated from
        secondBound = secondBound - memoryReq + 1; 
        cout << "Process ID: " << processID << "\n" << "Service Time: " << serviceTime << "\n" << "Memory Requirements: " << memoryReq << "\n" << "\n";
    }
    cout << "Total Memory: " << total << "\n";
}
