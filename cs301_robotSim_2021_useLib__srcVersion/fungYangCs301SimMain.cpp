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
vector<string> directions;
vector<Pair> foodList;

void myMapRead(void);
void readFoodList(void);

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
	//currentCarAngle = 90;//degree
	//maxDarkDefValueTH = 20;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	myMapRead();
	readFoodList();

	printf("Printing location of food particles");
	for (auto& food : foodList) {
		printf("(%d, %d)\n", food.first, food.second);
	}
	printf("\n");

	printf("Printing map from init\n");
	//Printing the map
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout << map[i][j];
		}
		cout << "\n";
	}

	//Source point (ROW, COL)
	Pair src = make_pair(1, 1);

	//Destination point (ROW, COL)
	Pair dest = make_pair(3, 9);

	//Calling A* algorithm
	/*aStarSearch(map, src, dest);*/
	directions = aStarSearch(map, src, dest);

	//Printing out directions to get to destination
	for (auto& direction : directions) {
		printf("%s, ", direction.c_str());
	}


	virtualCarLinearSpeed_seed = virtualCarLinearSpeedFloor * floorToCoordScaleFactor;//coord

	currentCarPosCoord_X = floorToCoordX(currentCarPosFloor_X);
	currentCarPosCoord_Y = floorToCoordY(currentCarPosFloor_Y);
	myTimer.resetTimer();

	return 1;
}

//Main function to update
int virtualCarUpdate()
{
	//{----------------------------------
	//process sensor state information
	float halfTiltRange = (num_sensors - 1.0) / 2.0;
	float tiltSum = 0.0;
	float blackSensorCount = 0.0;
	for (int i = 0; i < num_sensors; i++)
	{
		if (virtualCarSensorStates[i] == 0)
		{
			float tilt = (float)i - halfTiltRange;
			tiltSum += tilt;
			blackSensorCount += 1.0;
		}
	}
    //}------------------------------------

	if (distanceTravelled == 10.0) {
		setVirtualCarSpeed(0.0, 0.0);
		cout << "Finished with time: " << (myTimer.getTimer()) << endl;
	}
	else {
		setVirtualCarSpeed(0.5, 0.0);
		distanceTravelled += 0.5;
	}

	//if (myTimer.getTimer() > 3) {
	//	setVirtualCarSpeed(0.5, 30.0);
	//	cout << "=turning=" << endl;
	//} else { 
	//	setVirtualCarSpeed(0.5, 0.0);
	//	cout << "=straight=" << endl;
	//}
	//	
	//if (myTimer.getTimer() > 5) {
	//	myTimer.resetTimer();
	//} 

	//{------------------------------------
	//updat linear and rotational speed based on sensor information
//	if (blackSensorCount > 0.0)
//		setVirtualCarSpeed(0.0, 0.0);
		//setVirtualCarSpeed(virtualCarLinearSpeed_seed, virtualCarAngularSpeed_seed*tiltSum);
		//setVirtualCarSpeed(0.60, 40.0*tiltSum);
//	else
//		setVirtualCarSpeed(0.0, 0.0);
		//setVirtualCarSpeed(0.0, virtualCarAngularSpeed_seed);
		//setVirtualCarSpeed(0.0, 40.0);
	//}---------------------------------------

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
//}=============================================================

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

			foodList.emplace_back(make_pair(rowVal, colVal));
		}
		file.close();
	}
}




int main(int argc, char** argv)
{
	FungGlAppMainFuction(argc, argv);

	return 0;
}
