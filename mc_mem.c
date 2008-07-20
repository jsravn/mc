/*
 * Implementation of the memory allocators. See mc_mem.h for more information.
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

#include "mc_mem.h"

void *mc_malloc(size_t size)
{
	void *p = malloc(size);
	if (p == NULL) {
		printf("Unable to allocate memory!");
	}
	return p;
}

void *mc_realloc(void *ptr, size_t size)
{
	void *p = realloc(ptr, size);
	if (p == NULL) {
		printf("Unable to allocate memory!");
	}
	return p;
}

void mc_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
