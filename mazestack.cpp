
//
//  mazestack.cpp
//  HW2
//
//  Created by Esmail Mozaffari on 4/29/23.
//

#include <stack>
#include <iostream>
using namespace std;


class Coord
   {
     public:
       Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
       int r() const { return m_r; }
       int c() const { return m_c; }
     private:
       int m_r;
       int m_c;
   };



bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    // Create stack, push the starting coordiante onto stack, update the maze at starting coordinate
    stack<Coord> coordStack;
    
    Coord start(sr,sc);
    coordStack.push(start);
    maze[sr][sc] = '*';

    while (!coordStack.empty()) {
        // Store current coordinate location
        Coord current = coordStack.top();
//        cerr << current.r() << ", " << current.c() << endl;
        // Pop top coordinate
        coordStack.pop();
        
        if (current.r() == er && current.c() == ec)
            return true;
        
        else {
            // Try South
            if (maze[current.r()+1][current.c()] == '.')
            {
                Coord south(current.r()+1, current.c());
                coordStack.push(south);
                maze[south.r()][south.c()] = '*';
            }
            // Try East
            if (maze[current.r()][current.c()+1] == '.')
            {
                Coord east(current.r(), current.c()+1);
                coordStack.push(east);
                maze[east.r()][east.c()] = '*';
            }
            // Try North
            if (maze[current.r()-1][current.c()] == '.') {
                Coord north(current.r()-1, current.c());
                coordStack.push(north);
                maze[north.r()][north.c()] = '*';
            }
            // Try West
            if (maze[current.r()][current.c()-1] == '.')
            {
                Coord west(current.r(), current.c()-1);
                coordStack.push(west);
                maze[west.r()][west.c()] = '*';
            }
        }
    }
    
    return false;
}





