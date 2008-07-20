/*
 * Implementation of bootstrap algorithm. See mc_bootstrap.h for more
 * information.
 *
 * Copyright 2008 James Ravn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "mc_bootstrap.h"
#include "mc_mem.h"

#define BLOCK_SIZE (ALLOC_SIZE / sizeof(float))

struct node {
	struct node *next;
	float data[BLOCK_SIZE];
};

struct bootstrap {
	long (*num)(long from, long to); /* Generate random longs */
	long size;         /* Number of total measurements */
	long tsize;        /* Number of measurements in tail block */
	struct node *head; /* Linked list of measurements */
	struct node *tail; /* Last item in linked list */
};

static int increase_size(struct bootstrap *bs)
{
	struct node *c;

	c = mc_malloc(sizeof(struct node));
	if (!c)
		return -1;
	c->next = NULL;

	if (bs->tail)
		bs->tail->next = c;
	else
		bs->head = c;
	bs->tail = c;
	bs->tsize = 0;

	return 0;
}

void *bs_init(long (*number)(long from, long to))
{
	struct bootstrap *bs;

	bs = mc_malloc(sizeof(struct bootstrap));
	if (bs == NULL)
		return NULL;

	bs->num = number;
	bs->size = 0;
	bs->tsize = 0;
	bs->head = NULL;
	bs->tail = NULL;

	if (increase_size(bs) != 0) {
		bs_free(bs);
		bs = NULL;
	}

	return bs;
}

/* Postconditions: g_head = NULL and g_size = 0 */
void bs_free(void *bootstrap)
{
	struct node *c, *n;
	struct bootstrap *bs = bootstrap;

	if (!bs->head)
		return;

	for (c = bs->head; c; c = n) {
		n = c->next;
		mc_free(c);
	}

	mc_free(bs);
}

/* Precondition: increase_size() has been called at least once */
int bs_add(void *bootstrap, float measurement)
{
	int r;
	struct bootstrap *bs = bootstrap;

	if (bs->tsize + 1 > BLOCK_SIZE) {
		r = increase_size(bs);
		if (r != 0)
			return -1;
	}

	if (bs->size == LONG_MAX) {
		puts("Can't exceed LONG_MAX # of measurements.");
		return -1;
	}

	bs->tail->data[bs->tsize++] = measurement;
	bs->size++;

	return 0;
}

float bs_sample(const void *bootstrap)
{
	long i, n, block, block_n;
	struct node *c;
	const struct bootstrap *bs = bootstrap;

	if (bs->size == 0)
		return 0.0;

	n = bs->num(0, bs->size - 1);
	block = n / BLOCK_SIZE;
	block_n = n % BLOCK_SIZE;

	for (c = bs->head, i = 0; i < block; i++)
		c = c->next;

	return c->data[block_n];
}
