#include <limits.h>

#include "minunit.h"
#include "mc_gen.h"
#include "mc_prng.h"
#include "mc_bootstrap.h"

int tests_run = 0;

static mu_test test_add_and_sample()
{
	int i, founda, foundb;

	mu_assert("init in test_add_and_sample", bs_init(mc_gen_number) == 0);

	mu_assert("bs_add(0.75)", bs_add(0.75) == 0);
	for (i = 0; i < 3; i++)
		mu_assert("equals 0.75", bs_sample() == 0.75);

	mu_assert("bs_add(0.5)", bs_add(0.5) == 0);
	founda = foundb = 0;
	for (i = 0; i < 10; i++) {
		if (bs_sample() == 0.5)
			founda++;
		if (bs_sample() == 0.75)
			foundb++;
	}
	mu_assert("0.5 happened at least once", founda > 0);
	mu_assert("0.75 happened at least once", foundb > 0);

	bs_free();

	return 0;
}
static mu_test test_add_failure()
{
	unsigned long i;

	mu_assert("init in test_add_failure", bs_init(mc_gen_number) == 0);

	for (i = 0; i < 1e6; i++)
		mu_assert("add should succeed", bs_add(1.5) == 0);

	bs_free();

	return 0;
}

static mu_test test_init()
{
	mu_assert("init in test_init", bs_init(mc_gen_number) == 0);
	bs_free();

	return 0;
}

static mu_test tests()
{
	unsigned long s = 123456789;
	mc_prng_seed(&s, 1);
	mc_gen_init(mc_prng_next);

	mu_run(test_init);
/* 	mu_run(test_add_and_sample); */
	mu_run(test_add_failure);

	return 0;
}

int main()
{
	mu_run_all(tests);
	return 0;
}
