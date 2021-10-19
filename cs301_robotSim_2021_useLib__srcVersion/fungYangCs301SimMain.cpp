//======================================================================
//Author: 
//Mr. Fung Yang
//Senior Technician Engineer Research and Design,
//Robotics and Control system signal processing Labs,
//Department of Electrical, Computer and Software Engineering,
//The University of Auckland.
//
//Written for teaching design course Compsys301 in ECSE department of UOA.
//
//This example program uses the pacman robot simulation library written by Mr. Fung Yang.
//
//Date 2012~2020
//=======================================================================

#include "mainFungGLAppEngin.h" //a must
#include "mazeGen.h" //just include to use random number generation function
#include <vector>
#include <iostream>
#include "highPerformanceTimer.h"//just to include if timer function is required by user.
#include "Astar_Header.h"
#include <stdio.h>
#include <fstream>

using namespace std;

//{------------------------------
//these global variables must be defined here with no modification.
float virtualCarLinearSpeed;
float virtualCarAngularSpeed;
float currentCarAngle;
float currentCarPosCoord_X, currentCarPosCoord_Y;

int sensorPopulationAlgorithmID;
float sensorSeparation;
float num_sensors;
extern int maxDarkDefValueTH;

vector<int> virtualCarSensorStates;
vector<ghostInfoPack> ghostInfoPackList;
highPerformanceTimer myTimer, movementTimer;


// Our Function prototypes
void myMapRead(void);								// Read map from map.txt file
void readFoodList(void);							// Read food list from foodlist.txt
void getEmptySpotLocations();						// Find all available locations on map
void visitAllSpots(Pair src);						// Getting directions to empty all available locations on map
vector<pPair> getDirectionsFromFoodParticles(const array<array<int, COL>, ROW>& map, vector<Pair> foodList, Pair src);		//Getting directions between start and food parcels.


// Our global variables
array<array<int, COL>, ROW> map = { {} };			// The map
vector<pPair> directions;							// Vector that stores all the directions.
vector<Pair> foodList, emptySpots;					// ...
int currentmove;									// The direction currently being moved in.
int futuremove;										// The direction that will be moved in next.
int index = 0;										// Index value to be used in directions array.
int targetTime = 0;									// Time value to be used as reference to sensor check when travelling straight
int turningLockTimer = 0;							// Timer to be used as reference to sensor check when turning
int turningLock = 0;								// Lock to be applied when rotating 90 degrees
int turningAroundTimer = 0;							// Lock to be applied when rotating 180 degrees
int SensorOI = 10;									// Sensor Of Interest. Index to be used when checking sensors
int init = 0;										// Inital variable to delay start
Pair src;											// Source point (ROW, COL). Defined in main()
int journeyComplete = 0;							// Variable that is set when journey is complete
int selectedLevel;									// Variable that dictacts what level is active. This is set in main()
int prevmove;										// The direction that the robot starts facing. This is set in main()
float estimatedXPos, estimatedYPos, estimatedAngle;	// Use of odometry to estimate the position of the car in the maze.



// Provided helper function
void setVirtualCarSpeed(float linearSpeed, float angularSpeed) {
	virtualCarLinearSpeed = linearSpeed;
	virtualCarAngularSpeed = angularSpeed;
}

//The Only TWO functions Students need to modify to add their own sensor guided
//path following control and Map path search calculations.
//{=================================================
float virtualCarLinearSpeed_seed;
float virtualCarAngularSpeed_seed;

float virtualCarLinearSpeedFloor;
float currentCarPosFloor_X, currentCarPosFloor_Y;
double distanceTravelled = 0.0;							//Variable to track distance travelled by Robot.

