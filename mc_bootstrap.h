/*
 * Bootstrap algorithm. This algorithm is used to create a distribution from
 * provided measurements.
 *
 * It is a simple algorithm. It will randomly select a value from one of the
 * provided measurements. It requires a lot of measurements to work well.
 *
 * This can be used to get the error of the mean of an unknown distribution. For
 * example, by sampling 201 mean values and sorting them, one can find the 66%
 * confidence error (roughly equivalent to standard error in the normal
 * distribution) by finding the difference between the 35th (101-66) and 167th
 * (101+66) values and dividing by 2. See calc_bs_error in mc.c for an example
 * of this.
 *
 * As an example:
 *   void *bootstrap = bs_init(mc_gen_number); -> returns bootstrap object
 *   bs_add(bootstrap, 0.5); -> adds 0.5 to measurements
 *   bs_sample(bootstrap); -> returns 0.5
 *   bs_free(bootstrap); -> frees memory, object is no longer usable
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
 * The number function should return a random long over a uniform range [from,
 * to]. Unless you want to do something funky.
 *
 * Returns a pointer to a bootstrap object on success. Returns NULL otherwise.
 */
void *bs_init(long (*number)(long from, long to));

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
int bs_add(void *bootstrap, float measurement);

/*
 * Returns one of the provided measurements at random. It is sampled using the
 * number function pointer provided in bs_init.
 */
float bs_sample(const void *bootstrap);

/*
 * Free all memory associated with the given bootstrap object. The bootstrap
 * object is unusable after using this function.
 */
void bs_free(void *bootstrap);

#endif

