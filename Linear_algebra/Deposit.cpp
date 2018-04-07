#include "Deposit.h"
#include <iostream>


Deposit::Deposit(int gold) :
	_gold(gold)
{
	_red = 0;
	_green = 0;
	_blue = 0;
	_alpha = 255;
}


Deposit::~Deposit()
{
}

float Deposit::take(float amount)
{
	_gold -= amount;
	
	if(_gold < 0)
	{
		float overflow = _gold;
		_gold = 0;
		return overflow + amount;
	}

	std::cout << "Deposit gold: " << _gold << std::endl;

	return amount;
}

bool Deposit::empty() const
{
	return _gold <= 0;
}

void Deposit::render(SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer,
		_red, _green, _blue, _alpha);
	SDL_RenderDrawLine(
		gRenderer,
		_position.x - 20,
		_position.y - 20,
		_position.x + 20,
		_position.y - 20);
	SDL_RenderDrawLine(
		gRenderer,
		_position.x + 20,
		_position.y - 20,
		_position.x + 20,
		_position.y + 20);
	SDL_RenderDrawLine(
		gRenderer,
		_position.x + 20,
		_position.y + 20,
		_position.x - 20,
		_position.y + 20);
	SDL_RenderDrawLine(
		gRenderer,
		_position.x - 20,
		_position.y + 20,
		_position.x - 20,
		_position.y - 20);
}