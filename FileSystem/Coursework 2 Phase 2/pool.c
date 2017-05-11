#include "pool.h"

Pool* allocatePool(int n)
{
	Pool* pool = NULL;
	if (n > 0)
	{
		pool = (Pool*)malloc(sizeof(Pool));
		if (pool != NULL)
		{
			pool->memory = malloc(sizeof(char)*n);
			if (pool->memory)
			{
				pool->size = n;
			}
			else
			{
				free(pool);
				pool = NULL;
			}
		}

		//The allocated list is empty at the moment.
		pool->allocated = NULL;

		//Creating a list of blocks. This is the first element, a block the size of the whole pool.
		pool->notAllocated = (Block*)malloc(sizeof(Block));
		pool->notAllocated->offset = 0;
		pool->notAllocated->size = n;
		pool->notAllocated->next = NULL;
		pool->notAllocated->parentPool = pool;
		pool->notAllocated->isAllocated = 0;
	}
	return pool;
}

void freePool(Pool* pool)
{
	if (pool)
	{
		free(pool->memory);
		pool->notAllocated = NULL;
		pool->allocated = NULL;
		free(pool);
	}
}

void store(Pool* pool, int offset, int size, void *object)
{
	if (pool && offset >= 0 && offset + size < pool->size)
	{
		memcpy((char*)pool->memory + offset, object, size);
	}
}

void *retrieve(Pool* pool, int offset, int size)
{
	if (pool && offset >= 0 && offset + size < pool->size)
	{
		return (char*)pool->memory + offset;
	}
	return NULL;
}