//
//  main.cpp
//  maze
//
//  Created by Esmail Mozaffari on 5/6/23.
//



// ----------------------------------------------------------------------------------------------------------
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    // Base case
    if (sr == er && sc == ec)
        return true;
    
    maze[sr][sc] = '*';
    
    // SOUTH
    if (maze[sr+1][sc] == '.') {
        if (pathExists(maze, sr + 1, sc, er, ec))
            return true;
    }
    
    // EAST
    if (maze[sr][sc+1] == '.') {
        if (pathExists(maze, sr, sc + 1, er, ec))
            return true;
    }
    
    // NORTH
    if (maze[sr-1][sc] == '.') {
        if (pathExists(maze, sr - 1, sc, er, ec))
            return true;
    }
    
    // WEST
    if (maze[sr][sc-1] == '.') {
        if (pathExists(maze, sr, sc - 1, er, ec))
            return true;
    }
    
    return false;
}
// ----------------------------------------------------------------------------------------------------------

