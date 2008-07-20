/*
 * Unit tests for the monte carlo implementation.
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

#include <math.h>

#include "minunit.h"
#include "mc_gen.h"
#include "mc_prng.h"
#include "mc.h"

int tests_run = 0;

static float mock_sim()
{
	static int sim_r = 0.0f;
	sim_r = 1.0f - sim_r;
	return sim_r;
}

static float mock_sim_exp()
{
	return mc_gen_exponential(10.0f);
}

static float mock_sim_norm()
{
	return mc_gen_std_normal();
}

static float mock_sim_uni()
{
	return mc_gen_uniform();
}

static mu_test test_sim_simple()
{
	mc_simulate_many(mock_sim, 100, 0.0, 0.0, 0);
	mu_assert("mu == 0.5,",  mc_mu() > 0.49 && mc_mu() < 0.51f);
	mu_assert("var == 0.25", mc_var() > 0.24 && mc_var() < 0.26);
	mu_assert("err == 0.05", mc_err() > 0.049 && mc_err() < 0.051);

	return 0;
}

static mu_test test_sim_exp()
{
	mc_simulate_many(mock_sim_exp, 1000, 0.0, 0.0, 0);
	mu_assert("mu == 0.1,",  mc_mu() > 0.09 && mc_mu() < 0.11f);
	mu_assert("var == 0.01", mc_var() > 0.009f && mc_var() < 0.011f);
	mu_assert("err == 0.0029", mc_err() > 0.0028 && mc_err() < 0.0030);

	return 0;
}

static mu_test test_sim_norm()
{
	mc_simulate_many(mock_sim_norm, 1000, 0.0, 0.0, 0);
	mu_assert("mu == 0.0", mc_mu() > -0.1 && mc_mu() < 0.1);
	mu_assert("var == 1.0", mc_var() > 0.9 && mc_var() < 1.1);
	mu_assert("err == 0.0316", mc_err() > 0.031 && mc_err() < 0.32);

	return 0;
}

static mu_test test_sim_uni()
{
	mc_simulate_many(mock_sim_uni, 1000, 0.0, 0.0, 0);
	mu_assert("mu == 0.5", mc_mu() > 0.48 && mc_mu() < 0.52);
	mu_assert("var == 0.083", mc_var() > 0.082 && mc_var() < 0.084);
	mu_assert("err == 0.0083", mc_err() > 0.0082 && mc_err() < 0.0084);

	return 0;
}

static int g_it = 0;
static void mock_cb(int iteration)
{
	g_it = iteration;
}

static mu_test test_callback()
{
	mc_simulate_many(mock_sim, 12, 0.0, 0.0, mock_cb);
	mu_assert("g_it == 11", g_it == 11);

	return 0;
}

static mu_test tests() 
{
	unsigned long s = 123456789;
	mc_prng_seed(&s, 1);
	mc_gen_init(mc_prng_next);
	mc_init_bs(66, mc_gen_number);

	mu_run(test_sim_simple);
	mu_run(test_sim_exp);
	mu_run(test_sim_norm);
	mu_run(test_sim_uni);
	mu_run(test_callback);

	return 0;
}

int main()
{
	mu_run_all(tests);
	return 0;
}
