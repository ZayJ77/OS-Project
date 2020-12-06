//Daniel Kantor & MacKenzie Richards
#ifndef PROCESSOR3_H
#define PROCESSOR3_H

#include <unistd.h>
#include <iostream>
#include "struct.h"
using namespace std;

//sets up the imports and returns of processor3 so it can be called from FIFO.cpp and SJF.cpp
data processor3(long speed3, long sTime, int processID, long serviceTime, int memRequire);

#endif