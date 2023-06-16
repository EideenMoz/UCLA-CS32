//
//  History.cpp
//  Rabbits
//
//  Created by Esmail Mozaffari on 4/6/23.
//

#include "History.h"
#include <iostream>
#include "globals.h"

using namespace std;

History::History(int nRows,int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    
    // Fill in history grid with dots
    for (int r = 1; r <= m_rows; r++)
    {
        for (int c = 1; c <= m_cols; c++)
        {
            m_historyGrid[r - 1][c - 1] = '.';
        }
    }
    
}

bool History::record(int r, int c)
{
    if (r > m_rows || r < 1 || c > m_cols || c < 1)
    {
        return false;
    }
    
    else
    {
        if (m_historyGrid[r-1][c-1] == '.')
        {
            m_historyGrid[r-1][c-1] = 'A';
            return true;
        }

        else if (m_historyGrid[r-1][c-1] >= 'A' && m_historyGrid[r-1][c-1] < 'Z')
        {
            m_historyGrid[r-1][c-1] += 1;
            return true;
        }
        
        else
        {
            m_historyGrid[r-1][c-1] = 'Z';
            return true;
        }
        
    }
}

void History::display() const
{
    // clear the screen
    clearScreen();
    // Draw the grid, this goes in display
    for (int r = 1; r <= m_rows; r++)
    {
        for (int c = 1; c <= m_cols; c++)
            cout << m_historyGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
    
}

