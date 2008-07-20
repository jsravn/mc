/*
 * This is the public interface file for the pseudo random number generator.
 * 
 * It describes the prototypes required by the Monte Carlo framework.
 *
 * An implementation is provided in mc_prng.c. It uses the CWMC1024 pseudo
 * random number generator described by Marsaglia, with a period of 2^131104.
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
