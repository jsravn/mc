#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "mc_bootstrap.h"
#include "mc_mem.h"

#define BLOCK_SIZE ALLOC_SIZE / sizeof(float)

struct node {
	struct node *next;
	float data[BLOCK_SIZE];
};

/* Generate random longs */
static long (*g_num)(long from, long to);
static long g_size = 0; /* Number of total measurements */
static long g_tsize = 0; /* Number of measurements in tail block */
static struct node *g_head = NULL; /* Linked list of measurements */
static struct node *g_tail = NULL; /* Last item in linked list */

static int increase_size()
{
	struct node *c;

	c = mc_malloc(sizeof(struct node));
	if (!c)
		return -1;
	c->next = NULL;

	if (g_tail)
		g_tail->next = c;
	else
		g_head = c;
	g_tail = c;
	g_tsize = 0;

	return 0;
}

int bs_init(long (*number)(long from, long to))
{
	if (g_head)
		bs_free();

	g_num = number;

	return increase_size();
}

/* Postconditions: g_head = NULL and g_size = 0 */
void bs_free()
{
	struct node *c, *n;

	if (!g_head)
		return;

	for (c = g_head; c; c = n) {
		n = c->next;
		mc_free(c);
	}
	g_head = NULL;
	g_tail = NULL;
	g_tsize = 0;
	g_size = 0;
}

/* Precondition: increase_size() has been called at least once */
int bs_add(float measurement)
{
	int r;

	if (g_tsize + 1 > BLOCK_SIZE) {
		r = increase_size();
		if (r != 0)
			return -1;
	}

	if (g_size == LONG_MAX) {
		puts("Can't exceed LONG_MAX # of measurements.");
		return -1;
	}

	g_tail->data[g_tsize++] = measurement;
	g_size++;

	return 0;
}

float bs_sample()
{
	return 0.0;
}
