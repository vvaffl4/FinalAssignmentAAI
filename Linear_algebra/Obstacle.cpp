#include "Obstacle.h"



Obstacle::Obstacle()
{
	_boundingRadius = 50;
}


Obstacle::~Obstacle()
{
}

void Obstacle::render(SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	float quarterPI = 3.14159 * 0.25;

	for(int i = 0; i < 8; ++i)
	{
		SDL_RenderDrawLine(
			gRenderer,
			_position.x + _boundingRadius * sin(quarterPI * i),
			_position.y + _boundingRadius * cos(quarterPI * i),
			_position.x + _boundingRadius * sin(quarterPI * (i + 1)),
			_position.y + _boundingRadius * cos(quarterPI * (i + 1)));
	}
}
