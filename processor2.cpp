//Daniel Kantor & MacKenzie Richards
#include "processor2.h"
#include "struct.h"

data processor2(long speed2, long sTime, int processID, long serviceTime, int memReq){    
    if(sTime > speed2 * 1000000000){//if the service time of the process is greater than 1 billion * speed (simulating speed of CPU which is 1 billion * #GHz) then it subtracts 1 billion * speed
        sTime = sTime - (speed2 * 1000000000);
        return data(speed2, sTime, processID, serviceTime, memReq);//returns the remaining service time left
    }
    else{//if service time of the process is less than 1 billion * speed then the service time left will be 0, so it returns 0 and the process is done.
        return data(speed2, 0, processID, serviceTime, memReq);
    }
}