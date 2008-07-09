#include <stdlib.h>

#include "mc_bootstrap.h"
#include "mc_mem.h"

static int (*g_num)(int from, int to); /* Function for generating random ints */
static int g_allocs = 0; /* Number of allocations */
static int g_alloc_size = 0; /* Allocation size */
static int g_size = 0; /* Number of g_measurements */
static float *g_measurements = NULL; /* Float array of measurements */

void bs_init(int (*number)(int from, int to), unsigned long alloc_size)
{
	if (g_measurements)
		bs_free();

	g_num = number;
	g_alloc_size = alloc_size;
	g_measurements = mc_malloc(sizeof(float) * alloc_size);
	g_allocs++;
}

/* Postconditions: g_measurements = NULL and g_size = 0 */
void bs_free()
{
	int i;

	if (!g_measurements)
		return;

	for (i = 0; i < g_allocs; i++)
		mc_free(&g_measurements[i * g_alloc_size]);

	g_measurements = NULL;
	g_size = 0;
}
