#include "Goal.h"



Goal::Goal(Vehicle* vehicle) :
	_vehicle(vehicle)
{
}


Goal::~Goal()
{
}

bool Goal::handleMessages(Telegram& telegram)
{
	return true;
}

bool Goal::isComplete()
{
	return true;
}
