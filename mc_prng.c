/* 
 * This file implements a high quality psuedo-random number generator.
 *
 * It uses a complimentary-multiply-with-carry RNG with a period of 2^131104 as
 * described by Marsaglia. This provides a nice balance between speed and
 * randomness (exceeding the Mersenne Twister on both accounts).
 *
 * The main drawback is use of long long to support the multiplication of two
 * longs. This requires a C99 compatible compiler (or at least long long
 * extension support).
 *
 * Marsaglia, G. 2003. Seeds for random number generators. Commun. ACM 46, 5
 * (May. 2003), 90-93. DOI= http://doi.acm.org/10.1145/769800.769827
 */

#include "mc_prng.h"

/* CMWC1024 PRNG implementation */

static unsigned long Q[1024]; /* 1024 seed values  */
static unsigned long g_c, g_i;    /* cmwc state values */

static void cmwc_reset()
{
	g_c = 362436;
	g_i = 1023;
}

/* Gets the next long integer using the cmwc algorithm. */
static unsigned long cmwc_next()
{
	unsigned long long t, a = 123471786ULL;
	unsigned long x, r = 0xfffffffe;
	
	g_i = (g_i + 1) & 1023;
	t = a * Q[g_i] + g_c;
	g_c = (t >> 32);
	x = t + g_c;
	if (x < g_c) {
		x++;
		g_c++;
	}

	return (Q[g_i] = r - x);
}

/* Seed and reset the prng. */
void mc_prng_seed(unsigned long *seeds, int size)
{
	int i, j;
	
	for (i = 0; i < size && i < 1024; i++)
		Q[i] = seeds[i];

	/* Use xorshift to seed the remaining values. */
	for (j = Q[i - 1]; i < 1024; i++) {		
		j ^= j << 13;
		j ^= j >> 17;
		j ^= j << 5;
		Q[i] = j;
	}

	cmwc_reset();
}

/* Get the next long integer in the random sequence. */
unsigned long mc_prng_next()
{
	return cmwc_next();
}
