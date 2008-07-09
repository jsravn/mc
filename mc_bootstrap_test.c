#include "minunit.h"
#include "mc_gen.h"
#include "mc_prng.h"
#include "mc_bootstrap.h"

int tests_run = 0;

static mu_test test_init()
{
	bs_init(mc_gen_number, 10);
	bs_free();

	return 0;
}

static mu_test tests()
{
	unsigned long s = 123456789;
	mc_prng_seed(&s, 1);
	mc_gen_init(mc_prng_next);

	mu_run(test_init);

	return 0;
}

int main()
{
	mu_run_all(tests);
	return 0;
}
