#include "Wall.h"

Wall::Wall()
{
}


Wall::~Wall()
{
}
bool Wall::intersectSimple(const Vector2D& position, const Vector2D& ray)
{
	Vector2D A = position;
	Vector2D B = ray;
	Vector2D C = _position;
	Vector2D D = _position + _wallEnd;

	double rTop = (A.y - C.y) * (D.x - C.x) - (A.x - C.x) * (D.y - C.y);
	double rBot = (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);

	double sTop = (A.y - C.y) * (B.x - A.x) - (A.x - C.x) * (B.y - A.y);
	double sBot = (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);

	if (rBot == 0 || sBot == 0)
		return false;

	double r = rTop / rBot;
	double s = sTop / sBot;

	return (r > 0 && r < 1 && s > 0 && s < 1);
}

bool Wall::intersect(const Vector2D& position, const Vector2D& ray, double& distance, Vector2D& point)
{
	Vector2D A = position;
	Vector2D B = ray;
	Vector2D C = _position;
	Vector2D D = _position + _wallEnd;

	double rTop = (A.y - C.y) * (D.x - C.x) - (A.x - C.x) * (D.y - C.y);
	double rBot = (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);

	double sTop = (A.y - C.y) * (B.x - A.x) - (A.x - C.x) * (B.y - A.y);
	double sBot = (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);

	if (rBot == 0 || sBot == 0)
		return false;

	double r = rTop / rBot;
	double s = sTop / sBot;

	if(r > 0 && r < 1 && s > 0 && s < 1)
	{
		distance = (Vector2D::distance(A, B) * r);
		point = A + r * (B - A);

		return true;
	}

	distance = 0;
	return false;
}

void Wall::setWallEnd(const Vector2D& position)
{
	_wallEnd = position - _position;
}

void Wall::calculateNormals()
{
//	_normal = side * Vector2D::normalize(Vector2D::perpendicular(_position));
	Vector2D temp = Vector2D::normalize(_wallEnd);
	_normal.x = -temp.y;
	_normal.y = temp.x;
}

void Wall::render(SDL_Renderer* gRenderer) const
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		SDL_RenderDrawLine(
			gRenderer,
			_position.x + _wallEnd.x / 2,
			_position.y + _wallEnd.y / 2,
			_position.x + _wallEnd.x / 2 + _normal.x * 20,
			_position.y + _wallEnd.y / 2 + _normal.y * 20);

		SDL_RenderDrawLine(
			gRenderer,
			_position.x,
			_position.y,
			_position.x + _wallEnd.x,
			_position.y + _wallEnd.y);
}

const Vector2D& Wall::getNormal() const
{
	return _normal;
}
