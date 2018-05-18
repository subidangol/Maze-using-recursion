//Recursively Finding a Path through the Maze

#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

const int maxRows = 22;   //declaring constant to process mazes 
const int maxCols = 76;   //so that have certain amount of rows and columns
const char Wall = '+';    //naming '+' as Wall
const char Open = ' ';    //naming free space as Open
const char Path = '@';    //naming the solution as Path

void readFile(string fname, char maze[maxRows][maxCols], int &totalRows, int &totalCols)
//reads the file that the user wants to be processed
//precondition - four parameters: filename, two-dimensional array, two integers
//postcondition - stores the contents of file in the array and returns the total rows and columns
{
  ifstream fin;           //to read a file
	string line;            //declaring a string
	fin.open(fname.c_str());//opening the file
	
	if (fin.fail())         //if the file does not exist or is not acceptable
	{
		cout << "Invalid input. Unable to open the file." << endl;
		exit(EXIT_FAILURE);   //stops the program
	}
	
	fin >> totalRows >> totalCols; //reads number of rows and columns of the maze  
  getline(fin, line);            //to get to new line where the maze starts

  for (int i = 0; i < totalRows; i++)
  {
    getline(fin, line);          //reads a line from the fiel
    for (int j = 0; j < totalCols; j++)
		{
      maze[i][j] = line[j];      //stores characters seperately in a two-dimensional array
		}
  }
  fin.close();      
}

void print(char maze[maxRows][maxCols], int totalRows, int totalCols)
//prints the maze
//precondition - three parameters: one two-dimensional array and two integers
//postcondition - prints the maze from the array
{
	for(int a = 0; a < totalRows; a++)
	{
		for(int b = 0; b < totalCols; b++)
		{
			cout << maze[a][b];  //prints a row of the maze
		}
		cout << endl;          //breaks the line
	}
}

int findOpenings(char maze[maxRows][maxCols], int totalCols, int row)
//find open space in a certain row of the maze
//precondition - three parameters: one two-dimensional array and two integers
//postcondition - returns the Open column
{
	for(int y = 0; y < totalCols; y++)
	{
		if(maze[row][y] == Open)   //if the Open space is found
			return y;                //return the column number
	}
}

bool solve(char maze[maxRows][maxCols], bool visited[maxRows][maxCols], int r, 
int c, int x_endingPoint, int y_endingPoint, int totalRows, int totalCols)
//solves the maze that was obtained from the file using recursion and conditional statements
//precondition - eight parameters: two two-dimensional arrays, six integers
//postcondition - return a bool variable
{
	if(0 < r < totalRows && 0 < c < totalCols)
	//if the current row and column are within the declared limits, then proceed
	{
		if(visited[r][c] || maze[r][c] == Wall || r < 0 || c < 0 || r > totalRows || c > totalCols)
		//if the position has not been visited, is not a Wall, or out of the boundary,
			return false; //then return false

		visited[r][c] = true; //store bool variable true in the visited array, if not visited before

		if((r == x_endingPoint && c == y_endingPoint) || 
			 	solve(maze, visited, r+1, c, x_endingPoint, y_endingPoint, totalRows, totalCols) || 
				solve(maze, visited, r-1, c, x_endingPoint, y_endingPoint, totalRows, totalCols) || 
				solve(maze, visited, r, c+1, x_endingPoint, y_endingPoint, totalRows, totalCols) || 
				solve(maze, visited, r, c-1, x_endingPoint, y_endingPoint, totalRows, totalCols))
		//if we have reached our destination, then store the position as Path in the maze array
		//or use recursion to find the path to our destination
		//base case - stores Path if our destination is found
		{
			maze[r][c] = Path;
			return true;
		}
	}
	  return false; //base case - goes back to find another way, if path was not found
}

int main()
{
	char maze[maxRows][maxCols];             //declare a two-dimensional array to store the maze
	bool visited[maxRows][maxCols] = {false};//declare another array to store visited positions
	string fname;                            //declare a string variable to store filename
	int totalRows, totalCols, x_startingPoint, y_startingPoint, x_endingPoint, y_endingPoint;
	//declare six integers

	cout << "Enter file name: ";             //prompts user to enter name of the file that has a puzzle
	cin >> fname;                            //inputs the filename 
  readFile(fname, maze, totalRows, totalCols); //calling the function that reads the file
	cout << "\nThe Unsolved Maze:" << endl;  
	print(maze, totalRows, totalCols);       //prints the maze that is in the file
	
	x_startingPoint = 0;                     //initialize it zero because the first row has the starting point
	y_startingPoint = findOpenings(maze, totalCols, x_startingPoint);//call function that returns the open column
	x_endingPoint = totalRows-1;             //the destination is in the last row
	y_endingPoint = findOpenings(maze, totalCols, x_endingPoint);    //call function that returns the open column
	
  solve(maze, visited, x_startingPoint, y_startingPoint, x_endingPoint, y_endingPoint, totalRows, totalCols);
	//calls function that finds the solution of the maze
	cout << "\nSolution:" << endl;
	print(maze, totalRows, totalCols);       //prints the solution path of the maze
	return 0;
}
