#pragma once
#include "Math.h"
#define N 256

//Function Prototypes
int locIndex(int, int);
void diffuse(int, float*, float*, float, float, int);
void lin_solve(int, float*, float*, float, float, int);
void set_bounds(int, float*);
void project(float*, float*, float*, float*, int);
void advect(int, float*, float*, float*, float*, float);

static int locIndex(int x, int y) {
	return x + y * N;
}

static void diffuse(int b, float* x, float* x0, float diff, float dt, int iter)
{
	float a = dt * diff * (N - 2) * (N - 2);
	lin_solve(b, x, x0, a, 1 + 6 * a, iter);
}

static void set_bounds(int b, float* x) {
	for (int i = 1; i < N - 1; i++) {
		x[locIndex(i, 0)] = b == 2 ? -x[locIndex(i, 1)] : x[locIndex(i, 1)];
		x[locIndex(i, N - 1)] = b == 2 ? -x[locIndex(i, N - 2)] : x[locIndex(i, N - 2)];
	}
	for (int j = 1; j < N - 1; j++) {
		x[locIndex(0, j)] = b == 1 ? -x[locIndex(1, j)] : x[locIndex(1, j)];
		x[locIndex(N - 1, j)] = b == 1 ? -x[locIndex(N - 2, j)] : x[locIndex(N - 2, j)];
	}

	x[locIndex(0, 0)] = 0.5f * (x[locIndex(1, 0)] + x[locIndex(0, 1)]);
	x[locIndex(0, N - 1)] = 0.5f * (x[locIndex(1, N - 1)] + x[locIndex(0, N - 2)]);
	x[locIndex(N - 1, 0)] = 0.5f * (x[locIndex(N - 2, 0)] + x[locIndex(N - 1, 1)]);
	x[locIndex(N - 1, N - 1)] = 0.5f * (x[locIndex(N - 2, N - 1)] + x[locIndex(N - 1, N - 2)]);
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
		set_bounds(b, x);
	}
}

static void project(float* velocX, float* velocY, float* p, float* div, int iter)
{
	for (int j = 1; j < N - 1; j++) {
		for (int i = 1; i < N - 1; i++) {
			div[locIndex(i, j)] = -0.5f * (
				velocX[locIndex(i + 1, j)]
				- velocX[locIndex(i - 1, j)]
				+ velocY[locIndex(i, j + 1)]
				- velocY[locIndex(i, j - 1)]
				) / N;
			p[locIndex(i, j)] = 0;
		}
	}

	set_bounds(0, div);
	set_bounds(0, p);
	lin_solve(0, p, div, 1, 6, iter);

	for (int k = 1; k < N - 1; k++) {
		for (int j = 1; j < N - 1; j++) {
			for (int i = 1; i < N - 1; i++) {
				velocX[locIndex(i, j)] -= 0.5f * (p[locIndex(i + 1, j)]
					- p[locIndex(i - 1, j)]) * N;
				velocY[locIndex(i, j)] -= 0.5f * (p[locIndex(i, j + 1)]
					- p[locIndex(i, j - 1)]) * N;
			}
		}
	}
	set_bounds(1, velocX);
	set_bounds(2, velocY);
}

static void advect(int b, float* d, float* d0, float* velocX, float* velocY, float dt)
{
	float i0, i1, j0, j1;

	float dtx = dt * (N - 2);
	float dty = dt * (N - 2);

	float s0, s1, t0, t1;
	float tmp1, tmp2, x, y;

	float Nfloat = N;
	float ifloat, jfloat;
	int i, j;

	
	for (j = 1, jfloat = 1; j < N - 1; j++, jfloat++) {
		for (i = 1, ifloat = 1; i < N - 1; i++, ifloat++) {
			tmp1 = dtx * velocX[locIndex(i, j)];
			tmp2 = dty * velocY[locIndex(i, j)];

			x = ifloat - tmp1;
			y = jfloat - tmp2;

			if (x < 0.5f) x = 0.5f;
			if (x > Nfloat + 0.5f) x = Nfloat + 0.5f;
			i0 = floorf(x);
			i1 = i0 + 1.0f;
			if (y < 0.5f) y = 0.5f;
			if (y > Nfloat + 0.5f) y = Nfloat + 0.5f;
			j0 = floorf(y);
			j1 = j0 + 1.0f;

			s1 = x - i0;
			s0 = 1.0f - s1;
			t1 = y - j0;
			t0 = 1.0f - t1;
	
			int i0i = (int)i0;
			int i1i = (int)i1;
			int j0i = (int)j0;
			int j1i = (int)j1;

			d[locIndex(i, j)] =
				s0 * (t0 * d0[locIndex(i0i, j0i)] + t1 * d0[locIndex(i0i, j1i)]) +
				s1 * (t0 * d0[locIndex(i1i, j0i)] + t1 * d0[locIndex(i1i, j1i)]);
		}
	}
	
	set_bounds(b, d);
}