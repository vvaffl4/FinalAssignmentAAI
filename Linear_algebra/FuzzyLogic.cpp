// FuzzyLogic.cpp : Defines the entry point for the console application.
//

#include "FuzzyModule.h"
#include "FuzzyVariable.h"
#include "FuzzyOperators.h"
#include <iostream>

using namespace std;

int main_FLogic()
{
	FuzzyModule fm;
	FuzzyVariable& distToTarget = fm.CreateFLV("DistToTarget");

	FzSet Target_Close = distToTarget.AddLeftShoulderSet("Target_Close", 0, 25, 150);
	FzSet Target_Medium = distToTarget.AddTriangularSet("Target_Medium", 25, 150, 300);
	FzSet Target_Far = distToTarget.AddRightShoulderSet("Target_Far", 150, 300, 500);

	FuzzyVariable& desirability = fm.CreateFLV("Desirability");

	FzSet Undesirable = desirability.AddLeftShoulderSet("Undesirable", 0, 25, 50);
	FzSet Desirable = desirability.AddTriangularSet("Desirable", 25, 50, 75);
	FzSet VeryDesirable = desirability.AddRightShoulderSet("VeryDesirable", 50, 75, 100);

	FuzzyVariable& ammoStatus = fm.CreateFLV("AmmoStatus");

	FzSet Ammo_Low = ammoStatus.AddLeftShoulderSet("Ammo_Low", 0, 0, 10);
	FzSet Ammo_Okay = ammoStatus.AddTriangularSet("Ammo_Okay", 0, 10, 30);
	FzSet Ammo_Loads = ammoStatus.AddRightShoulderSet("Ammo_Loads", 10, 30, 40);

	fm.AddRule(*(new FzAND(Target_Close, Ammo_Loads)), Undesirable);
	fm.AddRule(*(new FzAND(Target_Close, Ammo_Okay)), Undesirable);
	fm.AddRule(*(new FzAND(Target_Close, Ammo_Low)), Undesirable);
	fm.AddRule(*(new FzAND(Target_Medium, Ammo_Loads)), VeryDesirable);
	fm.AddRule(*(new FzAND(Target_Medium, Ammo_Okay)), VeryDesirable);
	fm.AddRule(*(new FzAND(Target_Medium, Ammo_Loads)), Desirable);
	fm.AddRule(*(new FzAND(Target_Far, Ammo_Loads)), Desirable);
	fm.AddRule(*(new FzAND(Target_Far, Ammo_Okay)), Desirable);
	fm.AddRule(*(new FzAND(Target_Far, Ammo_Low)), Undesirable);

	fm.Fuzzify("DistToTarget", 200);
	fm.Fuzzify("AmmoStatus", 8);

	cout << fm.DeFuzzify("Desirability", FuzzyModule::max_av) << endl;

    return 0;
}

