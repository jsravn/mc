/*
 * This is the public interface file for a distribution generator.
 * 
 * It describes the prototypes required by the Monte Carlo framework.
 *
 * An implementation is provided in mc_gen.c.
 *
 * Original author: James S. Ravn (james.ravn@gmail.com)
*/

#ifndef MC_GEN_H
#define MC_GEN_H

/*
 * Initialize the generator with a psuedo random number generator. The prng
 * function should return a random sequence of unsigned long integers.
 */
void mc_gen_init(unsigned long (*prng)());

/* Returns a float in the uniform interval over [0, 1). */
float mc_gen_uniform();

/* Returns an integer in the uniform range [from, to]. */
int mc_gen_number(int from, int to);

/* Returns a float in the normal distribution. */
float mc_gen_normal(float mu, float sigma);

/* Returns a float in the standard normal distribution (mu = 0, sigma = 1). */
float mc_gen_std_normal();

/* Returns a float in the exponential distribution. */
float mc_gen_exponential(float lambda);

#endif
