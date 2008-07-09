#include <math.h>

#include "mc_gen.h"

static unsigned long (*prng_next)();

void mc_gen_init(unsigned long (*prng)())
{
	prng_next = prng;
}

float mc_gen_uniform()
{
	const float f = 2.328306437e-10f; /* 1.0 / (2^32 - 1) */
	return prng_next() * f;
}

long mc_gen_number(long from, long to)
{
	return (long)(mc_gen_uniform() * (to - from + 1)) + from;
}

unsigned long mc_gen_unumber(unsigned long from, unsigned long to)
{
	return (unsigned long)(mc_gen_uniform() * (to - from + 1)) + from;
}

/* Adapted from Knuth's implementation of Marsaglia's algorithm */
float mc_gen_std_normal()
{
	static float v1, v2, s;
	static int phase = 0;
	float x;

	if (phase == 0) {
		do {
			v1 = 2.0 * mc_gen_uniform() - 1.0;
			v2 = 2.0 * mc_gen_uniform() - 1.0;
			s = v1 * v1 + v2 * v2;
		} while (s >= 1 || s == 0);
		
		x = v1 * sqrt(-2.0 * log(s) / s);
	} else
		x = v2 * sqrt(-2.0 * log(s) / s);

	phase = 1 - phase;

	return x;
}

float mc_gen_normal(float mu, float sigma)
{
	return mu + sigma * mc_gen_std_normal();
}

float mc_gen_exponential(float lambda)
{
	return -1.0 * log(mc_gen_uniform()) / lambda;
}
