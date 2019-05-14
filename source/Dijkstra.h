//Benjamin Greenwood
//Novel Poudel
//Final Project
//Maze simulation

//reference: https://www.geeksforgeeks.org/shortest-path-in-a-binary-maze/

//Dijkstra's algorithm

#ifndef dijkstra_h
#define dijkstra_h

#include <iostream>
#include <queue>

#include "Detector.h"

using std::cout;
using std::queue;
using std::endl;

int possRow[] = { -1, 0, 0, 1 };        //arrays used to check around coordinates/cells
int possCol[] = { 0, -1, 1, 0 };


void dijkstraAlgorithm(bool maze[rowSize][colSize], Point start, Point dest, bool beenThere[rowSize][colSize])
{
	beenThere[start.x][start.y] = true;
	queue<info> q;
	info info_ = { start, 0 }; // the first item in the queue will be the starting point, has distance 0
	q.push(info_);

	while (!q.empty())
	{
		info curr = q.front();      //keeps track of where we are currently 
		Point currPoint = curr.p;

		if (currPoint.x == dest.x && currPoint.y == dest.y)    //if we have reached teh destination
		{
			cout << "The shortest path is: " << curr.distance << endl;
			return;
		}

		//if it's not the one we're looking for, get rid of it and go to the next item in the queue
		q.pop();
		for (int i = 0; i < 4; i++)     //checks the adjecent indexes for possible paths
		{
			int row = currPoint.x + possRow[i];
			int col = currPoint.y + possCol[i];
			if (pathDetect(maze, currPoint) && !beenThere[row][col])   //if it's a valid place and we haven't been there
			{
				beenThere[row][col] = true;     //marks the new cell
				info nextCell = { {row, col}, curr.distance + 1 };    // adds the cell to the queue to be checked out for a possible solution
				q.push(nextCell);
			}
		}
	}
	cout << "No solution was found\n";
	return;
}


#endif