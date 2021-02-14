#pragma once

class FluidCube {
public:
	FluidCube(int a_size, float a_dt, int a_diffusion, int a_viscosity);
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

private:
	int locIndex(int x, int y);
};