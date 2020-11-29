//MacKenzie Richards, Daniel Kantor, Isaiah Jones
//first-fit algorithm implementation
//linked list implementation source - https://www.tutorialspoint.com/cplusplus-program-to-implement-singly-linked-list

#include "freeBlock.h"
#include "allocatedBlock.h"
#include <bits/stdc++.h> 
using namespace std;  

//keeps track of positions of new free memory blocks
int freePositionCounter = 0; 

//creates free memory - starts off with 1 block of size 10MB
void createMemory(int s) 
{ 
	//allocates structure of empty memory blocks of specific size
	struct freeBlock* mem = (struct freeBlock*) malloc(sizeof(struct freeBlock)); 
	mem -> size = s; 
	mem -> freeBlockPosition = freePositionCounter; 
	mem -> next = NULL; 
	
	if (freeBlock_head != NULL) 
		freeBlock_head = mem; //sets head to current node
	else
		prev_freeBlock -> next = mem; //sets previous node's pointer to p
		
	prev_freeBlock = mem; 
	
	freePositionCounter++; //moves position -- new position is set each time a block is made
} 

//keeps track of positions of allocated memory blocks
int mallocPositionCounter = 0; 

//allocates memory to blocks
void my_malloc(int s) 
{ 
	//create the process node 
	struct allocatedBlock* process = (struct allocatedBlock*) malloc(sizeof(struct allocatedBlock)); 
	
	process -> size = s; 
	process -> allocatedBlockPosition = mallocPositionCounter; 
	process -> next = NULL; 

	struct freeBlock* mem = freeBlock_head; //mem is the head of the free list - starts from here

	//iterate through free list
	while (mem != NULL) { 
		if (process -> size <= mem -> size) //if process fits in the memory block...
			break; 
		mem = mem -> next;  
	} 

	//found a block  
	if (mem != NULL) { 
		process -> blockID = mem -> freeBlockPosition; //sets block ID of process to position of block
		mem -> size -= process -> size; //subtracts size of process from memory block
		if (allocatedBlock_head == NULL) 
			allocatedBlock_head = process; //sets head of filled memory blocks to this process
		else { 
			prev_allocatedBlock = allocatedBlock_head; //move pointer to head
			while (prev_allocatedBlock->next != NULL) 
				prev_allocatedBlock = prev_allocatedBlock->next; //traverse through list
			prev_allocatedBlock->next = process; //put allocated process at the end
		} 
		mallocPositionCounter++; //updates position of last allocated memory to match free blocks
	} 
	else 
		cout << s << " size process does not fit!\n"; 
} 

//prints allocated blocks and their block ids 
void printMemory() 
{ 
	struct allocatedBlock* process = allocatedBlock_head; 
	cout << "position \t block # \tsize\n"; 
	while (process != NULL) { 
		cout << process -> allocatedBlockPosition << "\t\t "
			<< process -> blockID << "\t\t"
			<< process -> size << "\t\n"; 
		process = process->next; 
	} 
} 

//deletes node from allocated list, given a position
void my_free(int pos) 
{ 
	struct allocatedBlock *process = allocatedBlock_head, *swap = NULL; 

    //search for process
	while (process != NULL) { 
		if (process -> allocatedBlockPosition == pos)  
			break; 
		swap = process; 
		process = process -> next; 
	} 
	
	//if process is at the head
	if (process == allocatedBlock_head) 
		allocatedBlock_head = allocatedBlock_head -> next; //change head to the next process
	else if (process != NULL) 
		swap -> next = process -> next; //connect previous process to the next process
	else
		cout << "process does not exist\n"; 
		
	struct freeBlock* temp = freeBlock_head;
	
	//add back the memory from the deleted process to the block it was located at
	while (temp != NULL) { 
		if (temp -> freeBlockPosition == process -> blockID) { 
			temp -> size += process -> size; 
			break; 
		} 
		temp = temp -> next; 
	} 
} 

int main() 
{ 
    int blockSize[] = { 100, 500, 200 }; 
    int processSize[] = { 417, 112, 426, 95 }; 
    int m = sizeof(blockSize) 
            / sizeof(blockSize[0]); 
    int n = sizeof(processSize) 
            / sizeof(processSize[0]); 
  
    for (int i = 0; i < m; i++) 
        createMemory(blockSize[i]); 
  
    for (int i = 0; i < n; i++) 
        my_malloc(processSize[i]); 
  
    printMemory(); 
  
    // Block of tag id 0 deleted 
    // to free space for block of size 426 
    my_free(0); 
  
    my_malloc(426); 
    cout << "After deleting block"
         << " with tag id 0.\n"; 
    printMemory(); 
} 