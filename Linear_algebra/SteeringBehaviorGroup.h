#ifndef STEERINGBEHAVIORGROUP_H
#define STEERINGBEHAVIORGROUP_H
#pragma once

#include "Vehicle.h"
#include "Vector2D.h"
#include "Matrix.h"
#include <iostream>
#include "Wall.h"
#include "Path.h"

class Vehicle;

class SteeringBehaviorGroup
{
private:
	SDL_Renderer * _renderer;

	bool _seekActive = false;
	bool _fleeActive = false;
	bool _arriveActive = false;
	bool _pursuitActive = false;
	bool _evadeActive = false;
	bool _wanderActive = false;
	bool _obstacleActive = false;
	bool _wallActive = false;
	bool _interposeActive = false;
	bool _hideActive = false;
	bool _pathActive = false;
	bool _pursuitOffsetActive = false;
	bool _separationActive = false;
	bool _alignmentActive = false;
	bool _cohesionActive = false;
	bool _exploreActive = false;

	float _seekMult = 1.0f;
	float _fleeMult = 1.0f;
	float _arriveMult = 1.0f;
	float _pursuitMult = 1.0f;
	float _evadeMult = 1.0f;
	float _wanderMult = 1.0f;
	float _obstacleMult = 1.0f;
	float _wallMult = 1.0f;
	float _interposeMult = 1.0f;
	float _hideMult = 1.0f;
	float _pathMult = 1.0f;
	float _pursuitOffsetMult = 1.0f;
	float _separationMult = 1.0f;
	float _alignmentMult = 1.0f;
	float _cohesionMult = 1.0f;
	float _exploreMult = 1.0f;

	float _exploreRadius = 0.0f;
	float _exploreIncement = 0.05f;

	double _wanderRadius	= 50;
	double _wanderDistance	= 75;
	double _wanderJitter	= 0.1 * 3.14159;
	double _wanderAngle		= 0.0;

	double _boxLength		= 0.0;
	double _boxMinLength	= 50.0;
	double _wallDetectionLength = 100.0;

	Vehicle* _vehicle = nullptr;
	Vehicle* _vehicleAgentAlpha = nullptr;
	Vehicle* _vehicleAgentBeta = nullptr;
	std::list<Vehicle*> _neighbours;

	Vector2D _target;
	Vector2D _wanderTarget;
	Path* _path;

	Vector2D pointToLocalSpace(const Vector2D& point, const Vector2D& heading, const Vector2D& side, const Vector2D& position);
	Vector2D vectorToWorldSpace(const Vector2D& vector, const Vector2D& heading, const Vector2D& side);
	Vector2D findHidingPosition(const Vector2D& position, double, const Vector2D& target);
	Vector2D pointToWorldSpace(const Vector2D& point, const Vector2D& heading, const Vector2D& side, const Vector2D& position);
	double min(const double value1, const double value2) const;
	double turnAroundTime(const Vehicle* agent, Vector2D target);

	Vector2D seek(const Vector2D& input);
	Vector2D flee(const Vector2D& input);
	Vector2D arrive(const Vector2D& input, double deceleration);
	Vector2D pursuit(const Vehicle* target);
	Vector2D offsetPursuit(const Vehicle* target, Vector2D);
	Vector2D evade(const Vehicle* target);
	Vector2D wander();
	Vector2D obstacleAvoidance(const std::vector<Obstacle*>& obstacles);
	Vector2D wallAvoidance(std::vector<Wall*> walls);
	Vector2D interpose(const Vehicle* targetAlpha, const Vehicle* targetBeta);
	Vector2D seperation(const std::list<Vehicle*>& neighbours);
	Vector2D alignment(const std::list<Vehicle*>& neighbours);
	Vector2D cohesion(const std::list<Vehicle*>& neighbours);
	bool accumulateForce(Vector2D& totalForce, const Vector2D& addedForce);
	Vector2D hide(const Vehicle* target, const std::vector<Obstacle*>& obstacles);
	Vector2D explore(const Vector2D& target);
	Vector2D followPath(Path* path, const double& distance);
public:
	SteeringBehaviorGroup(Vehicle* vehicle, SDL_Renderer* renderer);
	~SteeringBehaviorGroup();
	double randomFloat() const;
	double randomClamped() const;
	Vector2D calculate();
	Vector2D calculateWTRSwP();
	Vector2D getForwardComponent();
	Vector2D getSideComponent();
	void setTarget(Vector2D target);
	void setTargetAgentAlpha(Vehicle* target);
	void setTargetAgentBeta(Vehicle* target);
	void setSeekActive(Vector2D target, float priority);
	void setFleeActive(Vector2D target, float priority);
	void setArriveActive(Vector2D target, float priority);
	void setPursuitActive(Vehicle* targetAgent, float priority);
	void setOffsetPursuitActive(Vehicle* targetAgent, const Vector2D& target, float priority);
	void setEvadeActive(Vehicle* targetAgent, float priority);
	void setWanderActive(float priority);
	void setInterposeActive(Vehicle* targetAlpha, Vehicle* targetBeta, float priority);
	void setPathFollowingActive(Path* path, float priority);
	void setSeperationActive(float priority);
	void setAlignmentActive(float priority);
	void setCohesionActive(float priority);
	void setExploreActive(Vector2D target, float priority);
	void setObjectAdvoidanceActive(float priority);
	void setWallAvoidanceActive(float priority);
	void setHideActive(Vehicle* vehicle, float priority);
};

#endif