#include <stdlib.h>     /* srand, rand */
#include <iostream>

#include "Matrix.h"

#include "SDL.h"
#include "SDL_video.h"
#include <SDL_render.h>
#include <SDL_image.h>
#include "Vehicle.h"
#include "Guard.h"
#include "Path.h"
#include "Graph.h"
#include "TwoSidedEdge.h"
#include "DepthFirstGraphSearch.h"
#include "AStarGraphSearch.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = nullptr;
//SDL_Surface* gScreenSurface = nullptr;
SDL_Renderer* gRenderer = nullptr;
//SDL_Texture* gTexture = nullptr;

Environment environment;
Vehicle* vehicle;
Vehicle* vehicleAlpha;

int targetX = 400;
int targetY = 300;

bool loop = true;
Uint32 last = 0;
Uint32 delta = 0;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Linear algebra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == nullptr)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == nullptr)
			{
				std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
//				int imageFlags = IMG_INIT_JPG;
//				if(!(IMG_Init(imageFlags) & imageFlags))
//				{
//					success = false;
//				}
//				else
//				{
//					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//					//Get window surface
//					gScreenSurface = SDL_GetWindowSurface(gWindow);
//				}
			}
		}
	}

	return success;
}

void close()
{
//	SDL_DestroyTexture(gTexture);
//	gTexture = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

//	SDL_FreeSurface(gScreenSurface);
//	gScreenSurface = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	SDL_Quit();
}

void mouseRelease(SDL_MouseButtonEvent event)
{
	targetX = event.x;
	targetY = event.y;
//	vehicleAlpha->getSteering()->setSeekActive(Vector2D(event.x, event.y), 1.0f);
}

void keyPress(unsigned int key)
{
	if (key == 27)
	{
		SDL_Event sdlevent;
		sdlevent.type = SDL_QUIT;

		SDL_PushEvent(&sdlevent);
	}
}

