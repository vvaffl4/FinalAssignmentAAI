#include "Food.h"

Food::Food()
{}


Food::~Food()
{
}

float Food::take(float amount) const
{
	return amount;
}

void Food::render(SDL_Renderer* gRenderer) const
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
