//Benjamin Greenwood
//Novel Poudel
//Final Project
//Maze simulation

//Structs used in the program

#ifndef structs_h
#define structs_h

const int rowSize = 15;
const int colSize = 30;

const int milliSec = 400;

struct Point {
	int x;
	int y;
	Point(int a = 0, int b = 0)
	{
		x = a; y = b;
	}
};

//this struct is only used for dijkstra's algorithm
struct info {
	Point p;        //point associated with the distance
	int distance;   //distance from the start
};


#endif