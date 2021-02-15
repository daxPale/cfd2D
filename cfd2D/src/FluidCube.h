#pragma once
#include "Functions.h"
#include <iostream>

class FluidCube {
public:
	FluidCube(float a_dt, int a_diffusion, int a_viscosity);
	~FluidCube();

	int size;
	float dt;
	float diff;
	float visc;

	float* s;
	float* density;

	float* Vx;
	float* Vy;

	float* Vx0;
	float* Vy0;

	void freeCube(FluidCube *cube);
	void addDensity(int x, int y, float amount);
	void addVelocity(int x, int y, float amountX, float amountY);
	void step();

private:
};