// Initialise function. Runs once at the beginning
int virtualCarInit() {

	sensorPopulationAlgorithmID = 2;
	num_sensors = 6;
	sensorSeparation = 0.1;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//variables below can be initializes in config file,
	//or you can uncomment them to override config file settings.
	//----------------------------------------------
	//virtualCarLinearSpeedFloor = 130;//mm
	//currentCarPosFloor_X = 2000;//mm
	//currentCarPosFloor_Y = 1000;//mm
	//virtualCarAngularSpeed_seed = 40;//degree
	//maxDarkDefValueTH = 20;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// Depending on the defined value of prevmode at the start (defined in main), intialise the direction the robot is facing. 
	if (prevmove == UP) {
	currentCarAngle = 90;
	estimatedAngle = 90;
	} else if (prevmove == LEFT) {
	currentCarAngle = 0;
	estimatedAngle = 0;
	} else if (prevmove == DOWN) {
	currentCarAngle = 270;
	estimatedAngle = 270;
	} else {
	currentCarAngle = 180;
	estimatedAngle = 180;
	}

	myMapRead();						// Read the map.txt file
	readFoodList();						// Read the foodlist.txt file

	//Calling A* algorithm
	if (selectedLevel == 1) {

		printf("Level one has been selected");
		getEmptySpotLocations();
		visitAllSpots(src);
		printf("Printing out directions to travel everywhere\n");

		// Printing directions
		for (auto& direction : directions) {
			cout << direction.first;
		}
	} else if (selectedLevel == 2) {
		printf("\nLevel two has been selected\n");
		directions = getDirectionsFromFoodParticles(map, foodList, src);

		printf("\n Printing out the directions between food particles\n");
		//Printing out directions to get to destination
		for (auto& direction : directions) {
			printf("%s, ", direction.first.c_str());
		}
	}

	virtualCarLinearSpeed_seed = virtualCarLinearSpeedFloor * floorToCoordScaleFactor;//coord

	// Establish where the car begins on the map.
	currentCarPosFloor_X = cellToFloorX(src.first);
	currentCarPosFloor_Y = cellToFloorY(src.second);
	currentCarPosCoord_X = floorToCoordX(currentCarPosFloor_X);
	currentCarPosCoord_Y = floorToCoordY(currentCarPosFloor_Y);
	myTimer.resetTimer();
	movementTimer.resetTimer();

	// Establish starting position
	estimatedYPos = currentCarPosCoord_Y;
	estimatedXPos = currentCarPosCoord_X;

	return 1;
}



