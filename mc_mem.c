#include <stdlib.h>
#include <stdio.h>

#include "mc_mem.h"

void *mc_malloc(size_t size)
{
	void *p = malloc(size);
	if (p == NULL) {
		printf("Unable to allocate memory!");
		exit(EXIT_FAILURE);
	}
	return p;
}

void *mc_realloc(void *ptr, size_t size)
{
	void *p = realloc(ptr, size);
	if (p == NULL) {
		printf("Unable to allocate memory!");
		exit(EXIT_FAILURE);
	}
	return p;
}

void mc_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
