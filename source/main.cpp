#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout; using std::endl; using std::vector; using std::ifstream;


void dijkstraAlgorithm(int maze[50][50])
{

}
//check if you can go right, go right, then if not left, then if not backwards 
void wallAlgorithim(int maze[50][50], int r, int c,  bool beenThere[50][50], int direction, int &steps)                 //direction is the index of the imaginary array that we came from.
{                                                                                                           //0 - right, 1 - up, 2 - left, 3 - down
    // if (r+1 > 50 || c+1 > 50 || c-1 < 0 || r-1 < 0 ) { return;}
    // else
    // {
        
    // }
    // for each possible direction minus where we came from
    for(int i = 0;i<4;i++)
    {   
        if(i!=direction && beenThere[r][c] == false) //makes sure we haven't been there and it's nopt the direction we came from
        {
            int upRow = r; int upCol = c+1;
            if (pathDetect(maze, upRow, upCol)) //check if can go left, move there
            {
                c = upCol;
                steps++;
                beenThere[r][c] = true;     //keeps track of where we've been
                int direction = 3;      //becuase the direction we came from was down
                wallAlgorithim(maze, r, c, beenThere, direction, steps);        //go again
            }
            int leftRow = r-1; int leftCol = c;
            if ( pathDetect(maze, leftRow, leftCol))
            {
                r = leftRow;
                steps++;
            }
        }
            
    }
}

bool pathDetect(int maze[50][50], int r, int c)
{
    if ( maze[r][c] == 1 || maze[r][c] == 2)
    {
        return true;
    }
    return false;
}
int main()
{
    int data[50][50];                                    //dynamically alloocates memory for a lot of ints
    ifstream infile;        
    infile.open("maze1.txt");                               //opens up the file of 50x50 bool
    if (!infile) { cout << "failed to open maze" << endl; }    //makes sure the file actually was found and opened    
    
    string line;
    int row = 0;
    while(!infile.eof()){
        getline(infile,line);
        cout << "Cur Line: |" << line << "|" << endl;
        for(int i = 0; i < 20; i++){
            cout << " " << static_cast<int>(line[i]-48);
            data[row][i] = static_cast<int>(line[i]-48);
        }
        row++;
        cout << endl;
    }


    return 0;
}