//Main function to update car position
int virtualCarUpdate() {

	vector<pPair> updatedDirections;

	// Provides a 1-second buffer before first moving
	if (myTimer.getTimer() < 1 && init == 0) {
		setVirtualCarSpeed(0.0, 0.0);
	} else {
		init = 1;
	}

	if (journeyComplete == 1) {							// If you have arrived at destination, stop car, and enter while(1) loop
		setVirtualCarSpeed(0.0, 0.0);
		printf("Car has arrived at destination\n");
		while (1);
	} else if (index > directions.size()) {				//Still have 1 more move to make
		setVirtualCarSpeed(0.6, 0.0);
		journeyComplete = 1;
	} else if (init == 1) {
		if (virtualCarSensorStates[SensorOI] == 0 || SensorOI == 10) {		// If the sensor of interest is under light OR sensor of interest value is dummy value
			if (targetTime > (myTimer.getTimer())) {						// While car has not finished straight path (length of more than 1 cell)

				// Check for front-side sensors to help adjust direction
				if (virtualCarSensorStates[0] == 0) {						// If back-left sensor goes off, adjust left	
					setVirtualCarSpeed(0.6, 25.0);
				}
				else if (virtualCarSensorStates[1] == 0) {				// If back-right sensore goes off, adjust right.
					setVirtualCarSpeed(0.6, -25.0);
				}
			}
			else {

				// Through the use of odometry, check if the car is where it is supposed to be

				// First compare estimated X position to X position outlined in directions vector
				if (coordToCellX(estimatedXPos) != directions[index].second.second) {
					if ((coordToCellX(estimatedXPos) != directions[index].second.second - 1)){
						if (coordToCellX(estimatedXPos) != directions[index].second.second + 1) {							
							if (index != directions.size()) {					//Covers edge case of last position
								//Calculate shortest distance from current position to next position in original directions list. Then insert this into directions list
								updatedDirections = aStarSearch(map, make_pair(coordToCellY(estimatedYPos), coordToCellX(estimatedXPos)), directions[index].second);
								int i = 0;
								while (i < updatedDirections.size() - 1) {
									directions.insert(directions.begin() + index - 1, updatedDirections[i]);
									i++;
								}
							}
						}
					}
				}

				// Then compare estimated Y position to Y position outlined in directions vector
				if (coordToCellY(estimatedYPos) != directions[index].second.first) {
					if (coordToCellY(estimatedYPos) != directions[index].second.first + 1){
						if (coordToCellY(estimatedYPos) != directions[index].second.first - 1) {
							if (index != directions.size()) {					//Covers edge case of last position 
								//Calculate shortest distance from current position to next position in original directions list. Then insert this into directions list
								updatedDirections = aStarSearch(map, make_pair(coordToCellY(estimatedYPos), coordToCellX(estimatedXPos)), directions[index].second);
								int i = 0;
								while (i < updatedDirections.size() - 1) {
									directions.insert(directions.begin() + index - 1, updatedDirections[i]);
									i++;
								}
							}
						}
					}
				}
				targetTime = 0;							// Reset targetTime as it is not currently needed
				SensorOI = 10;							// Set sensor of interest to dummy value
				// Retrieving the following move
				if (directions[index].first == "U") {
					currentmove = UP;
				}

				if (directions[index].first == "R") {
					currentmove = RIGHT;
				}

				if (directions[index].first == "D") {
					currentmove = DOWN;
				}

				if (directions[index].first == "L") {
					currentmove = LEFT;
				}

				if ((currentmove == prevmove + 1) || (currentmove == UP && prevmove == LEFT)) {      // If car needs to rotate 90 degrees clockwise
					if (turningLockTimer == 0) {
						turningLockTimer = 1;
						myTimer.resetTimer();
					}
					if (myTimer.getTimer() > 0.8 && virtualCarSensorStates[3] == 0) {           // Rotate until sensor is active AND sufficient time has passed
						turningLock = 0;
						turningLockTimer = 0;
					} else {
						turningLock = 1;
						setVirtualCarSpeed(0.0, -45);
					}
				} else if ((currentmove == prevmove + 2) || (currentmove == UP && prevmove == DOWN) || (currentmove == RIGHT && prevmove == LEFT)) {		// Rotate 180 degrees
					turningLock = 1;
					if (turningAroundTimer == 0) {
						myTimer.resetTimer();
						turningAroundTimer = 1;
					} else if (myTimer.getTimer() < 1.2 && turningAroundTimer == 1) {
						setVirtualCarSpeed(0.6, 0.0);
					} else {
						turningAroundTimer = 2;
						if (turningLockTimer == 0) {
							turningLockTimer = 1;
							myTimer.resetTimer();
						}
						if (myTimer.getTimer() > 3.6 && virtualCarSensorStates[3] == 0) {		// Rotate until sensor is active AND sufficient time has passed
							turningLock = 0;
							turningLockTimer = 0;
						}
						else {
							turningLock = 1;
							setVirtualCarSpeed(0.0, 45);
						}
					}
				} else if ((currentmove == prevmove - 1) || (currentmove == LEFT && prevmove == UP)) {		// Rotate 90 degrees anti-clockwise
					if (turningLockTimer == 0) {
						turningLockTimer = 1;
						myTimer.resetTimer();
					}

					if (myTimer.getTimer() > 0.8 && virtualCarSensorStates[3] == 0) {			// Rotate until sensor is active AND sufficient time has passed
						turningLock = 0;
						turningLockTimer = 0;
					} else {
						turningLock = 1;
						setVirtualCarSpeed(0.0, 45);
					}
				}

				if (turningLock == 0) {															// If car is turning, skip this
					turningAroundTimer = 0;
					while (directions[index + 1].first == directions[index].first) {			// How many future moves are in the same direction
						index++;
						targetTime += 1.1;
					}
					setVirtualCarSpeed(0.6, 0.0);			
					myTimer.resetTimer();
					index++;
					prevmove = currentmove;
					// Obtain next move
					if (directions[index].first == "U") {
						futuremove = UP;
					}

					if (directions[index].first == "R") {
						futuremove = RIGHT;
					}
					
					if (directions[index].first == "D") {
						futuremove = DOWN;
					}
					
					if (directions[index].first == "L") {
						futuremove = LEFT;
					}

					// By comparing the current move to future move, determine which sensor will be required to check when to stop
					if ((futuremove == currentmove + 1) || (futuremove == UP && currentmove == LEFT)) {				// Next turn is right turn, so set sensor of interest to be centre-right (#5)
						SensorOI = 5;
					} else if ((futuremove == currentmove - 1) || (futuremove == LEFT && currentmove == UP)) {		// Next turn is left turn, so set sensor of interest to be centre-left (#4)
						SensorOI = 4;
					}
				}
			}
		}
		else {				// If the sensor indicating the car has not reached its next stopping point, execute this
			//Following statements are for adjusting car
			if (virtualCarSensorStates[3] == 0) {							// If front sensor goes off, continue forward
				setVirtualCarSpeed(0.6, 0.0);
			} else if (virtualCarSensorStates[0] == 0) {					// If front-left sensor goes off, adjust left	
				setVirtualCarSpeed(0.6, 25.0);
			} else if (virtualCarSensorStates[1] == 0) {					// If front-right sensore goes off, adjust right.
				setVirtualCarSpeed(0.6, -25.0);
			}
		}
	}


	// Use of odometry to track the car

	// If we have set the car to be on an angle, update the angle the car is at
	if (virtualCarAngularSpeed != 0) {									
		estimatedAngle += (virtualCarAngularSpeed * movementTimer.getTimer());
	}
	
	// Update car angle to be in range of 0 to 360 degrees
	if (estimatedAngle > 360) {
		estimatedAngle -= 360;
	} else if (estimatedAngle < 0) {
		estimatedAngle += 360;
	}

	// Depending on what direction the car is facing, update our estimate for the car's X and Y position (unit is coord)
	if ((estimatedAngle < 15)  || (estimatedAngle > 345)) {
		estimatedXPos += (virtualCarLinearSpeed * movementTimer.getTimer());
	} else if ((75 < estimatedAngle) && (estimatedAngle < 105)) {
		estimatedYPos += (virtualCarLinearSpeed * movementTimer.getTimer());
	} else if ((165 < estimatedAngle) && (estimatedAngle < 195)) {
		estimatedXPos -= (virtualCarLinearSpeed * movementTimer.getTimer());
	} else {
		estimatedYPos -= (virtualCarLinearSpeed * movementTimer.getTimer());
	}

	movementTimer.resetTimer();

	return 1;
}


