#include "Environment.h"
#include "Vehicle.h"

Environment::Environment()
{
	_stockpile = nullptr;
	_graph = nullptr;
	_graphSearch = nullptr;
}


Environment* Environment::_environment = 0;
Environment* Environment::GetInstance() {
	if (_environment == 0)
		_environment = new Environment();
	return _environment;
}


Environment::~Environment()
{
	delete _graph;
	delete _graphSearch;
}

void Environment::generateGraph()
{
	_graph = new Graph();
	_graph->generateGraph();
}

Path* Environment::findPath(const Vector2D& start, const Vector2D& end)
{
	Path* path = nullptr;
	if (_graph != nullptr)
	{
		delete _graphSearch;

		_graphSearch = new AStarGraphSearch();
		path = _graph->findPath(start, end, _graphSearch);
	}
	return path;
}


void Environment::render(SDL_Renderer* gRenderer, double delta)
{
	/*
	* Graph
	*/
	if(_graphRender)
	{
		_graph->render(gRenderer);

		if (_graphSearch != nullptr)
		{
			const std::map<unsigned, Edge*>& searchFrontier = _graphSearch->getSearchFrontier();

			for (const auto& edge : searchFrontier)
			{
				edge.second->setColor(220, 220, 255, 255);
				edge.second->render(gRenderer);
			}
		}
	}


	/*
	* Obstacles
	*/
	for (auto& obstacle : _obstacles)
	{
		obstacle->render(gRenderer);
	}

	/*
	* Walls
	*/
	for (auto& wall : _walls)
	{
		wall->render(gRenderer);
	}

	/*
	* Vehicles
	*/
	for (auto& vehicle : _vehicles)
	{
		vehicle->update(static_cast<float>(delta) / 1000);
		vehicle->render(gRenderer);
	}

	/*
	* Deposits
	*/
	for (auto& deposit : _deposits)
	{
		deposit->render(gRenderer);
	}

	/*
	* Deposits
	*/
	for (auto& food : _foods)
	{
		food->render(gRenderer);
	}

	/*
	* Stockpile
	*/
	if(_stockpile != nullptr)
		_stockpile->render(gRenderer);
}

bool Environment::rayIntersectsObstacle(Vector2D start, Vector2D end, Obstacle* obs)
{
	Vector2D d = end - start;
	Vector2D f = start - obs->getPosition();
	float r = obs->getRadius();

	float a = d.dotProduct(d);
	float b = 2 * f.dotProduct(d);
	float c = f.dotProduct(f) - r * r;

	float discriminant = b * b - 4 * a*c;
	if (discriminant < 0)
	{
		// no intersection
		return false;
	}
	else
	{
		// ray didn't totally miss sphere,
		// so there is a solution to
		// the equation.

		discriminant = sqrt(discriminant);

		// either solution may be on or off the ray so need to test both
		// t1 is always the smaller value, because BOTH discriminant and
		// a are nonnegative.
		float t1 = (-b - discriminant) / (2 * a);
		float t2 = (-b + discriminant) / (2 * a);

		// 3x HIT cases:
		//          -o->             --|-->  |            |  --|->
		// Impale(t1 hit,t2 hit), Poke(t1 hit,t2>1), ExitWound(t1<0, t2 hit), 

		// 3x MISS cases:
		//       ->  o                     o ->              | -> |
		// FallShort (t1>1,t2>1), Past (t1<0,t2<0), CompletelyInside(t1<0, t2>1)

		if (t1 >= 0 && t1 <= 1)
		{
			// t1 is the intersection, and it's closer than t2
			// (since t1 uses -b - discriminant)
			// Impale, Poke
			return true;
		}

		// here t1 didn't intersect so we are either started
		// inside the sphere or completely past it
		if (t2 >= 0 && t2 <= 1)
		{
			// ExitWound
			return true;
		}

		// no intn: FallShort, Past, CompletelyInside
		return false;
	}
}

bool Environment::isPathObstructed(Vector2D start, Vector2D end)
{
	for (auto iter = getObstacles().cbegin(); iter != getObstacles().cend(); ++iter) {
		if (rayIntersectsObstacle(start, end, (*iter)))
			return true;
	}
	return false;
}

bool Environment::isEdgeObstructed(const Vector2D& start, const Vector2D& end)
{
	if (isPointOutside(end))
		return true;

	for (auto iter : getObstacles())
	{
		if (rayIntersectsObstacle(start, end, iter))
			return true;
	}
	for (auto wall : _walls)
	{
		if (wall->intersectSimple(start, end))
			return true;
	}
	return false;
}

bool Environment::isPointOutside(const Vector2D& point) const
{
	return (point.x < 0 || point.x >= _width || point.y < 0 || point.y >= _height);
}

void Environment::setSize(int width, int height)
{
	_width = width;
	_height = height;
}

void Environment::addVehicle(Vehicle* vehicle)
{
	_vehicles.push_back(vehicle);
}

const std::vector<Vehicle*>& Environment::getVehicles() const
{
	return _vehicles;
}

void Environment::addObstacle(Obstacle* obstacle)
{
	_obstacles.push_back(obstacle);
}

const std::vector<Obstacle*>& Environment::getObstacles() const
{
	return _obstacles;
}

void Environment::addWall(Wall* wall)
{
	_walls.push_back(wall);
}

Deposit* Environment::getClosestAvailableDeposit(const Vector2D& target)
{
	double closestDistance = DBL_MAX;
	Deposit* closestDeposit = nullptr;

	for (auto deposit : _deposits)
	{
		if(!deposit->empty())
		{
			const double distance = Vector2D::distance(target, deposit->getPosition());

			if(closestDistance > distance)
			{
				closestDistance = distance;
				closestDeposit = deposit;
			}
		}
	}

	return closestDeposit;
}

Food* Environment::getClosestAvailableFood(const Vector2D& target)
{
	double closestDistance = DBL_MAX;
	Food* closestFood = nullptr;

	for (auto food : _foods)
	{
		const double distance = Vector2D::distance(target, food->getPosition());

		if (closestDistance > distance)
		{
			closestDistance = distance;
			closestFood = food;
		}
	}

	return closestFood;
}

void Environment::addDeposit(Deposit* deposit)
{
	_deposits.push_back(deposit);
}

const std::vector<Wall*>& Environment::getWalls() const
{
	return _walls;
}

void Environment::toggleGraphRendering()
{
	_graphRender = !_graphRender;
}

Graph* Environment::getGraph() const
{
	return _graph;
}

Vehicle * Environment::getClosestVehicle(Vehicle * vehicle)
{
	//loop through all vehicles
	//calc distance
	//compare to closest found
	//update closest found when necessary

	float closest = FLT_MAX;
	Vehicle* closestVehicle = vehicle;
	for (auto &Vehicle : _vehicles) {
		if (Vehicle != vehicle) {
			float dist = Vector2D::distance(vehicle->getPosition(), Vehicle->getPosition());
			if (dist < closest) {
				closest = dist;
				closestVehicle = Vehicle;
			}
		}
	}

	return closestVehicle;
}

void Environment::addStockpile(Stockpile* stockpile)
{
	_stockpile = stockpile;
}

Stockpile* Environment::getStockpile()
{
	return _stockpile;
}

void Environment::addFood(Food* food)
{
	_foods.push_back(food);
}
