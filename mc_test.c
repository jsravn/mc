#include <stdio.h>

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
	mc_simulate_many(mock_sim, 100, 0.0f, 0.0f, 0);
	mu_assert("mu should be close to 0.5", 
		  mc_mu() >= 0.49f && mc_mu() <= 0.51f);

	return 0;
}

static mu_test test_sim_exp()
{
	mc_simulate_many(mock_sim_exp, 1000, 0.0f, 0.0f, 0);
	mu_assert("mu == 0.1, var == 0.01",
		  mc_mu() >= 0.09 && mc_mu() <= 0.11f
		  && mc_var() >= 0.009f && mc_var() <= 0.011f);

	return 0;
}

static mu_test test_sim_norm()
{
	mc_simulate_many(mock_sim_norm, 1000, 0.0f, 0.0f, 0);
	mu_assert("mu == 0.0, var == 1.0",
		  mc_mu() >= -0.1 && mc_mu() <= 0.1
		  && mc_var() >= 0.9 && mc_var() <= 1.1);

	return 0;
}

static mu_test test_sim_uni()
{
	mc_simulate_many(mock_sim_uni, 1000, 0.0f, 0.0f, 0);
	mu_assert("mu == 0.5, var == 0.083",
		  mc_mu() >= 0.49 && mc_mu() <= 0.51
		  && mc_var() >= 0.082 && mc_var() <= 0.084);

	return 0;
}

static mu_test tests() 
{
	unsigned long s = 123456789;
	mc_prng_seed(&s, 1);
	mc_gen_init(mc_prng_next);

	mu_run(test_sim_simple);
	mu_run(test_sim_exp);
	mu_run(test_sim_norm);
	mu_run(test_sim_uni);

	return 0;
}

int main()
{
	mu_run_all(tests);
	return 0;
}
