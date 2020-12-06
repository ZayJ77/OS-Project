//Daniel Kantor & MacKenzie Richards
#ifndef PROCESSOR1_H
#define PROCESSOR1_H

#include <unistd.h>
#include <iostream>
#include "struct.h"
using namespace std;

//sets up the imports and returns of processor1 so it can be called from FIFO.cpp and SJF.cpp
data processor1(long speed1, long sTime, int processID, long serviceTime, int memRequire);

#endif