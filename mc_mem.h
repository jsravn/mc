/*
 * Memory utility functions for the Monte Carlo framework.
 *
 * Original author: James S. Ravn (james.ravn@gmail.com)
 */

#ifndef MC_MEM_H
#define MC_MEM_H

void *mc_malloc(size_t size);
void mc_free(void *ptr);

#endif
