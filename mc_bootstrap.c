#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "mc_bootstrap.h"
#include "mc_mem.h"

/* Generate random unsigned longs */
static unsigned long (*g_num)(unsigned long from, unsigned long to);
static unsigned long g_alloc_size = 0; /* Allocation size */
static unsigned long g_size = 0; /* Number of g_measurements */
static float *g_measurements = NULL; /* Float array of measurements */

/* Postconditions: g_measurements = NULL and g_size = 0 */
void bs_free()
{
	if (!g_measurements)
		return;

	mc_free(g_measurements);
	g_measurements = NULL;
	g_size = 0;
}

void bs_init(unsigned long (*number)(unsigned long from, unsigned long to),
	     unsigned long alloc_size)
{
	if (g_measurements)
		bs_free();

	g_num = number;
	g_alloc_size = alloc_size;
	g_measurements = mc_malloc(sizeof(float) * alloc_size);
}

static int increase_size()
{
	/* Check for potential overflow */
	if (g_alloc_size > ULONG_MAX / 2) {
		puts("Can't allocate memory for bootstrap measurements!");
		printf("size would be > %lu\n", ULONG_MAX);
		return -1;
	}

	g_alloc_size *= 2;
	g_measurements = mc_realloc(g_measurements, g_alloc_size);
	return 0;
}

int bs_add(float measurement)
{
	if (g_size + 1 > g_alloc_size)
		if (increase_size() != 0)
			return -1;

	g_measurements[g_size++] = measurement;
	return 0;
}

float bs_sample()
{
	return g_measurements[g_num(0, g_size - 1)];
}
