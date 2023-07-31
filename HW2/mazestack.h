//
//  mazestack.hpp
//  HW2
//
//  Created by Esmail Mozaffari on 4/29/23.
//

#ifndef mazestack_hpp
#define mazestack_hpp

#include <stdio.h>


bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
         // Return true if there is a path from (sr,sc) to (er,ec)
         // through the maze; return false otherwise

#endif /* mazestack_hpp */
