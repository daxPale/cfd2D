#include "FluidCube.h"

FluidCube::FluidCube(int a_size, float a_dt, int a_diffusion, int a_viscosity)
{
	size = a_size;

	dt = a_dt;
	diff = a_diffusion;
	visc = a_viscosity;

	s = new float(size * size);
	density = new float(size * size);

	Vx = new float(size * size);
	Vy = new float(size * size);

	Vx0 = new float(size * size);
	Vy0 = new float(size * size);
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

	delete(cube);
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

int FluidCube::locIndex(int x, int y) {
	return x + y * size;
}