#include "Stockpile.h"
#include <iostream>


Stockpile::Stockpile()
{
	_red = 0;
	_green = 0;
	_blue = 0;
	_alpha = 255;
}


Stockpile::~Stockpile()
= default;

void Stockpile::addGold(float gold)
{
	_gold += gold;

	std::cout << "Stockpile gold: " << _gold << std::endl;
}

void Stockpile::render(SDL_Renderer* gRenderer)
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