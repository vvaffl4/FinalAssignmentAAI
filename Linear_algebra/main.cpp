#include <stdlib.h>     /* srand, rand */
#include <iostream>

#include "Matrix.h"

#include "SDL.h"
#include "SDL_video.h"
#include <SDL_render.h>
#include "Vehicle.h"
#include "FuzzyLogicVehicle.h"
#include "Guard.h"
#include "Path.h"
#include "Graph.h"
#include "TwoSidedEdge.h"
#include "DepthFirstGraphSearch.h"
#include "AStarGraphSearch.h"
#include "VehicleGoalBehavior.h"
#include "Stockpile.h"
#include "Food.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = nullptr;
//SDL_Surface* gScreenSurface = nullptr;
SDL_Renderer* gRenderer = nullptr;
//SDL_Texture* gTexture = nullptr;

Environment* environment;
Vehicle* vehicle;
Vehicle* vehicleAlpha;
Vehicle* vehicleExplore;
Vehicle* fuzzyLogicVehicle;
Path* precisePath;

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

	Path* foundPath = environment->findPath(vehicleAlpha->getPosition(), Vector2D(targetX, targetY));

	//	Path* roughPath = foundPath->smoothPath(Path::Precise);
	precisePath = foundPath->smoothPath(Path::Rough);
	precisePath->setRepeat(true);

	delete foundPath;

	precisePath->begin();
	vehicleAlpha->getSteering()->setPathFollowingActive(precisePath, 1.0f);
}

void quit()
{
	SDL_Event sdlevent;
	sdlevent.type = SDL_QUIT;

	SDL_PushEvent(&sdlevent);
}

void keyPress(unsigned int key)
{
	switch(key)
	{
	case 27:	quit();									break;
	case 103:	environment->toggleGraphRendering();	break;
	default:											break;
	}
}

