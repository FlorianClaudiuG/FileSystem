#ifndef __STRUCTS_H
#define __STRUCTS_H

typedef struct _BLOCK Block;
typedef struct _POOL Pool;

struct _POOL
{
	int size;
	void* memory;
	Block* allocated;
	Block* notAllocated;
};

struct _BLOCK
{
	int size;
	int offset;
	Pool* parentPool;
	Block* next;
	//Determines whether the block is part of the allocated list.
	int isAllocated;
};
#endif