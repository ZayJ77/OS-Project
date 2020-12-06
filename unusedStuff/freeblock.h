//Daniel Kantor, Isaiah Jones & MacKenzie Richards

#ifndef STRUCT_H
#define STRUCT_H

//node of free memory block
struct freeBlock { 
    int size; //size of memory
	int freeBlockPosition; //position in memory
	struct freeBlock* next; 
};

//head and prev
struct freeBlock* freeBlock_head = NULL;
struct freeBlock* prev_freeBlock = NULL; 

#endif
