#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using std::cout; using std::endl; using std::queue; using std::ifstream; using std::string;
int possRow[] = { -1, 0, 0, 1};        //arrays used to check around coordinates/cells
int possCol[] = { 0, -1, 1, 0};

struct point //allows us to easily store coordinates
{ int x; int y; };
struct info {
    point p;        //point associatd with the distance
    int distance;   //distance from the start
 };
bool pathDetect(int maze[10][10], point p)
{
    if ( maze[p.x][p.y] == 1 )
    {
        return true;
    }
    return false;
}

void dijkstraAlgorithm(int maze[10][10], point start, point dest, bool beenThere[10][10])
{
    beenThere[start.x][start.y] = true;
    queue<info> q;
    info info_ = {start, 0}; // the first item in the queue will be the starting point, has distance 0
    q.push(info_);

    while (!q.empty())
    {
        info curr = q.front();      //keeps track of where we are currently 
        point currPoint = curr.p;      

        if (currPoint.x == dest.x && currPoint.y == dest.y )    //if we have reached teh destination
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
            if( pathDetect(maze, currPoint) && beenThere[row][col] != true)   //if it's a valid place and we haven't been there
            {
                beenThere[row][col] = true;     //marks the new cell
                info nextCell = { {row, col}, curr.distance +1};    // adds the cell to the queue to be checked out for a possible solution
                q.push(nextCell);
            }
        }
    }
    return;
}
//check if you can go right, go right, then if not left, then if not backwards 
/*void wallAlgorithim(int maze[10][10], point start,  bool beenThere[10][10], int direction, int &steps)                 //direction is the index of the imaginary array that we came from.
{
    if ( r < 0 || c < 0 || r > 10 || c > 10) { return; } 
    // for each possible direction minus where we came from
    for(int i = 0; i<4; i++)
    {   
        if(i != direction && beenThere[r][c] == false) //makes sure we haven't been there and it's not the direction we came from
        {
            int upRow = r-1; int col = c;
            if (pathDetect(maze, upRow, col)) //check if can go up, move there
            {
                r = upRow;
                steps++;
                beenThere[r][c] = true;     //keeps track of where we've been (maybe need to mark previous step)
                direction = 1;      //becuase the direction we're heading is north
                wallAlgorithim(maze, r, c, beenThere, direction, steps);        //go again
            }
            int downRow = r+1; col = c;
            if (pathDetect(maze, downRow, c))
            {
                r = downRow;
                steps++;
                beenThere[r][c] = true;     //keeps track of where we've been (maybe need to mark previous step)
                direction = 3;      //becuase the direction we're heading is south
                wallAlgorithim(maze, r, c, beenThere, direction, steps);        //go again
            }
            int row = r; int leftCol = c-1;
            if (pathDetect(maze, row, leftCol))
            {
                c = leftCol;
                steps++;
                beenThere[r][c] = true;     //keeps track of where we've been (maybe need to mark previous step)
                direction = 2;      //becuase the direction we're heading is west
                wallAlgorithim(maze, r, c, beenThere, direction, steps);        //go again
            }
             row = r; int rightCol = c+1;
            if (pathDetect(maze, row, rightCol))
            {
                c = rightCol;
                steps++;
                beenThere[r][c] = true;     //keeps track of where we've been (maybe need to mark previous step)
                direction = 0;      //becuase the direction we're heading is east
                wallAlgorithim(maze, r, c, beenThere, direction, steps);        //go again
            }
        }
            
    }
} */

int main()
{
    int data[10][10];                                    //dynamically alloocates memory for a lot of ints
    ifstream infile;        
    infile.open("maze1.txt");                               //opens up the file of 50x50 bool
    if (!infile) { cout << "failed to open maze" << endl; }    //makes sure the file actually was found and opened    
    string line;
    int row = 0;
    while(!infile.eof()){
        getline(infile,line);
        cout << "Cur Line: |" << line << "|" << endl;
        for(int i = 0; i < 10; i++){
            cout << " " << static_cast<int>(line[i]-48);
            data[row][i] = static_cast<int>(line[i]-48);
        }
        row++;
        cout << endl;
    }
    bool beenThere[10][10];
    std::fill(beenThere[0], beenThere[0] + 10 * 10, 0);       //initializes the beenThere array to all 0's
    int steps = 0;
  //  wallAlgorithim(data, 0, 0, beenThere, -1, steps);


    return 0;
}

