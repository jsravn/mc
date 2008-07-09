/*
 * Bootstrap algorithm. This algorithm is used to create a distribution from
 * provided measurements.
 *
 * It is a simple algorithm. It will randomly select a value from one of the
 * provided measurements. It requires a lot of measurements to work well.
 *
 * This can be used to get the error of an unknown distribution. For example, by
 * sampling 200 random values and sorting them, one can find the 66% confidence
 * error by finding the difference between the 35th and 166th values and
 * dividing by 2. This is similar to one standard deviation in the normal
 * distribution.
 *
 * To use, first call bs_init(). Then add measurements using bs_add(float). Then
 * sample from the distribution using bs_sample(). When done, call
 * bs_free(). bs_free() is not required to re-init. bs_init() will automatically
 * free any previously allocated memory.
 *
 * Original author: James S. Ravn (james.ravn@gmail.com)
 */

#ifndef MC_BOOTSTRAP_H
#define MC_BOOTSTRAP_H

/*
 * Allocates required memory structures for use in the bootstrap algorithm and
 * frees any previously used memory.
 *
 * The number function should return a random long over the uniform range [from,
 * to].
 *
 * The size parameter determines how much memory is initially allocated for
 * stored measurements. 4 bytes are allocated for each measurement on a 32-bit
 * machine. The algorithm will automatically allocate additional memory of this
 * size as needed.
 */
void bs_init(unsigned long (*number)(unsigned long from, unsigned long to),
	     unsigned long alloc_size);

/*
 * Adds a measurement to be used by the algorithm when sampling. Returns a
 * non-zero value if unsuccessful.
 */
int bs_add(float measurement);

/*
 * Returns one of the provided measurements at random. Each measurement has an
 * equal chance of being returned.
 */
float bs_sample();

/* Free all memory used by the bootstrap algorithm. */
void bs_free();

#endif

