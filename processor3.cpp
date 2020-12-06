//Daniel Kantor & MacKenzie Richards
#include "processor3.h"
#include "struct.h"

data processor3(long speed3, long sTime, int processID, long serviceTime, int memReq){    
    if(sTime > speed3 * 1000000000){//if the service time of the process is greater than 1 billion * speed (simulating speed of CPU which is 1 billion * #GHz) then it subtracts 1 billion * speed
        sTime = sTime - (speed3 * 1000000000);
        return data(speed3, sTime, processID,serviceTime, memReq);//returns the remaining service time left
    }
    else{ //if service time of the process is less than 1 billion * speed then the service time left will be 0, so it returns 0 and the process is done.
        return data(speed3, 0, processID, serviceTime, memReq);

    }
}