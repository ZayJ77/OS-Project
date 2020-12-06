//Daniel Kantor & MacKenzie Richards
#ifndef OTHERSCENARIOS_H
#define OTHERSCENARIOS_H

#include <queue>
#include <iostream>
#include "struct.h"
using namespace std;

//Sets up the imports for otherScenarios.cpp so it can be called from createProcess.cpp
void otherScenarios(queue<node> processes, long speed, int size, int scenario);

#endif