/*
* Reading map from txt file
*/
void myMapRead(void) {
	int rowIndex = 0;
	int columnIndex;
	std::ifstream file("map/map.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			for (columnIndex = 0; columnIndex < line.length(); columnIndex++) {
				if (line[columnIndex] == '0') {
					map[rowIndex][columnIndex] = 0;
				} else {
					map[rowIndex][columnIndex] = 1;
				}
			}
			rowIndex++;
		}
		file.close();
	}
}


/*
* Readings co-ordinates of food particles from txt file
*/
void readFoodList(void) {
	int rowIndex = 0;
	int columnIndex;
	printf("\n");
	std::ifstream file("foodList/foodList.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			string firstPos, secondPos, thirdPos, fourthPos, fifthPos, rowPos, colPos;
			int rowVal, colVal;

			firstPos = line[0];
			secondPos = line[1];
			thirdPos = line[2];
			fourthPos = line[3];
			fifthPos = line[4];

			if (secondPos != " ") {
				rowPos = firstPos + secondPos;
				if (fifthPos == " ") {
					colPos = fourthPos;
				}
				else {
					colPos = fourthPos + fifthPos;
				}
			} else {
				rowPos = firstPos;
				if (fourthPos == " ") {
					colPos = thirdPos;
				}
				else {
					colPos = thirdPos + fourthPos;
				}
			}

			stringstream conv2IntRow(rowPos);
			conv2IntRow >> rowVal;
			stringstream conv2IntCol(colPos);
			conv2IntCol >> colVal;

			foodList.emplace_back(make_pair(colVal, rowVal));
		}
		file.close();
	}
}

/*
* Finds the shortest path between food particles
*/
vector<pPair> getDirectionsFromFoodParticles(const array<array<int, COL>, ROW>& map, vector<Pair> foodList, Pair src) {

	vector<pPair>  directions, returnedDirections;

	//Get directions from starting point to first food item
	returnedDirections = aStarSearch(map, src, foodList[0]);
	directions.insert(directions.end(), returnedDirections.begin(), returnedDirections.end());

	//Getting directions from current food item to next food item
	for (int i = 0; i < foodList.size() - 1; i++) {

		Pair src = make_pair(foodList[i].first, foodList[i].second);
		Pair dest = make_pair(foodList[i + 1].first, foodList[i + 1].second);

		returnedDirections = aStarSearch(map, src, dest);

		directions.insert(directions.end(), returnedDirections.begin(), returnedDirections.end());
	}

	return directions;
}

/*
* Retrieves all spots that the robot can move to
*/
void getEmptySpotLocations() {
	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			if (map[row][col] == 0) {
				emptySpots.emplace_back(make_pair(row, col));
			}
		}
	}
}

void visitAllSpots(Pair src) {

	vector<pPair> returnedDirections;
	array<array<int, COL>, ROW> altMap = map;
	Pair nextPos = emptySpots[0];

	//While there are spots that have not been visited continue to travel
	while (!emptySpots.empty()) {
		emptySpots.erase(emptySpots.begin());

		//Try to travel to the next point that can pick the food items up
		returnedDirections = aStarSearch(altMap, src, nextPos);
		//If we cannot reach the destination, call A* on the regular map
		//TODO: try to find the closest empty space direction in if statement
		if (returnedDirections.size() == 0) {
			returnedDirections = aStarSearch(map, src, nextPos);
		}

		//Block positions we have already visited
		for (auto& direction : directions) {
			altMap[direction.second.first][direction.second.second] = 1;
		}

		directions.insert(directions.end(), returnedDirections.begin(), returnedDirections.end());

		//Remove locations we have passed through from emptySpots vector
		for (auto& direction : returnedDirections) {
			for (int i = 0; i < emptySpots.size(); i++) {
				if (emptySpots[i] == direction.second) {
					emptySpots.erase(emptySpots.begin() + i);
					break;
				}
			}
		}

		src = nextPos;
		nextPos = emptySpots[0];
	}
	printf("\nNumber of steps taken: %d\n", directions.size());
}




int main(int argc, char** argv)
{

	//Variables that need to be set before running the code
	selectedLevel = 2;
	prevmove = DOWN;							// What direction is the car initially facing	
	src = make_pair(1, 1);						// Starting point (ROW, COL)

	FungGlAppMainFuction(argc, argv);

	return 0;
}