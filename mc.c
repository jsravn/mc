#include <stdio.h>
#include <math.h>

#include "mc.h"

static float g_mu;
static float g_var;
static float g_err;

void mc_simulate_many(float (*simulate_once)(),
		      int N, float absolute_precision, float relative_precision,
		      void (*callback)(int iteration))
{
	int i;
	float sum1 = 0.0f, sum2 = 0.0f;
	float result;

	g_mu = 0.0f;
	g_var = 0.0f;
	g_err = 0.0f;

	for (i = 0; i < N; i++) {
		result = simulate_once();
		
		sum1 += result;
		sum2 += result * result;
		
		g_mu = sum1 / (i + 1);
		g_var = sum2 / (i + 1) - g_mu * g_mu;
		g_err = sqrt(g_var / (i + 1));

		if (callback)
			callback(i);

		if (i > 0 && g_err != 0.0f
		    && (g_err < absolute_precision 
			|| g_err < relative_precision * g_mu))
			break;
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
