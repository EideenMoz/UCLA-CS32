//
//  Board.hpp
//  Kalah
//
//  Created by Esmail Mozaffari on 5/19/23.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include "Side.h"
#include <vector>

class Board
{
    public:
        Board(int nHoles, int nInitialBeansPerHole);
        int holes() const;
        int beans(Side s, int hole) const;
        int beansInPlay(Side s) const;
        int totalBeans() const;
        bool sow(Side s, int hole, Side& endSide, int& endHole);
        bool moveToPot(Side s, int hole, Side potOwner);
        bool setBeans(Side s, int hole, int beans);
    
    
    private:
        int m_holesPerSide;
        int m_initialBeansPerHole;
        std::vector<int> m_NorthSide;  
        std::vector<int> m_SouthSide;

    
};

#endif /* Board_hpp */
