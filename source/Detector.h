//Benjamin Greenwood
//Novel Poudel
//Final Project
//Maze simulation

//Detector function

#ifndef detector_h
#define detector_h

#include "Structs.h"

//detects if the step to be taken is valid
bool pathDetect(bool maze[rowSize][colSize], Point current) {
	if ((current.x < 0) || (current.x > rowSize) || (current.y < 0) || (current.y > colSize))
		return false;
	return maze[current.x][current.y];

}

#endif