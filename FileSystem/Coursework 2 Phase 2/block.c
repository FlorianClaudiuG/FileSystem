#include "block.h"
//
//	The program holds one big block of unallocated memory within the pool that then splits
//	into several allocated blocks. The allocated blocks are then saved as a linked list.
//
Block* allocate(Pool* pool, int size)
{
	//Each pool contains a notAllocated block that represents the free space inside the pool.
	if (size <= 0 || pool->notAllocated->size < size)
	{
		return NULL;
	}

	Block* thisBlock = pool->notAllocated;

	if (thisBlock != NULL)
	{
		//Create a new block.
		Block* newBlock = (Block*)malloc(sizeof(Block));
		newBlock->offset = 0;
		newBlock->size = size;
		newBlock->parentPool = pool;

		//Add it to the allocated blocks list.
		newBlock->next = pool->allocated;
		pool->allocated = newBlock;
		
		//Adjust the bigger block's size.
		thisBlock->size = thisBlock->size - size;

		newBlock->isAllocated = 1;

		return newBlock;
	}
	return NULL;
}

void write(Block* block, void *object, int objectSize, int offsetInBlock)
{
	if (block && offsetInBlock >= 0 && (offsetInBlock + objectSize < block->size))
	{
		memcpy((char*)block->parentPool->memory + block->offset + offsetInBlock, object, objectSize);
	}
}

void* read(Block* block, int objectSize, int offsetInBlock)
{
	if (block == NULL || offsetInBlock < 0 || (offsetInBlock + objectSize > block->size))
	{
		return NULL;
	}
	else
	{
		return (char*)block->parentPool->memory + block->offset + offsetInBlock;
	}
}

void deallocate(Block* block)
{
	if (block != NULL)
	{
		if (block->isAllocated == 1)
		{
			//Set next block to point to NULL, in order to merge it back into notAllocated.
			block->next = NULL;

			//notAllocated size is adjusted accordingly.
			block->parentPool->notAllocated->size = block->parentPool->notAllocated->size + block->size;
			block->parentPool->notAllocated->offset = 0;
			block->isAllocated = 0;

			//Make a pointer that searches for it through the allocated list.
			Block* temp = block->parentPool->allocated;

			//If found, remove it from the allocated list.
			if (block->parentPool->allocated != NULL)
			{
				if (temp == block)
				{
					block->parentPool->allocated = block->parentPool->allocated->next;
				}
				//Or keep searching for it.
				else
				{
					while (temp->next != NULL)
					{
						if (temp->next == block)
						{
							temp->next = temp->next->next;
						}
						else
						{
							temp = temp->next;
						}
					}
				}
			}
		}
	}
}