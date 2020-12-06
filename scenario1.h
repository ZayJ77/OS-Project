//Daniel Kantor & MacKenzie Richards
#ifndef SCENARIO1_H
#define SCENARIO1_H

#include <queue>
#include <iostream>
#include "struct.h"
using namespace std;

//Sets up the imports for FIFO so it can be called from createProcess.cpp
void scenario1(queue<node> processes, long speed);

#endif