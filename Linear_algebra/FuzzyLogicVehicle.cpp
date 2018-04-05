#include "FuzzyLogicVehicle.h"

FuzzyLogicVehicle::FuzzyLogicVehicle(Environment* environment, SDL_Renderer* renderer)
{
	//create variables
	FuzzyVariable &distToFuel = fm.CreateFLV("distToFuel");
	FzSet Fuel_Close = distToFuel.AddLeftShoulderSet("Fuel_Close", 0, 50, 125);
	FzSet Fuel_Medium = distToFuel.AddTriangularSet("Fuel_Medium", 50, 125, 300);
	FzSet Fuel_Far = distToFuel.AddRightShoulderSet("Fuel_Far", 125, 300, 1000);

	FuzzyVariable &distToSmallAgents = fm.CreateFLV("distToSmallAgents");
	FzSet Agents_Close = distToSmallAgents.AddLeftShoulderSet("Agents_Close", 0, 5, 10);
	FzSet Agents_Medium = distToSmallAgents.AddTriangularSet("Agents_Medium", 5, 10, 150);
	FzSet Agents_Far = distToSmallAgents.AddRightShoulderSet("Agents_Far", 30, 150, 1000);

	FuzzyVariable &desirability = fm.CreateFLV("desirability");
	FzSet Undesirable = desirability.AddLeftShoulderSet("Undesirable", 0, 25, 50);
	FzSet Desirable = desirability.AddLeftShoulderSet("Desirable", 25, 50, 75);
	FzSet Very_Desirable = desirability.AddLeftShoulderSet("Very_Desirable", 50, 75, 100);

	//create rules
	//desirability is desirability to chase agents
	fm.AddRule(*(new FzAND(Fuel_Far, Agents_Far)), Desirable);			//if fuel is far and agents far, undesirable
	fm.AddRule(*(new FzAND(Fuel_Medium, Agents_Far)), Undesirable);		//if fuel is medium and agents far, undesirable
	fm.AddRule(*(new FzAND(Fuel_Close, Agents_Far)), Undesirable);		//if fuel is close and agents far, undesirable
	fm.AddRule(*(new FzAND(Fuel_Far, Agents_Medium)), Very_Desirable);	//if fuel is far and agents are medium, desirable
	fm.AddRule(*(new FzAND(Fuel_Medium, Agents_Medium)), Desirable);	//if fuel is medium and agents are medium, desirable
	fm.AddRule(*(new FzAND(Fuel_Close, Agents_Medium)), Undesirable);	//if fuel is close and agents are medium, undesirable
	fm.AddRule(*(new FzAND(Fuel_Far, Agents_Close)), Very_Desirable);	//if fuel is far and agents are close, very desirable
	fm.AddRule(*(new FzAND(Fuel_Medium, Agents_Close)), Very_Desirable);//if fuel is medium and agents are close, very desirable
	fm.AddRule(*(new FzAND(Fuel_Close, Agents_Close)), Desirable);		//if fuel is close and agents are close, desirable

	//fuzzy logic test data
	fm.Fuzzify("distToFuel", 250);
	fm.Fuzzify("distToSmallAgents", 20);

	//seems like the desirability will range from 12.5(we want to NOT chase agents) to 62.5(we REALLY want to chase agents)
	//if desirability < 37.5 we'll go for fuel
	//else we'll chase small agents 
	std::cout << fm.DeFuzzify("desirability", FuzzyModule::max_av) << std::endl;

	//zet current target
	currentTarget = Environment::GetInstance()->getClosestVehicle(this)->getPosition();
	getSteering()->setSeekActive(currentTarget, 1.0f);
	
	Vehicle::Vehicle(environment, renderer);
}


FuzzyLogicVehicle::~FuzzyLogicVehicle()
{
	Vehicle::~Vehicle();
}

void FuzzyLogicVehicle::update(double delta) {
	//fuzzy logic here
	fm.Fuzzify("distToFuel", Vector2D::distance(this->getPosition(), Vector2D(150, 400)));
	fm.Fuzzify("distToSmallAgents", Vector2D::distance(Environment::GetInstance()->getClosestVehicle(this)->getPosition(), this->getPosition()));

	float desirability = fm.DeFuzzify("desirability", FuzzyModule::max_av);

	std::cout << "Desirability to chase agents: " << desirability << std::endl;

	if (desirability < 37.5) {
		//chase fuel
		//set target vector to fuel
		getSteering()->setSeekActive(Vector2D(150, 400), 1.0f);
	}
	else {
		//chase agents
		//set target vector to closest agent
		getSteering()->setSeekActive(Environment::GetInstance()->getClosestVehicle(this)->getPosition(), 1.0f);
	}
	
	Vehicle::update(delta);
}