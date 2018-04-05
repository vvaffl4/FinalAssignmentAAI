#include "SteeringBehaviorGroup.h"

SteeringBehaviorGroup::SteeringBehaviorGroup(Vehicle* vehicle, SDL_Renderer* renderer) :
	_vehicle(vehicle),
	_renderer(renderer)
{
	double theta = randomFloat() * (3.14159 * 2);
	
	_wanderTarget = Vector2D(
		static_cast<float>(_wanderRadius * cos(theta)),
		static_cast<float>(_wanderRadius * sin(theta)));
}


SteeringBehaviorGroup::~SteeringBehaviorGroup()
{
}

double SteeringBehaviorGroup::randomFloat() const
{
	return ((rand()) / (RAND_MAX + 1.0));
}

double SteeringBehaviorGroup::randomClamped() const
{
	return randomFloat() - randomFloat();
}

Vector2D SteeringBehaviorGroup::pointToLocalSpace(const Vector2D& point, const Vector2D& heading, const Vector2D& side,
	const Vector2D& position)
{
	const Vector2D transformPoint = point;

	const float tX = -position.dotProduct(heading);
	const float tY = -position.dotProduct(side);

	Matrix matrix(
		heading.x,	heading.y,	tX,
		side.x,		side.y,		tY,
		0,			0,			1
	);

	return transformPoint * matrix;
}

Vector2D SteeringBehaviorGroup::pointToWorldSpace(const Vector2D& point, const Vector2D& heading,
	const Vector2D& side, const Vector2D& position)
{
	return (Matrix(3, 3)
		.rotate(heading, side)
		.translate(position)) * point;
}

double SteeringBehaviorGroup::min(const double value1, const double value2) const
{
	if(value1 < value2)
		return value1;
	if (value1 > value2)
		return value2;
	return value1;
}

double SteeringBehaviorGroup::turnAroundTime(const Vehicle* agent, Vector2D target)
{
	Vector2D targetNormal = Vector2D::normalize(target - agent->getPosition());
	double targetNormalDot = agent->getHeading().dotProduct(targetNormal);

	const double coefficient = -0.5;
	return (targetNormalDot - 1.0) * coefficient;
}

Vector2D SteeringBehaviorGroup::vectorToWorldSpace(const Vector2D& vector, const Vector2D& heading,
	const Vector2D& side)
{
	Vector2D transformPoint = vector;

	Matrix matrix = Matrix(3, 3)
		.rotate(heading, side);

	return transformPoint * matrix;
}

Vector2D SteeringBehaviorGroup::findHidingPosition(const Vector2D& position, const double radius, const Vector2D& target)
{
	double distanceFromBoundary = 30.0;
	double distance = radius + distanceFromBoundary;

	return Vector2D::normalize(position - target) * distance + position;
}

Vector2D SteeringBehaviorGroup::seek(const Vector2D& input)
{
	return ((Vector2D::normalize(input - _vehicle->getPosition()) * _vehicle->getMaximumSpeed()) - _vehicle->getVelocity());
}

Vector2D SteeringBehaviorGroup::flee(const Vector2D & input)
{
//	const double fleeDistance = 100.0 * 100.0;
//	if (_vehicle->getPosition().distanceSqrt(input) > fleeDistance)
//		return Vector3;

	return ((Vector2D::normalize(_vehicle->getPosition() - input) * _vehicle->getMaximumSpeed()) - _vehicle->getVelocity());
}

Vector2D SteeringBehaviorGroup::arrive(const Vector2D & input, const double deceleration)
{
	Vector2D target = input - _vehicle->getPosition();

	const double distance = target.magnitude(); // get length/magnitude

	if(distance > 0)
	{
		const double decelerationAdjustment = 0.3;
		const double speed = min(distance / (deceleration * decelerationAdjustment), _vehicle->getMaximumSpeed());

		return ((target * speed / distance) - _vehicle->getVelocity());
	}
	return Vector2D();
}

Vector2D SteeringBehaviorGroup::pursuit(const Vehicle* target)
{
	Vector2D targetDirection = target->getPosition() - _vehicle->getPosition();
	const double relativeHeading = _vehicle->getHeading().dotProduct(target->getHeading());

	if((targetDirection.dotProduct(_vehicle->getHeading()) > 0) && (relativeHeading < -0.95))
		return seek(target->getPosition());

	return seek(target->getPosition() + target->getVelocity() * (targetDirection.magnitude() / (_vehicle->getMaximumSpeed() + target->getVelocity().magnitude())));
}

