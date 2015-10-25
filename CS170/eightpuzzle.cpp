#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

//store default pussle
int puzzledefault[3][3] = {{1, 3, 2}, {4, 9, 5}, {8, 6, 7}};
//store custom key
int puzzlecustom[3][3];
//9 is the blank spot
int puzzlegoal[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

//holds data about one state, and its children
struct State
{
	int state[3][3];
	//g(n)
	int depth;
	//next possible states that can be reached
	vector<int> children;
};

//holds tree of all states
struct Tree
{
	vector<State> tree;
};

//displays the custom puzzle
void displayCustomPuzzle(int puzzle[][3])
{
	cout << endl;
	for (unsigned int i = 0; i < 3; ++i)
	{
			for (unsigned int j = 0; j < 3; ++j)
			{
					cout << puzzle[i][j] << " ";
			}
			cout << endl;
	}
}

//checks to see if goal state is reached
bool checkGoalState()
{
	return (puzzledefault == puzzlegoal || puzzlecustom == puzzlegoal);
}

//find correct indexes of where number n piece should be
void findCorrectPos(int n, int goalstate[][3], int &ifinal, int &jfinal)
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			//once correct index found, return
			if (n == goalstate[i][j])
			{
				ifinal = i;
				jfinal = j;
				return;
			}
		}
	}
}

//returns estimated cost of moving piece to correct spot
int getHeuristic(int currentstate[][3], int goalstate[][3])
{
	int total = 0;
	int ifinal = 0;
	int jfinal = 0;
	for (unsigned int i = 0; i < 3; ++i)
	{
		for (unsigned int j = 0; j < 3; ++j)
		{
			//if spots do not match, find manhatten distance
			if (currentstate[i][j] != 9 && currentstate[i][j] != goalstate[i][j])
			{
				findCorrectPos(currentstate[i][j], goalstate, ifinal, jfinal);
				total += abs(i - ifinal) + abs(j - jfinal);
			}
		}
	}
	return total;
}

int main()
{
	int puzzletype;
	cout << "Welcome to Rica's soon to be A+ eight-puzzle solver." << endl;
	cout << "Type '1' to use default puzzle, type anything else to use custom puzzle." << endl;
	cin >> puzzletype;

	if (puzzletype == 1) //default puzzle
	{

	}
	else //custom puzzle
	{
		int spot;
		cout << "Enter in 9 numbers, 1 - 9, seperated by spaces, which will fill in the eight puzzle." << endl;
		cout << "The eight-puzzle will be filled in from left to right, from the first row to the last row. " << endl;
		cout << "Make sure to only enter digits; entering a 9 will represent the blank space." << endl;
		cout << "No repeating digits allowed." << endl;
		for (unsigned int i = 0; i < 3; ++i)
		{
			for (unsigned int j = 0; j < 3; ++j)
			{
				cin >> spot;
				puzzlecustom[i][j] = spot;
			}
		}

		displayCustomPuzzle(puzzlecustom);
		cout << "curr h: " << getHeuristic(puzzlecustom, puzzlegoal) << endl;
	}
}
