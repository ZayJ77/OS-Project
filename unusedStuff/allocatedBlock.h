//Daniel Kantor, Isaiah Jones & MacKenzie Richards
#ifndef STRUCT_H
#define STRUCT_H

//node of allocated memory block
struct allocatedBlock { 
    int size; 
    int allocatedBlockPosition; 
	int blockID; 
	struct allocatedBlock* next; 
};

//head and prev
struct allocatedBlock* allocatedBlock_head = NULL;
struct allocatedBlock* prev_allocatedBlock = NULL; 

#endif
