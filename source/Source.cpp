#include <cmath>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>

using std::queue;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

int possRow[] = { -1, 0, 0, 1 };        //arrays used to check around coordinates/cells
int possCol[] = { 0, -1, 1, 0 };

struct Point{
	int x;
	int y;
	Point(int a = 0, int b = 0)
	{
		x = a; y = b;
	}
};

struct info {
	Point p;        //point associatd with the distance
	int distance;   //distance from the start
};

bool pathDetect(int maze[10][10], Point current) {
	if ((current.x < 0) || (current.x > 10) || (current.y < 0) || (current.y > 10))
		return false;
	return maze[current.x][current.y];

}

bool wallAlgorithm(int maze[10][10], Point current, Point end, bool beenThere[10][10], int direction, int &steps)
{
	cout << "row: " << current.x << " column: " << current.y << "\n";
	beenThere[current.x][current.y] = true;
	if (current.x == end.x && current.y == end.y)
		return true;
	int pathCount = 0;
	for (int i = 0; i < 4; i++)				//this loop looks at the possible directions
	{
		if (i != direction)
		{
			//0 - going east
			//1 - going north
			//2 - going west
			//3 - going south
			double row = std::sin(3.1415* i / 2)*(-1.5);			//it was supposed to be multiplied by -1 but some of
																	//the answers came out to be -0.999999 which was read as 0 instead of -1
			double col = std::cos(3.1415* i / 2);
			//the above two lines of code converts the direction into rows and columns to increase
			Point newPoint(current.x + (int)row, current.y + (int)col);
			if (pathDetect(maze,newPoint) && !beenThere[newPoint.x][newPoint.y])
			{
				steps++;
				if (wallAlgorithm(maze, newPoint, end, beenThere, (2 + i) % 4, steps))				//2+i mod 4 gives the opposite direction (if going east - 0, returns west - 2)
				{
					cout << "RETURNED TRUE\n";
					return true;
				}
				else
					steps++;
			}
		}
	}
	return false;
}

void dijkstraAlgorithm(int maze[10][10], Point start, Point dest, bool beenThere[10][10])
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
	return;
}


int main()
{
	std::ifstream mazeFile("maze1.txt");

	bool beenThere[10][10];
	int maze[10][10];

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			beenThere[i][j] = 0;

	if (mazeFile.is_open())
	{
		//reading the file and storing the data in a boolean array
		std::string line;
		int counter = 0;
		while (std::getline(mazeFile, line)) {
			std::cout << line << "\n";							//displaying the input
			for (int i = 0; i < 10; i++)
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
	Point start(4, 0);
	Point dest(6, 2);
	if (wallAlgorithm(maze, start, dest, beenThere, -1, steps))
		cout << "Wall Algorithm: " << steps << "\n";
	else
		cout << "There is no solution\n";


	//displaying and resetting the bool array
	cout << "\n\n";
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << beenThere[i][j];
		}
		cout << "\n";
	}

	//dijkstraAlgorithm(maze, start, dest, beenThere);
	return 0;
}