#pragma once
#include "Vehicle.h"
#include "FuzzyModule.h"
#include "FuzzyVariable.h"
#include "FuzzyOperators.h"

class FuzzyLogicVehicle :
	public Vehicle
{
private:
	FuzzyModule fm;
	Vector2D currentTarget;
public:
	void update(double delta) override;
	FuzzyLogicVehicle(Environment* environment, SDL_Renderer* renderer);
	~FuzzyLogicVehicle();
};

