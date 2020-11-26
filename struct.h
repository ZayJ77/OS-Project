//Daniel Kantor, Isaiah Jones & MacKenzie Richards
#ifndef STRUCT_H
#define STRUCT_H

struct node{ //Struct to store the randomly generated serive time and memory size. It also stores the process ID of the process. This struct will be interested into a queue
    node(long long s, int m, int i) : serviceTime(s), memoryReq(m), processID(i){}
    long long serviceTime;
    int memoryReq;
    int processID;
};

#endif