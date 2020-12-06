//Daniel Kantor & MacKenzie Richards
#ifndef STRUCT_H
#define STRUCT_H

struct node{ //Struct to store the randomly generated serive time and memory size. It also stores the process ID of the process. This struct will be interested into a queue
    node(long long s, int m, int i) : serviceTime(s), memoryReq(m), processID(i){}
    long long serviceTime;
    int memoryReq;
    int processID;
};

struct data{ //Struct to store the data that the processors return after execution
    data(long sp, long r, int p, long se, int mem) : speed(sp), remainingServiceTime(r), processID(p), serviceTime(se), memReq(mem){}
    long speed;
    long remainingServiceTime;
    long processID;
    long serviceTime;
    int memReq;
};


#endif