int wmain(int argc, char* args[])
{
	if( !init())
		std::cout << "Failed to initialize" << std::endl;

	std::cout << "test123" << std::endl;

	int xOffset = 200;
	int yOffset = 200;

	int xSize = 30;
	int ySize = 30;

	int xCount = 10;
	int yCount = 10;

	Guard guard = Guard();
	Graph graph = Graph();

	int xPositionOld = 0;
	int yPositionOld = 0;

	std::vector<Node*> nodeVector;

	for(int yPosition = 0; yPosition < xCount; ++yPosition)
	{
		for (int xPosition = 0; xPosition < yCount; ++xPosition)
		{
			Node* node = new Node(Vector2D(xOffset + xPosition * xSize, yOffset + yPosition * ySize));
			node->setIndex(nodeVector.size());
			nodeVector.push_back(node);

			if (xPosition > xPositionOld)
			{
				int xIndex = yPosition * xCount + xPositionOld;
				Node* xPreviousNode = nodeVector[xIndex];

				Edge* edge = new TwoSidedEdge(xPreviousNode, node, 1.0f);
				xPreviousNode->addEdge(edge);
				node->addEdge(edge);
			}
			if (yPosition > yPositionOld)
			{
				int yIndex = yPositionOld * yCount + xPosition;
				Node* yPreviousNode = nodeVector[yIndex];

				Edge* edge = new TwoSidedEdge(yPreviousNode, node, 1.0f);
				yPreviousNode->addEdge(edge);
				node->addEdge(edge);
			}

			xPositionOld = xPosition;
		}

		yPositionOld = yPosition;
	}

	graph.setNodes(nodeVector);



//	GraphSearch* graphSearch = new DepthFirstGraphSearch(nodeVector[0], nodeVector[nodeVector.size() - 1]);
	GraphSearch* graphSearch = new AStarGraphSearch(nodeVector[0], nodeVector[nodeVector.size() - 1]);
	Path* foundPath = graph.findPath(graphSearch);

	Wall wallTop;
	wallTop.setPosition(Vector2D(100, 20));
	wallTop.setWallEnd(Vector2D(700, 20));
	wallTop.calculateNormals();

	Wall wallTopRight;
	wallTopRight.setPosition(Vector2D(700, 20));
	wallTopRight.setWallEnd(Vector2D(780, 100));
	wallTopRight.calculateNormals();

	Wall wallRight;
	wallRight.setPosition(Vector2D(780, 100));
	wallRight.setWallEnd(Vector2D(780, 500));
	wallRight.calculateNormals();

	Wall wallBottomRight;
	wallBottomRight.setPosition(Vector2D(780, 500));
	wallBottomRight.setWallEnd(Vector2D(700, 580));
	wallBottomRight.calculateNormals();

	Wall wallBottom;
	wallBottom.setPosition(Vector2D(700, 580));
	wallBottom.setWallEnd(Vector2D(100, 580));
	wallBottom.calculateNormals();

	Wall wallBottomLeft;
	wallBottomLeft.setPosition(Vector2D(100, 580));
	wallBottomLeft.setWallEnd(Vector2D(20, 500));
	wallBottomLeft.calculateNormals();

	Wall wallLeft;
	wallLeft.setPosition(Vector2D(20, 500));
	wallLeft.setWallEnd(Vector2D(20, 100));
	wallLeft.calculateNormals();

	Wall wallTopLeft;
	wallTopLeft.setPosition(Vector2D(20, 100));
	wallTopLeft.setWallEnd(Vector2D(100, 20));
	wallTopLeft.calculateNormals();

	environment.addWall(&wallTop);
	environment.addWall(&wallTopRight);
	environment.addWall(&wallRight);
	environment.addWall(&wallBottomRight);
	environment.addWall(&wallBottom);
	environment.addWall(&wallBottomLeft);
	environment.addWall(&wallLeft);
	environment.addWall(&wallTopLeft);



	Obstacle obstacle;
	obstacle.setPosition(Vector2D(400, 300));
//	Obstacle obstacle2;
//	obstacle2.setPosition(Vector2D(150, 150));
//	Obstacle obstacle3;
//	obstacle3.setPosition(Vector2D(650, 150));
//	Obstacle obstacle4;
//	obstacle4.setPosition(Vector2D(150, 450));
//	Obstacle obstacle5;
//	obstacle5.setPosition(Vector2D(650, 450));

	environment.addObstacle(&obstacle);
//	environment.addObstacle(&obstacle2);
//	environment.addObstacle(&obstacle3);
//	environment.addObstacle(&obstacle4);
//	environment.addObstacle(&obstacle5);



	vehicle = new Vehicle(&environment, gRenderer);
	vehicle->setPosition(Vector2D(400, 200));
	vehicle->setScale(Vector2D(2.0f, 2.0f));
	vehicle->setMaximumSpeed(100);
	vehicle->setMaximumForce(50.0);
	vehicle->setBoundingRadius(20);
	vehicle->getSteering()->setObjectAdvoidanceActive(1.0f);
	vehicle->getSteering()->setWallAvoidanceActive(50.0f);
	vehicle->getSteering()->setWanderActive(0.4f);
	environment.addVehicle(vehicle);

	vehicleAlpha = new Vehicle(&environment, gRenderer);
	vehicleAlpha->setPosition(Vector2D(600, 100));
	vehicleAlpha->setMaximumSpeed(100);
	vehicleAlpha->setMaximumForce(50.0);
	vehicleAlpha->setBoundingRadius(10);
	vehicleAlpha->getSteering()->setObjectAdvoidanceActive(1.0f);
	vehicleAlpha->getSteering()->setWallAvoidanceActive(1.0f);
//	vehicleAlpha->getSteering()->setHideActive(vehicle, 0.6f);
	environment.addVehicle(vehicleAlpha);

//	vehicleAlpha.getSteering()->setOffsetPursuitActive(&vehicle, Vector2D(25.0f, 40.0f));

	Path path = Path(true);
	path.addWaypoint(Vector2D(100, 100));
	path.addWaypoint(Vector2D(700, 100));
	path.addWaypoint(Vector2D(100, 500));
	path.addWaypoint(Vector2D(700, 500));
	path.begin();
//
	vehicleAlpha->getSteering()->setPathFollowingActive(&path, 1.0f);

	for(int i = 0; i < 100; ++i)
	{
		Vehicle* smallVehicle = new Vehicle(&environment, gRenderer);
		smallVehicle->setPosition(Vector2D(30 + rand() % 740 , 30 + rand() % 540));
		smallVehicle->setScale(Vector2D(0.5f, 0.5f));
		smallVehicle->setMaximumSpeed(100);
		smallVehicle->setMaximumForce(50.0);
		smallVehicle->setBoundingRadius(10);
		smallVehicle->getSteering()->setObjectAdvoidanceActive(1.0f);
		smallVehicle->getSteering()->setWallAvoidanceActive(50.0f);
		smallVehicle->getSteering()->setEvadeActive(vehicle, 5.0f);
		smallVehicle->getSteering()->setWanderActive(2.0f);
//		smallVehicle->getSteering()->setHideActive(vehicle, 1.0f);
		smallVehicle->getSteering()->setSeperationActive(50.0f);
		smallVehicle->getSteering()->setAlignmentActive(0.4f);
		smallVehicle->getSteering()->setCohesionActive(0.4f);
		environment.addVehicle(smallVehicle);
	}

//	vehicleAlpha.getSteering()->setTargetAgentAlpha();
//	vehicleAlpha.getSteering()->setTargetAgentBeta();
//	vehicleAlpha.getSteering()->setInterposeActive(vehicles[0], vehicles[1]);

	SDL_Event gEvent;

	while(loop)
	{
		guard.update();

		Uint32 now = SDL_GetTicks();
		if (now > last) 
		{
			delta = now - last;
			last = now;
		}

		while(SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT)
				loop = false;
			if (gEvent.type == SDL_MOUSEBUTTONUP)
				mouseRelease(gEvent.button);
			if (gEvent.type == SDL_KEYDOWN)
				keyPress(gEvent.key.keysym.sym);
		}

		/*
		 * Draw scene
		 */
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(gRenderer);

		/*
		 * Obstacles
		 */
		const std::vector<Obstacle*> obstacles = environment.getObstacles();
		for(int i = 0, il = obstacles.size(); i < il; ++i)
		{
			obstacles[i]->render(gRenderer);
		}

		/*
		 * Walls
		 */
		const std::vector<Wall*> walls = environment.getWalls();
		for (int i = 0, il = walls.size(); i < il; ++i)
		{
			walls[i]->render(gRenderer);
		}

		/*
		 * Active vehicle
		 */
//		vehicle.update(static_cast<float>(delta) / 1000);
//		vehicle.render(gRenderer);
		
		/*
		 * Alpha vehicle
		 */
//		vehicleAlpha.update(static_cast<float>(delta) / 1000);
//		vehicleAlpha.render(gRenderer);

		/*
		 * Wandering vehicles
		 */
		const std::vector<Vehicle*>& vehicles = environment.getVehicles();
		for (int i = 0, il = vehicles.size(); i < il; ++i)
		{
			vehicles[i]->update(static_cast<float>(delta) / 1000);
			vehicles[i]->render(gRenderer);
		}

		/*
		 * Draw Graph
		 */
		graph.render(gRenderer);

		/*
		 * Draw predefined path
		 */
//		path.render(gRenderer);

		/*
		 * Draw found path
		 */
		foundPath->render(gRenderer);

		SDL_RenderPresent(gRenderer);
		SDL_GL_SwapWindow(gWindow);
	}

	close();

	return -1;
}
