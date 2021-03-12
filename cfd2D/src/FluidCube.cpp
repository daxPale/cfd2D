#include "FluidCube.h"

FluidCube::FluidCube(float a_dt, int a_diffusion, int a_viscosity)
{
	size = N;

	dt = a_dt;
	diff = a_diffusion;
	visc = a_viscosity;

	s = (float*) calloc(N  * N, sizeof(float));
	density = (float*) calloc(N * N, sizeof(float));

	Vx = (float*) calloc(N * N, sizeof(float));
	Vy = (float*) calloc(N * N, sizeof(float));

	Vx0 = (float*) calloc(N * N, sizeof(float));
	Vy0 = (float*) calloc(N * N, sizeof(float));
}
	 
FluidCube::~FluidCube() {
	freeCube(this);
}

void FluidCube::freeCube(FluidCube *cube)
{
	delete(cube->s);
	delete(cube->density);

	delete(cube->Vx);
	delete(cube->Vy);

	delete(cube->Vx0);
	delete(cube->Vy0);
}

void FluidCube::addDensity(int x, int y, float amount) {
	int index = locIndex(x, y);

	density[index] += amount;
}

void FluidCube::addVelocity(int x, int y, float amountX, float amountY) {
	int index = locIndex(x, y);

	Vx[index] += amountX;
	Vy[index] += amountY;
}

void FluidCube::step()
{
	float _visc = visc;
	float _diff = diff;
	float _dt = dt;

	float* _Vx = Vx;
	float* _Vy = Vy;

	float* _Vx0 = Vx0;
	float* _Vy0 = Vy0;

	float* _s = s;
	float* _density = density;

	diffuse(1, _Vx0, _Vx, _visc, _dt, 4);
	diffuse(2, _Vy0, _Vy, _visc, _dt, 4);

	project(Vx0, Vy0, Vx, Vy, 4);

	advect(1, Vx, Vx0, Vx0, Vy0, dt);
	advect(2, Vy, Vy0, Vx0, Vy0, dt);

	project(Vx, Vy, Vx0, Vy0, 4);

	diffuse(0, s, density, diff, dt, 4);
	advect(0, density, s, Vx, Vy, dt);
}
