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
#include "mazeGen.h" //just include to use radnom number generation function
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
//int map[ROW][COL];
array<array<int, COL>, ROW> map = { {} };

//For storing directions robot needs to travel 
//to get to the destination
vector<pPair> directions;
vector<Pair> foodList, emptySpots;
int currentmove;
int prevmove = 3;						// Initially facing down
int index = 0;
int movefinished = 0;
int targetTime = 0;
int turningLock = 0;
int futuremove;
int SensorOI = 10;
int init = 0;
int turningLockTimer = 0;
//Source point (ROW, COL)
Pair src = make_pair(1, 1);
//Destination point (ROW, COL)
Pair dest = make_pair(8,13);
int journeyComplete = 0;
int selectedLevel;

void myMapRead(void);
void turnleft();
void turnright();
void readFoodList(void);
void getEmptySpotLocations();
vector<pPair> getDirectionsFromFoodParticles(const array<array<int, COL>, ROW>& map, vector<Pair> foodList, Pair src);

void visitAllSpots(Pair src);


vector<int> virtualCarSensorStates;

vector<ghostInfoPack> ghostInfoPackList;
//}-------------------------------

highPerformanceTimer myTimer;

//just a helper function
void setVirtualCarSpeed(float linearSpeed, float angularSpeed)
{
	virtualCarLinearSpeed = linearSpeed;
	virtualCarAngularSpeed = angularSpeed;
}

//The Only TWO functions Students need to modify to add their own sensor guided
//path following control and Map path search calculations.
//{=================================================
float virtualCarLinearSpeed_seed;
float virtualCarAngularSpeed_seed;

//added2021_2_22
float virtualCarLinearSpeedFloor;
float currentCarPosFloor_X, currentCarPosFloor_Y;
double distanceTravelled = 0.0;							//Variable to track distance travelled by Robot.

//TODO: THis is where we should call our path finding algorithm to find the shortest path.
//When doing finding multiple food particles, we would need to recalculate each time
int virtualCarInit()
{
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
	currentCarAngle = 270;//degree
	//maxDarkDefValueTH = 20;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	myMapRead();
	readFoodList();

	//printf("Printing location of food particles");
	//for (auto& food : foodList) {
	//	printf("\n(%d, %d): %d", food.first, food.second, map[food.first][food.second]);
	//}
	//printf("\n");

	//printf("Printing map from init\n");
	////Printing the map
	//for (int i = 0; i < ROW; i++) {
	//	for (int j = 0; j < COL; j++) {
	//		cout << map[i][j];
	//	}
	//	cout << "\n";
	//}
	// 


	//Calling A* algorithm
	//directions = aStarSearch(map, src, dest);
	if (selectedLevel == 1) {

		//Do something to visit all the cells
		printf("Level one has been selected");
		getEmptySpotLocations();
		visitAllSpots(src);

	}
	//If level two is selected find the shortest path between each food pellet
	else if (selectedLevel == 2) {
		printf("\nLevel two has been selected\n");
		//directions = getDirectionsFromFoodParticles(map, foodList, src);
		directions = aStarSearch(map, src, dest);

		//printf("\n Printing out the directions between food particles\n");
		////Printing out directions to get to destination
		//for (auto& direction : directions) {
		//	printf("%s, ", direction.c_str());
		//}
	}

	//printf("\n Printing out the directions\n");
	////Printing out directions to get to destination
	//for (auto& direction : directions) {
	//	printf("\n%s, ", direction.c_str());
	//}
	currentCarPosFloor_X = cellToFloorX(src.first);
	currentCarPosFloor_Y = cellToFloorY(src.second);

	virtualCarLinearSpeed_seed = virtualCarLinearSpeedFloor * floorToCoordScaleFactor;//coord

	currentCarPosCoord_X = floorToCoordX(currentCarPosFloor_X);
	currentCarPosCoord_Y = floorToCoordY(currentCarPosFloor_Y);
	myTimer.resetTimer();

	return 1;
}


