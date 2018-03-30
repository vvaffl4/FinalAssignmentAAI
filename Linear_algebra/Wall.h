#ifndef WALL_H
#define WALL_H
#pragma once
#include <SDL.h>
#include "BaseEntity.h"

class Wall : public BaseEntity
{
private:
	Vector2D _wallEnd;
	Vector2D _normal;
public:
	Wall();
	~Wall();
	bool intersectSimple(const Vector2D& position, const Vector2D& ray);
	bool intersect(const Vector2D& position, const Vector2D& ray, double& distance, Vector2D& point);
	void setWallEnd(const Vector2D& position);
	void calculateNormals();
	void render(SDL_Renderer* gRenderer) const;
	const Vector2D& getNormal() const;
};

#endif