/*
 * Unit tests for the distribution generator implementation.
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

#include <limits.h>

#include "minunit.h"
#include "mc_gen.h"

int tests_run = 0;

static unsigned long next = 123456789;
static unsigned long mock_prng()
{
	unsigned long j = next;
	j ^= j << 13;
	j ^= j >> 17;
	j ^= j << 5;
	return next = j;
}

static mu_test test_init()
{
	mc_gen_init(mock_prng);
	return 0;
}

static mu_test test_uniform()
{
	int i;
	float t;
	for (i = 0; i < 1000; i++) {
		t = mc_gen_uniform();
		mu_assert("uniform in range", t >= 0.0f && t < 1.0f);
	}
	return 0;
}

static mu_test test_number() 
{
	int i, t, found;
	unsigned long t2;
	for (i = 0; i < 1000; i++) {
		t = mc_gen_number(-5, 10);
		mu_assert("number in range", t >= -5 && t <= 10);
	}

	found = 0;
	for (i = 0; i < 20; i++) {
		t = mc_gen_number(-5, 3);
		if (t == -5)
			found = 1;
	}
	mu_assert("-5 should have happened at least once", found);

	found = 0;
	for (i = 0; i < 20; i++) {
		t2 = mc_gen_unumber(ULONG_MAX - 2, ULONG_MAX);
		if (t2 == ULONG_MAX)
			found = 1;
	}
	mu_assert("ULONG_MAX should have happened at least once", found);

	return 0;
}

static mu_test test_normal()
{
	int i;
	float t;

	mc_gen_normal(-1.0, 1.0);

	for (i = 0; i < 20; i++) {	
		t = mc_gen_std_normal();
#if 0
		printf("%f\n", t);
#endif
	}

	return 0;
}

static mu_test test_exponential()
{
	int i;
	float t, sum = 0;

	for (i = 0; i < 20; i++) {
		t = mc_gen_exponential(10.0);
		sum += t;
#if 0
		printf("%f\n", t);
#endif
	}
#if 0
	printf("avg: %f\n", sum / 20.0f); 
#endif

	return 0;
}

static mu_test tests() 
{
	mu_run(test_init);
	mu_run(test_uniform);
	mu_run(test_number);
	mu_run(test_normal);
	mu_run(test_exponential);
	return 0;
}

int main()
{
	mu_run_all(tests);
	return 0;
}
