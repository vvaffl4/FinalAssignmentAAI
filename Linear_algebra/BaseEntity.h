#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H
#pragma once

#include "Vector2D.h"
#include <list>

class BaseEntity
{
protected:
	unsigned int _id;
	unsigned int _type;
	Vector2D _position;
	Vector2D _scale;
	float _boundingRadius;
	bool _m_bTag;

public:
	BaseEntity();
	~BaseEntity();
	void setPosition(const Vector2D& position);
	const Vector2D& getPosition() const;
	void setScale(const Vector2D& scale);
	const Vector2D& getScale() const;
	float getBoundingRadius() const;
	void setBoundingRadius(float boundingRadius);
	float getRadius() const;
	unsigned int getId() const;

	template<class T, class CT>
	static std::list<T*> tagNeighbors(const T* entity, CT& container, double radius)
	{
		std::list<T*> result;

		for (typename CT::const_iterator currentEntity = container.begin(); 
			currentEntity != container.end(); 
			++currentEntity)
		{
			Vector2D toPosition = (*currentEntity)->getPosition() - entity->getPosition();

			double range = radius + (*currentEntity)->getBoundingRadius();

			if ((*currentEntity) != entity)
			{
				double magSqrt = toPosition.magnitudeSqrt();
				double doubleRange = range * range;

				if (magSqrt < doubleRange)
					result.push_back((*currentEntity));
			}
		}

		return result;
	}
};

#endif