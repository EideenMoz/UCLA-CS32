

#include <iostream>
#include <stack>
#include "mazestack.h"
#include <cassert>
using namespace std;

int main()
{
  char maze[10][10] = {
      { 'X','X','X','X','X','X','X','X','X','X' },
      { 'X','.','.','.','X','.','.','.','.','X' },
      { 'X','.','.','X','X','.','X','X','.','X' },
      { 'X','.','X','.','.','.','.','X','X','X' },
      { 'X','X','X','X','.','X','X','X','.','X' },
      { 'X','.','.','X','.','.','.','X','.','X' },
      { 'X','.','.','X','.','X','.','.','.','X' },
      { 'X','X','.','X','.','X','X','X','X','X' },
      { 'X','.','.','.','.','.','.','.','.','X' },
      { 'X','X','X','X','X','X','X','X','X','X' }
  };

  if (pathExists(maze, 3,4, 8,1))
      cout << "Solvable!" << endl;
  else
      cout << "Out of luck!" << endl;
}