//Main function to update
int virtualCarUpdate() {

	if (myTimer.getTimer() < 1 && init == 0) {
		setVirtualCarSpeed(0.0, 0.0);
	} else {
		init = 1;
	}

	if (journeyComplete == 1) {
		;
	} else if (index > directions.size()) {
		printf("\nWE ARE DONE!\n");
		setVirtualCarSpeed(0.0, 0.0);
		journeyComplete = 1;
	} else if (init == 1) {

		if (virtualCarSensorStates[SensorOI] == 0 || SensorOI == 10) {
			if (targetTime - 0.4 > (myTimer.getTimer())) {
				if (virtualCarSensorStates[0] == 0) {						// If back-left sensor goes off, adjust left	
					setVirtualCarSpeed(0.6, 20.0);
				}
				else if (virtualCarSensorStates[1] == 0) {					// If back-right sensore goes off, adjust right.
					setVirtualCarSpeed(0.6, -20.0);
				}
			}
			else {
				targetTime = 0;
				SensorOI = 10;
				if (directions[index].first == "U") {
					currentmove = 1;
				}
				if (directions[index].first == "R") {
					currentmove = 2;
				}
				if (directions[index].first == "D") {
					currentmove = 3;
				}
				if (directions[index].first == "L") {
					currentmove = 4;
				}
				
				if ((currentmove == prevmove + 1) || (currentmove == 4 && prevmove == 1)) {      //if turning right
					if (turningLockTimer == 0) {
						turningLockTimer = 1;
						myTimer.resetTimer();
					}
					if (myTimer.getTimer() > 0.8 && virtualCarSensorStates[3] == 0) {           //turn clockwise for 2 seconds
						turningLock = 0;
						turningLockTimer = 0;
					}
					else {
						turningLock = 1;
						setVirtualCarSpeed(0.0, -60);
					}
				}
				else if ((currentmove == prevmove + 2) || (currentmove == 3 && prevmove == 1) || (currentmove == 4 && prevmove == 2)) {
					if (turningLockTimer == 0) {
						turningLockTimer = 1;
						myTimer.resetTimer();
					}
					if (myTimer.getTimer() > 1.6 && virtualCarSensorStates[3] == 0) {
						turningLock = 0;
						turningLockTimer = 0;
					}
					else {
						turningLock = 1;
						setVirtualCarSpeed(0.0, 45);
					}
				}
				else if ((currentmove == prevmove - 1) || (currentmove == 1 && prevmove == 4)) {
					if (turningLockTimer == 0) {
						turningLockTimer = 1;
						myTimer.resetTimer();
					}
					if (myTimer.getTimer() > 0.8 && virtualCarSensorStates[3] == 0) {
						turningLock = 0;
						turningLockTimer = 0;
					}
					else {
						turningLock = 1;
						setVirtualCarSpeed(0.0, 60);
					}
				}

				if (turningLock == 0) {
					while (directions[index + 1].first == directions[index].first) {
						index++;
						targetTime += 1.5;
					}
					setVirtualCarSpeed(0.6, 0.0);      //set car to move forward and increment values
					myTimer.resetTimer();
					index++;
					prevmove = currentmove;
					if (directions[index].first == "U") {
						futuremove = 1;
					}
					if (directions[index].first == "R") {
						futuremove = 2;
					}
					if (directions[index].first == "D") {
						futuremove = 3;
					}
					if (directions[index].first == "L") {
						futuremove = 4;
					}
					if ((futuremove == currentmove + 1) || (futuremove == 4 && currentmove == 1)) {				//Right turn
						SensorOI = 5;
					}
					else if ((futuremove == currentmove - 1) || (futuremove == 4 && currentmove == 1)) {
						SensorOI = 4;
					}
				}
			}
		} else {
			if (virtualCarSensorStates[3] == 0) {
				setVirtualCarSpeed(0.6, 0.0);
			} else if (virtualCarSensorStates[0] == 0) {					// If back-left sensor goes off, adjust left	
				setVirtualCarSpeed(0.6, 20.0);
			} else if (virtualCarSensorStates[1] == 0) {					// If back-right sensore goes off, adjust right.
				setVirtualCarSpeed(0.6, -20.0);
			}
		}
	}


	//below is optional. just to provid some status report .
	//{--------------------------------------------------------------
	
	
	//if (myTimer.getTimer() > 0.5)
	//{
	//	myTimer.resetTimer();
	//	//for (int i = 0; i < ghostInfoPackList.size(); i++)
	//	//	cout << ghostInfoPackList[i].ghostType << " , " << ghostInfoPackList[i].direction << endl;
	//	cout << "=====================================" << endl;
	//	cout << "current car floor X, Y, theta = " << coordToFloorX(currentCarPosCoord_X) << " , " << coordToFloorY(currentCarPosCoord_Y) << " , " << currentCarAngle << endl;
	//	cout << "current Cell X, Y = " << coordToCellX(currentCarPosCoord_X) << " , " << coordToCellY(currentCarPosCoord_Y) << endl;
	//	cout << "-----------------------------------------" << endl;
	//	cout << " ghost list info:" << endl;
	//	for (int i = 0; i < ghostInfoPackList.size(); i++)
	//	{
	//		cout << "g[" << i << "]: (" << ghostInfoPackList[i].coord_x << ", " << ghostInfoPackList[i].coord_y <<"); [s="<<
	//			ghostInfoPackList[i].speed<<"; [d="<< ghostInfoPackList[i].direction << "]; [T=" << ghostInfoPackList[i].ghostType<<"]" << endl;
	//	}
	//}
	
	//}---------------------------------------------------------------
	
	return 1;
}
void turnright() {
	if (myTimer.getTimer() < 3) {
		setVirtualCarSpeed(0.0, 45);
	}
}

void turnleft() {
		setVirtualCarSpeed(0.0, -45);
}
//}=============================================================

/*
* Reading map from txt file
*/
void myMapRead(void) {
	int rowIndex = 0;
	int columnIndex;
	printf("\n");
	std::ifstream file("map/map.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			for (columnIndex = 0; columnIndex < line.length(); columnIndex++) {
				if (line[columnIndex] == '0') {
					map[rowIndex][columnIndex] = 0;
				}
				else {
					map[rowIndex][columnIndex] = 1;
				}
			}
			rowIndex++;
		}
		printf("\n");
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

			if (secondPos != "32") {
				rowPos = firstPos + secondPos;
			}

			if (thirdPos == " ") {
				colPos = fourthPos + fifthPos;
			}
			else if (fourthPos != " ") {
				colPos = thirdPos + fourthPos;
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
	Pair nextPos = emptySpots[0];

	//While there are spots that have not been visited continue to travel
	while (!emptySpots.empty()) {
		emptySpots.erase(emptySpots.begin());
		returnedDirections = aStarSearch(map, src, nextPos);
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
	selectedLevel = 2; 

	FungGlAppMainFuction(argc, argv);

	return 0;
}
