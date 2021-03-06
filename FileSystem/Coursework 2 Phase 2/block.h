#ifndef __BLOCK_H
#define __BLOCK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "pool.h"

Block* allocate(Pool* pool, int size);
void write(Block* block, void *object, int objectSize, int offsetInBlock);
void* read(Block* block, int objectSize, int offsetInBlock);
void deallocate(Block* block);

#endif