Vector2D SteeringBehaviorGroup::offsetPursuit(const Vehicle* target, const Vector2D offset)
{
	const Vector2D offsetPosition = target->getPosition() + pointToWorldSpace(
		offset,
		target->getHeading(),
		target->getSide(),
		target->getPosition());

	Vector2D toOffset = offsetPosition - _vehicle->getPosition();

	const double lookAheadTime = offset.magnitude() / (_vehicle->getMaximumSpeed() + target->getVelocity().magnitude());

	return arrive(offsetPosition + target->getVelocity() * lookAheadTime, 3);
}

Vector2D SteeringBehaviorGroup::evade(const Vehicle* target)
{
	const double fleeDistance = 100.0 * 100.0;
	if (Vector2D::distanceSqrt(_vehicle->getPosition(), target->getPosition()) > fleeDistance)
		return Vector2D();

	Vector2D targetDirection = target->getPosition() - _vehicle->getPosition();

	return flee(target->getPosition() + target->getVelocity() * (targetDirection.magnitude() / (_vehicle->getMaximumSpeed() + target->getVelocity().magnitude())));
}

Vector2D SteeringBehaviorGroup::wander()
{
	_wanderTarget += Vector2D(
		randomClamped() * _wanderJitter,
		randomClamped() * _wanderJitter);

	_wanderTarget.normalize();
	_wanderTarget *= _wanderRadius;

	Vector2D targetLocal = _wanderTarget + Vector2D(_wanderDistance, 0);
	Vector2D targetWorld = pointToWorldSpace(
		targetLocal,
		_vehicle->getHeading(),
		_vehicle->getSide(),
		_vehicle->getPosition());

	Vector2D point = targetWorld - _vehicle->getPosition();

	SDL_SetRenderDrawColor(
		_renderer,
		255,
		0,
		0,
		255);
	SDL_RenderDrawPoint(
		_renderer,
		_vehicle->getPosition().x + point.x,
		_vehicle->getPosition().y + point.y);

	return point;
}

//Vector2D SteeringBehaviorGroup::wander()
//{
//	_wanderAngle += randomClamped() * _wanderJitter;
//
//	Vector2D vehiclePosition = _vehicle->getPosition();
//	Vector2D vehicleWanderDistance = _vehicle->getHeading() * _wanderDistance;
//
//	Vector2D vehicleWanderOffset = Vector2D(
//		static_cast<float>(_wanderRadius * sin(_wanderAngle)),
//		static_cast<float>(_wanderRadius * cos(_wanderAngle))
//	);
//	
//	const Vector2D point = vehiclePosition + vehicleWanderDistance + vehicleWanderOffset;
//
//	SDL_SetRenderDrawColor(
//		_renderer,
//		255,
//		0,
//		0,
//		255
//	);
//	SDL_RenderDrawPoint(
//		_renderer,
//		point.x,
//		point.y
//	);
//
//	return seek(point);
//}

Vector2D SteeringBehaviorGroup::hide(const Vehicle* target, const std::vector<Obstacle*>& obstacles)
{
	double distanceToClosest = DBL_MAX;
	Vector2D bestHidingSpot;

	for (auto currentObject = obstacles.cbegin(); currentObject != obstacles.cend(); ++currentObject)
	{
		Vector2D hidingSpot = findHidingPosition(
			(*currentObject)->getPosition(),
			(*currentObject)->getBoundingRadius(),
			target->getPosition());

		double distance = Vector2D::distanceSqrt(hidingSpot, _vehicle->getPosition());

		if (distance < distanceToClosest)
		{
			distanceToClosest = distance;
			bestHidingSpot = hidingSpot;
		}
	}

	if (distanceToClosest == DBL_MAX)
		return evade(target);
	return arrive(bestHidingSpot, 3);
}

Vector2D SteeringBehaviorGroup::explore(const Vector2D& target)
{
	const Vector2D offset = Vector2D(
		static_cast<float>(sin(_exploreRadius * 0.3)),
		static_cast<float>(cos(_exploreRadius * 0.3)));

	Vector2D point = target + Vector2D::normalize(offset) * _exploreRadius;

	SDL_SetRenderDrawColor(
		_renderer,
		255,
		0,
		0,
		255
	);
	SDL_RenderDrawPoint(
		_renderer,
		point.x,
		point.y
	);

	Environment* environment = Environment::GetInstance();
	if (environment->isEdgeObstructed(target, point))
		_exploreRadius = 0.0f;
	if (Vector2D::distance(_vehicle->getPosition(), point) < 50)
		_exploreRadius += _exploreIncement;

	return arrive(point, 3);
}

