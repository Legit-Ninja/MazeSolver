#ifndef visualization_h
#define visualization_h

#include <iostream>

#include "Structs.h"

bool stopGraphics = false;
char position = 178;
bool flow = false;

void show(bool maze[rowSize][colSize], Point current, Point end, int steps)
{
	system("CLS");
	std::cout << "\t\tVISUALIZATION\n\nWALL ALGORITHM";
	std::cout << "steps taken till now: " << steps << "\n";
	std::cout << "current position: " << current.x << " " << current.y << "\n";
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
			if (i == current.x&&j == current.y)
				std::cout << position;
			else
				std::cout << maze[i][j];
		std::cout << "\n";
	}
	std::cout << "Destination : " << end.x << " " << end.y << "\n";
}

void show(bool maze[rowSize][colSize], Point current, Point end)
{
	system("CLS");
	std::cout << "\t\tVISUALIZATION\n\nDIJKSTRA'S ALGORITHM\n";
	std::cout << "current position: " << current.x << " " << current.y << "\n";
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
			if (i == current.x&&j == current.y)
				std::cout << position;
			else
				std::cout << maze[i][j];
		std::cout << "\n";
	}
	std::cout << "Destination : " << end.x << " " << end.y << "\n";
}

#endif