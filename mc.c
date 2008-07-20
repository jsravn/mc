/*
 * Monte carlo framework implementation. See mc.h for more information.
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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mc.h"
#include "mc_bootstrap.h"

static float g_mu;
static float g_var;
static float g_err;
static int g_conf;
static long (*g_num)(long to, long from);

void mc_init_bs(int confidence, long (*number)(long to, long from))
{
	g_conf = confidence;
	g_num = number;
}

static int flt_cmp(const void *p1, const void *p2)
{
	const float *a = p1;
	const float *b = p2;

	if (*a < *b)
		return -1;
	if (*a > *b)
		return 1;
	return 0;
}

static float calc_bs_error(const void *bs, int measurement_size)
{
	float means[201], mean;
	int i, j;

	for (i = 0; i < 201; i++) {
		mean = 0.0;
		for (j = 0; j < measurement_size; j++) {
			mean += bs_sample(bs) / measurement_size;
		}
		means[i] = mean;
	}

	qsort(means, 201, sizeof(float), flt_cmp);

	return (means[100 + g_conf] - means[100 - g_conf]) / 2.0;
}

void mc_simulate_many(float (*simulate_once)(),
		      int N, float absolute_precision, float relative_precision,
		      void (*callback)(int iteration))
{
	int i;
	float sum1 = 0.0, sum2 = 0.0;
	float result;
	void *bs;

	g_mu = 0.0;
	g_var = 0.0;
	g_err = 0.0;

	if (BOOTSTRAP)
		bs = bs_init(g_num);

	for (i = 0; i < N; i++) {
		result = simulate_once();

		sum1 += result;
		sum2 += result * result;
		
		g_mu = sum1 / (i + 1);
		g_var = sum2 / (i + 1) - g_mu * g_mu;
		g_err = sqrt(g_var / (i + 1));

		if (callback)
			callback(i);

		if (BOOTSTRAP)
			bs_add(bs, result);

		if (i > 0 && g_err != 0.0
		    && (g_err < absolute_precision 
			|| g_err < relative_precision * g_mu))
			break;
	}

	if (BOOTSTRAP) {
		g_err = calc_bs_error(bs, i);
		bs_free(bs);
	}
}

float mc_mu()
{
	return g_mu;
}

float mc_var()
{
	return g_var;
}

float mc_err()
{
	return g_err;
}

void mc_print_iteration(int iteration)
{
	if (iteration == 0)
		puts("n,mu,err,var");
	printf("%d,%f,%f,%f\n", iteration, mc_mu(), mc_err(), mc_var());
}