Vector2D SteeringBehaviorGroup::followPath(Path* path, const double& distance)
{
	if (Vector2D::distanceSqrt(path->getCurrentWaypoint(), _vehicle->getPosition()) < distance)
		path->gotoNextWaypoint();

	if (!path->finished())
		return arrive(path->getCurrentWaypoint(), 1);
	return arrive(path->getCurrentWaypoint(), 3);
}

Vector2D SteeringBehaviorGroup::obstacleAvoidance(const std::vector<Obstacle*>& obstacles)
{
	_boxLength = _boxMinLength +
		(_vehicle->getVelocity().magnitude() / _vehicle->getMaximumSpeed()) *
		_boxMinLength;

//	std::cout << _boxLength << std::endl;
	//tag all obstances within range

	BaseEntity* closestIntersectingObstacle = nullptr;
	Vector2D localPositionOfClosestObstacle;
	double distanceToClosestIntersectingObstacle = DBL_MAX;

	for(auto currentObject = obstacles.begin(); currentObject != obstacles.end(); ++currentObject)
	{
		const Vector2D localPosition = pointToLocalSpace(
			(*currentObject)->getPosition(),
			_vehicle->getHeading(),
			_vehicle->getSide(),
			_vehicle->getPosition());//todo: POINT TO LOCAL SPACE

		if(localPosition.x >= 0)
		{
			const double expandedRadius = (*currentObject)->getBoundingRadius() + _vehicle->getBoundingRadius();

			if(fabs(localPosition.y) < expandedRadius)
			{
				const double cX = localPosition.x;
				const double cY = localPosition.y;

				const double sqrtRadius = sqrt(expandedRadius * expandedRadius - cY * cY);
				double invertedSqrtRadius = cX - sqrtRadius;

				if(invertedSqrtRadius <= 0)
					invertedSqrtRadius = cX + sqrtRadius;
				
				if(invertedSqrtRadius < distanceToClosestIntersectingObstacle)
				{
					distanceToClosestIntersectingObstacle = invertedSqrtRadius;
					closestIntersectingObstacle = *currentObject;
					localPositionOfClosestObstacle = localPosition;
				}
			}
		}
	}

	Vector2D steeringForce;

	if(closestIntersectingObstacle)
	{
		const float brakingWeight = 0.2f;
		const float multiplier = 1.0f + (_boxLength - localPositionOfClosestObstacle.x) / _boxLength;
		
		//TESTING OUT OPERATIONS
//		steeringForce = (closestIntersectingObstacle->getBoundingRadius() - localPositionOfClosestObstacle) * brakingWeight;
		steeringForce = Vector2D(
			(closestIntersectingObstacle->getBoundingRadius() - localPositionOfClosestObstacle.x) * brakingWeight,
			(closestIntersectingObstacle->getBoundingRadius() - localPositionOfClosestObstacle.y) * multiplier);
	}

	//todo: TO WORLD SPACE
	return vectorToWorldSpace(
		steeringForce,
		_vehicle->getHeading(),
		_vehicle->getSide());
}

Vector2D SteeringBehaviorGroup::wallAvoidance(const std::vector<Wall*> walls)
{
	const Vector2D vehiclePostion = _vehicle->getPosition();
	Vector2D rays[3];
	rays[0] = vehiclePostion + _wallDetectionLength * _vehicle->getHeading();
	rays[1] = vehiclePostion + (_wallDetectionLength / 2.0f) 
		* Vector2D::rotateAroundOrigin(_vehicle->getHeading(), 3.14159265359f * 1.75f);
	rays[2] = vehiclePostion + (_wallDetectionLength / 2.0f) 
		* Vector2D::rotateAroundOrigin(_vehicle->getHeading(), 3.14159265359f * 0.25f);

//	for(int i = 0; i < 3; ++i)
//	{
//		SDL_SetRenderDrawColor(_renderer, 205, 205, 205, 255);
//		SDL_RenderDrawLine(
//			_renderer,
//			vehiclePostion.x,
//			vehiclePostion.y,
//			rays[i].x,
//			rays[i].y);
//	}

	double distanceToWall = 0.0;
	double distanceToClosestWall = DBL_MAX;

	Wall* closestWall = nullptr;

	Vector2D steeringForce;
	Vector2D currentPoint;
	Vector2D closestPoint;

	for(unsigned int ray = 0; ray < 3; ++ray)
	{
		for(auto wall = walls.begin(); wall != walls.end(); ++wall)
		{
			if((*wall)->intersect(
				vehiclePostion,
				rays[ray],
				distanceToWall,
				currentPoint))
			{
				if(distanceToWall < distanceToClosestWall)
				{
//					std::cout << "Intersection happened" << std::endl;

					distanceToClosestWall = distanceToWall;
					closestPoint = currentPoint;
					closestWall = *wall;
				}
			}
		} // Next wall

		if (closestWall)
		{ 
			Vector2D overshoot = rays[ray] - closestPoint;

			steeringForce = closestWall->getNormal() * overshoot.magnitude(); //closestWall->getNormal() * ((rays[ray] - closestPoint).magnitude());
		}
	} // Next ray

	return steeringForce;
}

