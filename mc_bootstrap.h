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
 * The main drawback is the memory requirement to store each measurement. On
 * long running simulations this can consume a large amount of memory. Consider
 * that on a 32-bit system a float is usually 4 bytes. At 4 million
 * measurements, we're consuming 16MB of memory. At 100 million, 400MB. So be
 * careful when using this algorithm on long running simulations. One solution
 * is to only add a percentage of measurements with a uniform distribution,
 * since the bootstrap algorithm just needs a representative sample.
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
 * Returns zero on success.
 */
int bs_init(long (*number)(long from, long to));

/*
 * ALLOC_SIZE determines how much memory is allocated for each block of stored
 * measurements. The optimum value depends on the expected number of
 * measurements. The algorithm uses a linked list of these blocks. So it
 * requires O(n / (alloc_size / sizeof(float))) time to find the correct block
 * to use. Depending on the number of measurements, a larger ALLOC_SIZE can
 * improve speed at the risk of more wasted memory.
 */
#define K * 1024
#define ALLOC_SIZE (256 K)

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

