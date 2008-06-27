/*
 * This is the public interface file for the Monte Carlo framework.
 * 
 * It describes the prototypes provided by the Monte Carlo framework.
 *
 * The implementation is provided in mc.c.
 *
 * Original author: James S. Ravn (james.ravn@gmail.com)
*/

#ifndef MC_H
#define MC_H

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
 * algorithm after the final iteration to get a much more accurate estimate of
 * error. Use the mc_set_errconf(int) function to set the confidence level for
 * this final estimate, otherwise it defaults to 66% (roughly equivalent to one
 * standard deviation).
 */
void mc_simulate_many(float (*simulate_once)(),
		      int N, float absolute_precision, float relative_precision,
		      int print_iterations);

/* Returns the observed mean from running the simulation many times. */
float mc_mu();

/* Returns the +/- error of mu, estimated using the bootstrap algorithm. */
float mc_err();

/* Returns the observed variance from running the simulation many times. */
float mc_var();

#endif
