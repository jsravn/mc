/*
 * This is the public interface file for the Monte Carlo framework.
 * 
 * It describes the prototypes provided by the Monte Carlo framework.
 *
 * The implementation is provided in mc.c.
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

#ifndef MC_H
#define MC_H

/* 
 * Set to 0 to disable the bootstrap algorithm. The bootstrap algorithm is used
 * to get a more accurate value for the error. However it requires a lot of
 * memory since it stores a result for every iteration. So on a 32-bit machine,
 * this is 4 bytes an iteration, or roughly 4MB for every 1 million
 * iterations. For most machines and simulations this shouldn't be an issue.
 */
#define BOOTSTRAP 1

/*
 * Initialize the bootstrap error algorithm. The confidence represents the
 * confidence interval for the error. 66% approximates 1 standard deviation on
 * a normal distribution and is commonly used as an error estimate.
 *
 * The number function should generate a random long over the uniform interval
 * [to, from].
 */
void mc_init_bs(int confidence, long (*number)(long to, long from));

/*
 * This is the big kahuna for running a simulation many times. The
 * simulate_once function returns a float representing its outcome. e.g. in a
 * binomial experiment, it could return 1.0f for true and 0.0f for false.
 *
 * The output can be read using the other framework functions, such as mc_mu(),
 * mc_error(), and mc_variance().
 *
 * It stops running when:
 * A) error is less than the absolute_precision
 * B) error/mu is less than the relative_precision
 * C) number of iterations exceeds N
 *
 * The error is calculated each iteration using a fast approximation based on
 * the assumption of a normal distribution. It then uses the bootstrap
 * algorithm if BOOTSTRAP is defined to get a more accurate estimate of final
 * error.
 *
 * The callback function is called each iteration. Set it to NULL to not do
 * anything.
 */
void mc_simulate_many(float (*simulate_once)(),
		      int N, float absolute_precision, float relative_precision,
		      void (*callback)(int iteration));

/* Returns the observed mean from running the simulation many times. */
float mc_mu();

/*
 * Returns the +/- error of mu. This is calculated by the bootstrap algorithm
 * if BOOTSTRAP is defined. Otherwise it is an approximation based on the
 * normal distribution.
 */
float mc_err();

/* Returns the observed variance from running the simulation many times. */
float mc_var();

/* Convenience callback for printing out simple information each iteration */
void mc_print_iteration(int iteration);

#endif