Vector2D SteeringBehaviorGroup::interpose(const Vehicle* targetAlpha, const Vehicle* targetBeta)
{
	Vector2D midPoint = (targetAlpha->getPosition() + targetBeta->getPosition()) / 2.0f;

	double timeToMidPoint = Vector2D::distance(_vehicle->getPosition(), midPoint) / _vehicle->getMaximumSpeed();

	Vector2D positionAlpha = targetAlpha->getPosition() + targetAlpha->getVelocity() * timeToMidPoint;
	Vector2D positionBeta = targetBeta->getPosition() + targetBeta->getVelocity() * timeToMidPoint;

	return arrive((positionAlpha + positionBeta) / 2.0f, 3);

}

Vector2D SteeringBehaviorGroup::seperation(const std::list<Vehicle*>& neighbours)
{
	Vector2D steeringForce;

	for(auto neighbour = neighbours.cbegin(); neighbour != neighbours.cend(); ++neighbour)
	{
		Vector2D toAgent = (_vehicle->getPosition()) - ((*neighbour)->getPosition());
		const float magnitude = toAgent.magnitude();

		if(magnitude > 0)
			steeringForce += Vector2D::normalize(toAgent) / magnitude;
	}

	return steeringForce;
}

Vector2D SteeringBehaviorGroup::alignment(const std::list<Vehicle*>& neighbours)
{
	Vector2D averageHeading = (*neighbours.cbegin())->getHeading();
	int neighbourCount = 0;

	for (auto neighbour = ++neighbours.cbegin(); neighbour != neighbours.cend(); ++neighbour)
		averageHeading *= (*neighbour)->getHeading();

	return averageHeading - _vehicle->getHeading();
}

Vector2D SteeringBehaviorGroup::cohesion(const std::list<Vehicle*>& neighbours)
{
	Vector2D steeringForce;
	Vector2D centerOfMass;

	for (auto neighbour = neighbours.cbegin(); neighbour != neighbours.cend(); ++neighbour)
		centerOfMass += (*neighbour)->getPosition();
	
	if(!neighbours.empty())
	{
		centerOfMass /= static_cast<double>(neighbours.size());
		steeringForce = seek(centerOfMass);
	}

	return steeringForce;
}

bool SteeringBehaviorGroup::accumulateForce(Vector2D& totalForce, const Vector2D& addedForce)
{
	double currentMagnitude = totalForce.magnitude();
	double remainingMagnitude = _vehicle->getMaximumForce() - currentMagnitude;

	if (remainingMagnitude <= 0.0)
		return false;

	double addedMagnitude = addedForce.magnitude();

	if (addedMagnitude < remainingMagnitude)
		totalForce += addedForce;
	else
		totalForce += (Vector2D::normalize(addedForce) * remainingMagnitude);
	return true;
}

