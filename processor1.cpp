//Daniel Kantor & MacKenzie Richards
#include "processor1.h"
#include "struct.h"

data processor1(long speed1, long sTime, int processID, long serviceTime, int memReq){    
    if(sTime > speed1 * 1000000000){//if the service time of the process is greater than 1 billion * speed (simulating speed of CPU which is 1 billion * #GHz) then it subtracts 1 billion * speed
        sTime = sTime - (speed1 * 1000000000);
        return data(speed1, sTime, processID, serviceTime, memReq); //returns the remaining service time left
    }
    else{//if service time of the process is less than 1 billion * speed then the service time left will be 0, so it returns 0 and the process is done.
        return data(speed1, 0, processID, serviceTime, memReq);
    }
}     
