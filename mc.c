#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mc.h"
#include "mc_gen.h"

static void *mu_malloc(size_t size)
{
	void *p = malloc(size);
	if (p == NULL) {
		printf("Unable to allocate memory!");
		exit(EXIT_FAILURE);
	}
	return p;
}

static void mu_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

static float g_mu;
static float g_var;
static float g_err;

void mc_simulate_many(float (*simulate_once)(),
		      int N, float absolute_precision, float relative_precision,
		      int print_iteration)
{
	int i;
	float *measurements;
	float sum1 = 0.0f, sum2 = 0.0f;
	float result;

	measurements = mu_malloc(sizeof(float) * N);
	g_mu = 0.0f;
	g_var = 0.0f;
	g_err = 0.0f;

	if (print_iteration)
		puts("n,mu,err,var");

	for (i = 0; i < N; i++) {
		result = simulate_once();
		
		measurements[i] = result;

		sum1 += result;
		sum2 += result * result;
		
		g_mu = sum1 / (i + 1);
		g_var = sum2 / (i + 1) - g_mu * g_mu;
		g_err = sqrtf(g_var / (i + 1));

		if (print_iteration)
			printf("%d,%f,%f,%f\n", i, g_mu, g_err, g_var);
		if (i > 0 && g_err != 0.0f
		    && (g_err < absolute_precision 
			|| g_err < relative_precision * g_mu))
			break;
	}

	mu_free(measurements);
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
