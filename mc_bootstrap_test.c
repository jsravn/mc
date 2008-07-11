#include <limits.h>

#include "minunit.h"
#include "mc_gen.h"
#include "mc_prng.h"
#include "mc_bootstrap.h"

int tests_run = 0;

static mu_test test_add_and_sample()
{
	int i, founda, foundb;
	void *bs;

	bs = bs_init(mc_gen_number);
	mu_assert("init in test_add_and_sample", bs != NULL);

	mu_assert("empty sample returns 0.0", bs_sample(bs) == 0.0);

	for (i = 0; i < 3; i++) {
		mu_assert("bs_add(0.75)", bs_add(bs, 0.75) == 0);
	}
	for (i = 0; i < 10; i++) {
		mu_assert("equals 0.75", bs_sample(bs) == 0.75);
	}

	mu_assert("bs_add(0.5)", bs_add(bs, 0.5) == 0);
	founda = foundb = 0;
	for (i = 0; i < 20; i++) {
		if (bs_sample(bs) == 0.5)
			founda++;
		if (bs_sample(bs) == 0.75)
			foundb++;
	}
	mu_assert("0.5 happened at least once", founda > 0);
	mu_assert("0.75 happened at least once", foundb > 0);

	bs_free(bs);

	return 0;
}

static mu_test test_add_failure()
{
	unsigned long i;
	void *bs;

	bs = bs_init(mc_gen_number);
	mu_assert("init in test_add_failure", bs != NULL);

	for (i = 0; i < 1e6; i++)
		mu_assert("add should succeed", bs_add(bs, 1.5) == 0);

	bs_free(bs);

	return 0;
}

static mu_test test_init()
{
	void *bs;

	bs = bs_init(mc_gen_number);
	mu_assert("init in test_init", bs != NULL);
	bs_free(bs);

	return 0;
}

static mu_test tests()
{
	unsigned long s = 123456789;
	mc_prng_seed(&s, 1);
	mc_gen_init(mc_prng_next);

	mu_run(test_init);
	mu_run(test_add_and_sample);
	mu_run(test_add_failure);

	return 0;
}

int main()
{
	mu_run_all(tests);
	return 0;
}
