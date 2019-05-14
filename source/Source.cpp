//Benjamin Greenwood
//Novel Poudel
//Final Project
//Maze simulation

//This program is coded to compare maze solving algorithms based on the steps taken to get from one point to another in a given maze

//main source file

#include <fstream>
#include <string>

#include "Dijkstra.h"
#include "WallAlgorithm.h"

using std::ifstream;
using std::string;


int main()
{
	//CHANGE THE FILE NAME TO READ A DIFFERENT FILE
	std::ifstream mazeFile("maze3 15x30.txt");

	bool beenThere[rowSize][colSize];			//this array holds bool values for the maze array
	bool maze[rowSize][colSize];				//this is the maze array

	//setting up the beenThere array
	for (int i = 0; i < rowSize; i++)
		for (int j = 0; j < colSize; j++)
			beenThere[i][j] = 0;
	
	//Reading the txt file and storing the values as bools (they are actually taken as ints)
	if (mazeFile.is_open())
	{
		//reading the file and storing the data in a boolean array
		std::string line;
		int counter = 0;
		while (std::getline(mazeFile, line)) {
			std::cout << line << "\n";							//displaying the input
			for (int i = 0; i < rowSize; i++)
			{
				maze[counter][i] = line[i] - 48;			//converting char to int, which is taken as bool
			}
			counter++;
		}
	}
	else
	{
		cout << "Unable to read the file\n";
		return -1;
	}

	int steps = 0;
	Point start(0, 3);
	Point dest(14, 28);

	if (wallAlgorithm(maze, start, dest, beenThere, -1, steps))
		cout << "Wall Algorithm: " << steps << "\n";
	else
		cout << "There is no solution\n";


	//resetting the bool array
	for (int i = 0; i < rowSize; i++)
		for (int j = 0; j < colSize; j++)
			beenThere[i][j] = 0;

	dijkstraAlgorithm(maze, start, dest, beenThere);
	return 0;
}