int wmain(int argc, char* args[])
{
	if( !init())
		std::cout << "Failed to initialize" << std::endl;

	Guard guard = Guard();


	/*////////////////////////
	* START SETUP ENVIRONMENT
	*////////////////////////

	environment = Environment::GetInstance();
	environment->setSize(800, 600);

	Deposit* depositTopLeft = new Deposit(200);
	depositTopLeft->setColor(200, 200, 0, 255);
	depositTopLeft->setPosition(Vector2D(150, 150));
	Deposit* depositTopRight = new Deposit(200);
	depositTopRight->setColor(200, 200, 0, 255);
	depositTopRight->setPosition(Vector2D(650, 150));
	Deposit* depositBottom = new Deposit(200);
	depositBottom->setColor(200, 200, 0, 255);
	depositBottom->setPosition(Vector2D(400, 450));

	environment->addDeposit(depositTopLeft);
	environment->addDeposit(depositTopRight);
	environment->addDeposit(depositBottom);

	Food* foodRight = new Food();
	foodRight->setColor(200, 100, 100, 255);
	foodRight->setPosition(Vector2D(600, 300));
	Food* foodLeft = new Food();
	foodLeft->setColor(200, 100, 100, 255);
	foodLeft->setPosition(Vector2D(200, 300));

	environment->addFood(foodRight);
	environment->addFood(foodLeft);

	Stockpile* stockpile = new Stockpile();
	stockpile->setColor(0, 200, 200, 255);
	stockpile->setPosition(Vector2D(400, 100));

	environment->addStockpile(stockpile);

	Obstacle obstacle;
	obstacle.setPosition(Vector2D(400, 300));
	environment->addObstacle(&obstacle);


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

	environment->addWall(&wallTop);
	environment->addWall(&wallTopRight);
	environment->addWall(&wallRight);
	environment->addWall(&wallBottomRight);
	environment->addWall(&wallBottom);
	environment->addWall(&wallBottomLeft);
	environment->addWall(&wallLeft);
	environment->addWall(&wallTopLeft);

	environment->generateGraph();

	 /*////////////////////////
	 * START SETUP GRAPH
	 *////////////////////////


//	Graph* graph = environment->getGraph();

//	AStarGraphSearch* search = new AStarGraphSearch();
//	Path* errorPath = search->searchGraph(graph->getNodes()[0], graph->getNodes()[graph->getNodes().size() - 1]);
//	errorPath = errorPath->smoothPath(Path::Precise);

	Path* foundPath = environment->findPath(Vector2D(600, 550), Vector2D(200, 50));

	precisePath = foundPath->smoothPath(Path::Precise);
	precisePath->begin();

	delete foundPath;


   /*////////////////////////
	* START SETUP VEHICLES
	*////////////////////////

	vehicle = new Vehicle(environment, gRenderer);
	vehicle->setColor(255, 0, 0, 255);
	vehicle->setPosition(Vector2D(400, 200));
	vehicle->setScale(Vector2D(2.0f, 2.0f));
	vehicle->setMaximumSpeed(100);
	vehicle->setMaximumForce(50.0);
	vehicle->setBoundingRadius(20);
	vehicle->getSteering()->setObjectAdvoidanceActive(1.0f);
	vehicle->getSteering()->setWallAvoidanceActive(50.0f);
	vehicle->getSteering()->setWanderActive(0.4f);
	environment->addVehicle(vehicle);

	vehicleAlpha = new Vehicle(environment, gRenderer);
	vehicleAlpha->setColor(0, 0, 255, 255);
	vehicleAlpha->setPosition(Vector2D(600, 100));
	vehicleAlpha->setMaximumSpeed(100);
	vehicleAlpha->setMaximumForce(50.0);
	vehicleAlpha->setBoundingRadius(10);
	vehicleAlpha->getSteering()->setWallAvoidanceActive(50.0f);
//	vehicleAlpha->getSteering()->setObjectAdvoidanceActive(10.0f);
	vehicleAlpha->getSteering()->setPathFollowingActive(precisePath, 1.0f);
	environment->addVehicle(vehicleAlpha);


	vehicleExplore = new Vehicle(environment, gRenderer);
	vehicleExplore->setColor(200, 200, 0, 255);
	vehicleExplore->setPosition(Vector2D(600, 100));
	vehicleExplore->setMaximumSpeed(100);
	vehicleExplore->setMaximumForce(50.0);
	vehicleExplore->setBoundingRadius(10);
	vehicleExplore->getSteering()->setWallAvoidanceActive(50.0f);
//	vehicleExplore->getSteering()->setObjectAdvoidanceActive(10.0f);
	vehicleExplore->getSteering()->setExploreActive(Vector2D(200, 200), 1.0f);
//	vehicleExplore->getSteering()->setExploreUnactive();
	environment->addVehicle(vehicleExplore);

	Vehicle* vehicleGoal = new VehicleGoalBehavior(environment, gRenderer);
	vehicleGoal->setColor(200, 0, 200, 255);
	vehicleGoal->setPosition(Vector2D(400, 100));
	vehicleGoal->setMaximumSpeed(100);
	vehicleGoal->setMaximumForce(50.0);
	vehicleGoal->setBoundingRadius(10);
	vehicleGoal->getSteering()->setWallAvoidanceActive(50.0f);
	environment->addVehicle(vehicleGoal);

	for(int i = 0; i < 100; ++i)
	{
		Vehicle* smallVehicle = new Vehicle(environment, gRenderer);
		smallVehicle->setColor(0, 200, 0, 255);
		smallVehicle->setPosition(Vector2D(static_cast<float>(30 + rand() % 740), static_cast<float>(30 + rand() % 540)));
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
		environment->addVehicle(smallVehicle);
	}

	fuzzyLogicVehicle = new FuzzyLogicVehicle(environment, gRenderer);
	fuzzyLogicVehicle->setPosition(Vector2D(100, 100));
	fuzzyLogicVehicle->setMaximumSpeed(80);
	fuzzyLogicVehicle->setMaximumForce(40);
	fuzzyLogicVehicle->setScale(Vector2D(1.5f, 1.25f));
	fuzzyLogicVehicle->setBoundingRadius(10);
	fuzzyLogicVehicle->getSteering()->setSeekActive(environment->getClosestVehicle(fuzzyLogicVehicle)->getPosition(), 1.0f);
	environment->addVehicle(fuzzyLogicVehicle);

	/*////////////////////////
	* FUZZY LOGIC SETUP
	//////////////////////////*/

	//this happens in FuzzyLogicVehicle

	/*////////////////////////
	* EVENT AND RENDER LOOP
	*////////////////////////

	SDL_Event gEvent;

	while(loop)
	{

		const Uint32 now = SDL_GetTicks();
		if (now > last) 
		{
			delta = now - last;
			last = now;
		}

		guard.update(delta);

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

		environment->render(gRenderer, delta);

//
//		/*
//		 * Draw Graph
//		 */
//		graph->render(gRenderer);

		/*
		 * Draw predefined path
		 */
//		path.render(gRenderer);

		/*
		 * Draw found path
		 */
//		foundPath->render(gRenderer);
		//precisePath->render(gRenderer);
//		errorPath->render(gRenderer);
//		roughPath->render(gRenderer);

		SDL_RenderPresent(gRenderer);
		SDL_GL_SwapWindow(gWindow);
	}

	close();

	return -1;
}