Vector2D SteeringBehaviorGroup::calculate()
{
	Vector2D acceleration = Vector2D(0.0f, 0.0f);

	if (_seekActive)
		acceleration += seek(_target);
	if (_fleeActive)
		acceleration += flee(_target);
	if (_arriveActive)
		acceleration += arrive(_target, 3);
	if (_pursuitActive)
		acceleration += pursuit(_vehicleAgentAlpha);
	if (_pursuitOffsetActive)
		acceleration += offsetPursuit(_vehicleAgentAlpha, _target);
	if (_evadeActive)
		acceleration += evade(_vehicleAgentAlpha);
	if (_wanderActive)
		acceleration += wander();
	if (_interposeActive)
		acceleration += interpose(_vehicleAgentAlpha, _vehicleAgentBeta);
	if (_hideActive)
		acceleration += hide(_vehicleAgentAlpha, _vehicle->getEnvironment()->getObstacles());
	if (_pathActive)
		acceleration += followPath(_path, 30);

	if(_separationActive || _alignmentActive || _cohesionActive)
	{
		const std::vector<Vehicle*> vehicles = _vehicle->getEnvironment()->getVehicles();

		const std::list<Vehicle*> neighbours = BaseEntity::tagNeighbors<Vehicle, const std::vector<Vehicle*>>(_vehicle, vehicles, 100.0);
		
		Vector2D groupAcceleration = Vector2D(0.0f, 0.0f);

		if(!neighbours.empty())
		{
			if (_separationActive)
				groupAcceleration += seperation(neighbours);
			if (_alignmentActive)
				groupAcceleration += alignment(neighbours);
			if (_cohesionActive)
				groupAcceleration += cohesion(neighbours);
		}
//		std::cout << groupAcceleration << std::endl;

		acceleration += groupAcceleration;
	}

	if (_obstacleActive)
		acceleration += obstacleAvoidance(_vehicle->getEnvironment()->getObstacles());
	if (_wallActive)
		acceleration += wallAvoidance(_vehicle->getEnvironment()->getWalls());

	return acceleration;
}

