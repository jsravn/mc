#include "minunit.h"
#include "mc_prng.h"

int tests_run = 0;

static mu_test test_prng_seed()
{
	unsigned long t;
	unsigned long s = 2102123UL;

	mc_prng_seed(&s, 1);
	t = mc_prng_next();
	mu_assert("prng_next generates something", t);
	mu_assert("different values", t != mc_prng_next());

	mc_prng_seed(&s, 1);	
	mu_assert("make sure we get same value", t == mc_prng_next());

	return 0;
}

static mu_test complex_seed()
{
	int i, t;
	unsigned long s[1024] = { 2123211UL };

	for (i = 1; i < 1024; i++)
		s[i] = s[i - 1] + 1;

	mc_prng_seed(s, 1024);
	t = mc_prng_next();
	mu_assert("prng_next generates something after 1024 seeds", t);
	mu_assert("different values after 1024 seeds", t != mc_prng_next());

	mc_prng_seed(s, 1024);
	mu_assert("same value again with 1024 seeds", t == mc_prng_next());
	
	return 0;
}

static mu_test tests() 
{
	mu_run(test_prng_seed);
	mu_run(complex_seed);
	return 0;
}

int main()
{
	mu_run_all(tests);
	return 0;
}
