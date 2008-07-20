/*
 * Unit tests for the monte carlo framework prng.
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
