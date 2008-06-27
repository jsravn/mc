/*
 * This is the public interface file for the pseudo random number generator.
 * 
 * It describes the prototypes required by the Monte Carlo framework.
 *
 * An implementation is provided in mc_prng.c. It uses the CWMC1024 pseudo
 * random number generator described by Marsaglia, with a period of 2^131104.
 *
 * Original author: James S. Ravn (james.ravn@gmail.com)
*/

#ifndef MC_PRNG_H
#define MC_PRNG_H

/*
 * Seeds the prng.
 *
 * @precondition: Contains at least one seed and size is equal to the number of
 * seeds.
 *
 * @postcondition: The prng is seeded, discarding additional seeds or creating
 * additional seeds internally as needed.
*/
void mc_prng_seed(unsigned long seeds[], int size);

/* Returns the next 32-bit integer from the prng. */
unsigned long mc_prng_next();

#endif
