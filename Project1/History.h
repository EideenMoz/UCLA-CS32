//
//  History.hpp
//  Rabbits
//
//  Created by Esmail Mozaffari on 4/6/23.
//

#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
{
    public:
      History(int nRows, int nCols);
      bool record(int r, int c);
      void display() const;
    
    private:
        int m_rows;
        int m_cols;
        char m_historyGrid[MAXROWS][MAXCOLS];
    
    // make a 2d array, using constructor to create a 2d array with passed in rows and intialize it to empty grid
};
#endif /* HISTORY_INCLUDED */
