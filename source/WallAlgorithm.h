//Benjamin Greenwood
//Novel Poudel
//Final Project
//Maze simulation

//Wall algorithm

#ifndef wallalgorithm_h
#define wallalgorithm_h

#include <cmath>
#include <chrono>
#include <thread>

#include "Detector.h"
#include "Visualization.h"

bool wallAlgorithm(bool maze[rowSize][colSize], Point current, Point end, bool beenThere[rowSize][colSize], int direction, int &steps)
{
	beenThere[current.x][current.y] = true;
	if (current.x == end.x && current.y == end.y)
		return true;

		//0 - going east
		//1 - going north
		//2 - going west
		//3 - going south
	for (int i = 0; i < 4; i++)				//this loop looks at the possible directions
	{
		if (i != direction)
		{
			//the following two lines of code converts the direction into rows and columns to increase
			double row = std::sin(3.1415* i / 2)*(-1.5);			//it was supposed to be multiplied by -1 but some of
																	//the answers came out to be -0.999999 which was read as 0 instead of -1
			double col = std::cos(3.1415* i / 2)*(1.5);				//same problem as above

			Point newPoint(current.x + (int)row, current.y + (int)col);
			if (pathDetect(maze, newPoint) && !beenThere[newPoint.x][newPoint.y])
			{
				steps++;
				if (wallAlgorithm(maze, newPoint, end, beenThere, (2 + i) % 4, steps))				//2+i mod 4 gives the opposite direction (if going east - 0, returns west - 2)
					return true;		//since we return true as soon as we get true, this function gives one answer even when there are multiple answers
				else
					steps++;
			}
		}
	}
	return false;			//returns false if the paths dont lead to the destination (Point end)
}


//THIS ONE HAS THE VISUALIZATION FUNCTION, EVERYTHING ELSE IS THE SAME
bool wallVisual(bool maze[rowSize][colSize], Point current, Point end, bool beenThere[rowSize][colSize], int direction, int &steps)
{
	beenThere[current.x][current.y] = true;
	if (current.x == end.x && current.y == end.y)
		return true;

	//0 - going east
	//1 - going north
	//2 - going west
	//3 - going south
	for (int i = 0; i < 4; i++)				//this loop looks at the possible directions
	{
		if (i != direction)
		{
			//the following two lines of code converts the direction into rows and columns to increase
			double row = std::sin(3.1415* i / 2)*(-1.5);			//it was supposed to be multiplied by -1 but some of
																	//the answers came out to be -0.999999 which was read as 0 instead of -1
			double col = std::cos(3.1415* i / 2)*(1.5);				//same problem as above

			char input;

			Point newPoint(current.x + (int)row, current.y + (int)col);
			if (pathDetect(maze, newPoint) && !beenThere[newPoint.x][newPoint.y])
			{
				steps++;
				///////the following line haults the program for given milliseconds or until a character is pressed
				//visual
				if (flow)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(milliSec));
					if (!stopGraphics)
						show(maze, newPoint, end, steps);
				}
				else
				{
					cout << "Press a key to take a step\n";
					input = getch();
					if (input == 'f')
						flow = true;
					if (!stopGraphics)
						show(maze, newPoint, end, steps);

				}
				//visual end

				if (wallVisual(maze, newPoint, end, beenThere, (2 + i) % 4, steps))				//2+i mod 4 gives the opposite direction (if going east - 0, returns west - 2)
				{
					stopGraphics = true;
					return true;		//since we return true as soon as we get true, this function gives one answer even when there are multiple answers
				}
				else
				{
					steps++;
					//visual
					if (flow)
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(milliSec));
						if (!stopGraphics)
							show(maze, newPoint, end, steps);
					}
					else
					{
						cout << "Press a key to take a step\n";
						input = getch();
						if (input == 'f')
							flow = true;
						if (!stopGraphics)
							show(maze, newPoint, end, steps);

					}
					//visual end
				}
			}
		}
	}
	return false;			//returns false if the paths dont lead to the destination (Point end)
}

#endif