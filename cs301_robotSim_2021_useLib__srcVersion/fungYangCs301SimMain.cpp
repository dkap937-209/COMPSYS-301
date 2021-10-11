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

int main(int argc, char** argv)
{
	FungGlAppMainFuction(argc, argv);

	return 0;
}
