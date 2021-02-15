#pragma once
#include "Math.h"
#define N 256

//Function Prototypes
int locIndex(int, int);
void diffuse(int, float*, float*, float, float, int);
void lin_solve(int, float*, float*, float, float, int);

static int locIndex(int x, int y) {
	return x + y * N;
}

static void diffuse(int b, float* x, float* x0, float diff, float dt, int iter)
{
	float a = dt * diff * (N - 2) * (N - 2);
	lin_solve(b, x, x0, a, 1 + 6 * a, iter);
}

static void lin_solve(int b, float* x, float* x0, float a, float c, int iter)
{
	float cRecip = 1.0 / c;
	for (int k = 0; k < iter; k++) {
		for (int j = 1; j < N - 1; j++) {
			for (int i = 1; i < N - 1; i++) {
				x[locIndex(i, j)] =
					(x0[locIndex(i, j)]
						+ a * (x[locIndex(i + 1, j)]
							+  x[locIndex(i - 1, j)]
							+  x[locIndex(i, j + 1)]
							+  x[locIndex(i, j - 1)])) 
						* cRecip;
			}
		}
		//set_bounds(b, x);
	}
}
