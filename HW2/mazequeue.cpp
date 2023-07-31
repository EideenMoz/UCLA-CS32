//
//  mazequeue.cpp
//  HW2
//
//  Created by Esmail Mozaffari on 4/29/23.
//

#include <queue>
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
    queue<Coord> coordQueue;
    
    Coord start(sr,sc);
    coordQueue.push(start);
    maze[sr][sc] = '*';
    
    while (!coordQueue.empty()) {
        // Store current coordinate location
        Coord current = coordQueue.front();
//        cerr << current.r() << ", " << current.c() << endl;
        // Pop top coordinate
        coordQueue.pop();
        
        if (current.r() == er && current.c() == ec)
            return true;
        
        else {
            // Try South
            if (maze[current.r()+1][current.c()] == '.')
            {
                Coord south(current.r()+1, current.c());
                coordQueue.push(south);
                maze[south.r()][south.c()] = '*';
            }
            // Try East
            if (maze[current.r()][current.c()+1] == '.')
            {
                Coord east(current.r(), current.c()+1);
                coordQueue.push(east);
                maze[east.r()][east.c()] = '*';
            }
            // Try North
            if (maze[current.r()-1][current.c()] == '.')
            {
                Coord north(current.r()-1, current.c());
                coordQueue.push(north);
                maze[north.r()][north.c()] = '*';
            }
            // Try West
            if (maze[current.r()][current.c()-1] == '.')
            {
                Coord west(current.r(), current.c()-1);
                coordQueue.push(west);
                maze[west.r()][west.c()] = '*';
            }
        }
    }
    
    return false;
}


