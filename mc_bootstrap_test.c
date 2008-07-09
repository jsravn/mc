#include "minunit.h"
#include "mc_gen.h"
#include "mc_prng.h"
#include "mc_bootstrap.h"

int tests_run = 0;

static mu_test test_add_and_sample()
{
	int i, founda, foundb;

	bs_init(mc_gen_unumber, 1);

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

static mu_test test_init()
{
	bs_init(mc_gen_unumber, 10);
	bs_free();

	return 0;
}

static mu_test tests()
{
	unsigned long s = 123456789;
	mc_prng_seed(&s, 1);
	mc_gen_init(mc_prng_next);

	mu_run(test_init);
	mu_run(test_add_and_sample);

	return 0;
}

int main()
{
	mu_run_all(tests);
	return 0;
}