Vector2D SteeringBehaviorGroup::calculateWTRSwP()
{
	Vector2D accumulatedForce;
	Vector2D force;

	if (_wallActive)
	{
		force = wallAvoidance(_vehicle->getEnvironment()->getWalls()) * _wallMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_obstacleActive)
	{ 
		force = obstacleAvoidance(_vehicle->getEnvironment()->getObstacles()) * _obstacleMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_evadeActive)
	{
		force = evade(_vehicleAgentAlpha) * _evadeMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_separationActive || _alignmentActive || _cohesionActive)
	{
		const std::vector<Vehicle*> vehicles = _vehicle->getEnvironment()->getVehicles();
		const std::list<Vehicle*> neighbours = BaseEntity::tagNeighbors<Vehicle, const std::vector<Vehicle*>>(_vehicle, vehicles, 50.0);

		Vector2D groupForce = Vector2D(0.0f, 0.0f);

		if (!neighbours.empty())
		{
			if (_separationActive)
				groupForce += seperation(neighbours) * _separationMult;
			if (_alignmentActive)
				groupForce += alignment(neighbours) * _alignmentMult;
			if (_cohesionActive)
				groupForce += cohesion(neighbours) * _cohesionMult;
		}
		
		if (!accumulateForce(accumulatedForce, groupForce))
			return accumulatedForce;
	}
	if(_exploreActive)
	{
		force = explore(_target) * _exploreMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_seekActive)
	{
		force = seek(_target) * _seekMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_fleeActive)
	{
		force = flee(_target) * _fleeMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_arriveActive)
	{
		force = arrive(_target, 3) * _arriveMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_pursuitActive)
	{
		force = pursuit(_vehicleAgentAlpha) * _pursuitMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_pursuitOffsetActive)
	{
		force = offsetPursuit(_vehicleAgentAlpha, _target) * _pursuitOffsetMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_wanderActive)
	{
		force = wander() * _wanderMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_interposeActive)
	{
		force = interpose(_vehicleAgentAlpha, _vehicleAgentBeta) * _interposeMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_hideActive)
	{
		force = hide(_vehicleAgentAlpha, _vehicle->getEnvironment()->getObstacles()) * _hideMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	if (_pathActive)
	{
		force = followPath(_path, 30) * _pathMult;

		if (!accumulateForce(accumulatedForce, force))
			return accumulatedForce;
	}
	
	return accumulatedForce;
}

Vector2D SteeringBehaviorGroup::getForwardComponent()
{
	return _vehicle->getHeading();
}

Vector2D SteeringBehaviorGroup::getSideComponent()
{
	return _vehicle->getSide();
}

void SteeringBehaviorGroup::setTarget(Vector2D target)
{
	_target = target;
}

void SteeringBehaviorGroup::setTargetAgentAlpha(Vehicle* target)
{
	_vehicleAgentAlpha = target;
}

void SteeringBehaviorGroup::setTargetAgentBeta(Vehicle* target)
{
	_vehicleAgentBeta = target;
}

void SteeringBehaviorGroup::setSeekActive(Vector2D target, float priority)
{
	setTarget(target);
	_seekActive = true;
	_seekMult = priority;
}

void SteeringBehaviorGroup::setFleeActive(Vector2D target, float priority)
{
	setTarget(target);
	_fleeActive = true;
	_fleeMult = priority;
}

void SteeringBehaviorGroup::setArriveActive(Vector2D target, float priority)
{
	setTarget(target);
	_arriveActive = true;
	_arriveMult = priority;
}

void SteeringBehaviorGroup::setPursuitActive(Vehicle* targetAgent, float priority)
{
	setTargetAgentAlpha(targetAgent);
	_pursuitActive = true;
	_pursuitMult = priority;
}

void SteeringBehaviorGroup::setOffsetPursuitActive(Vehicle* targetAgent, const Vector2D& target, float priority)
{
	setTarget(target);
	setTargetAgentAlpha(targetAgent);
	_pursuitOffsetActive = true;
	_pursuitOffsetMult = priority;
}

void SteeringBehaviorGroup::setEvadeActive(Vehicle* targetAgent, float priority)
{
	setTargetAgentAlpha(targetAgent);
	_evadeActive = true;
	_evadeMult = priority;
}

void SteeringBehaviorGroup::setWanderActive(float priority)
{
	_wanderActive = true;
	_wanderMult = priority;
}

void SteeringBehaviorGroup::setObjectAdvoidanceActive(float priority)
{
	_obstacleActive = true;
	_obstacleMult = priority;
}

void SteeringBehaviorGroup::setWallAvoidanceActive(float priority)
{
	_wallActive = true;
	_wallMult = priority;
}

void SteeringBehaviorGroup::setHideActive(Vehicle* vehicle, float priority)
{
	_vehicleAgentAlpha = vehicle;
	_hideActive = true;
	_hideMult = priority;
}

void SteeringBehaviorGroup::setInterposeActive(Vehicle* targetAlpha, Vehicle* targetBeta, float priority)
{
	_vehicleAgentAlpha = targetAlpha;
	_vehicleAgentBeta = targetBeta;
	_interposeActive = true;
	_hideMult = priority;
}

void SteeringBehaviorGroup::setPathFollowingActive(Path* path, float priority)
{
	_path = path;
	_pathActive = true;
	_pathMult = priority;
}

void SteeringBehaviorGroup::setSeperationActive(float priority)
{
	_separationActive = true;
	_separationMult = priority;
}

void SteeringBehaviorGroup::setAlignmentActive(float priority)
{
	_alignmentActive = true;
	_alignmentMult = priority;
}

void SteeringBehaviorGroup::setCohesionActive(float priority)
{
	_cohesionActive = true;
	_cohesionMult = priority;
}

void SteeringBehaviorGroup::setExploreActive(Vector2D target, float priority)
{
	_target = target;
	_exploreActive = true;
	_exploreMult = priority;
}


void SteeringBehaviorGroup::setSeekUnactive()
{
	_seekActive = false;
}

void SteeringBehaviorGroup::setFleeUnactive()
{
	_fleeActive = false;
}

void SteeringBehaviorGroup::setArriveUnactive()
{
	_arriveActive = false;
}

void SteeringBehaviorGroup::setPursuitUnactive()
{
	_pursuitActive = false;
}

void SteeringBehaviorGroup::setOffsetPursuitUnactive()
{
	_pursuitOffsetActive = false;
}

void SteeringBehaviorGroup::setEvadeUnactive()
{
	_evadeActive = false;
}

void SteeringBehaviorGroup::setWanderUnactive()
{
	_wanderActive = false;
}

void SteeringBehaviorGroup::setInterposeUnactive()
{
	_interposeActive = false;
}

void SteeringBehaviorGroup::setPathFollowingUnactive()
{
	_pathActive = false;
}

void SteeringBehaviorGroup::setSeperationUnactive()
{
	_separationActive = false;
}

void SteeringBehaviorGroup::setAlignmentUnactive()
{
	_alignmentActive = false;
}

void SteeringBehaviorGroup::setCohesionUnactive()
{
	_cohesionActive = false;
}

void SteeringBehaviorGroup::setExploreUnactive()
{
	_exploreActive = false;
}

void SteeringBehaviorGroup::setObjectAdvoidanceUnactive()
{
	_obstacleActive = false;
}

void SteeringBehaviorGroup::setWallAvoidanceUnactive()
{
	_wallActive = false;
}

void SteeringBehaviorGroup::setHideUnactive()
{
	_hideActive = false;
}