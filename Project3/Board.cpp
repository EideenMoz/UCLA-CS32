//
//  Board.cpp
//  Kalah
//
//  Created by Esmail Mozaffari on 5/19/23.
//

#include "Board.h"
#include "Side.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
// Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
{
    m_holesPerSide = (nHoles > 0) ? nHoles : 1;     // Validation check for holes
    m_initialBeansPerHole = (nInitialBeansPerHole >= 0) ? nInitialBeansPerHole : 0;     // Validation check for beans
    
    // Reserve memory for each vector
    m_NorthSide.reserve(m_holesPerSide + 1);
    m_SouthSide.reserve(m_holesPerSide + 1);
    
    // Pots start with 0 beans
    m_NorthSide.push_back(0);
    m_SouthSide.push_back(0);
    
    // Fill in each side's holes with beans
    for (int i = 1; i <= m_holesPerSide; i++) {
        m_NorthSide.push_back(m_initialBeansPerHole);
        m_SouthSide.push_back(m_initialBeansPerHole);
    }
        
}


int Board::holes() const
// Return the number of holes on a side (not counting the pot).
{
    return m_holesPerSide;
}


int Board::beans(Side s, int hole) const
// Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
{
    // Check for valid hole
    if (hole >= 0 && hole <= m_holesPerSide)
    {
        
        if (s == NORTH)
            return m_NorthSide[hole];
        
        if (s == SOUTH)
            return m_SouthSide[hole];
    }
    
    return -1;
    
}


int Board::beansInPlay(Side s) const
// Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
{
    
    int count = 0;
    
    if (s == NORTH) {
        for (int i = 1; i <= m_holesPerSide; i++)
            count += m_NorthSide[i];
    }
    
    if (s == SOUTH) {
        for (int i = 1; i <= m_holesPerSide; i++)
            count += m_SouthSide[i];
    }
        
    return count;
}


int Board::totalBeans() const
// Return the total number of beans in the game, including any in the pots.
{
    int count = 0;
    
    for (int i = 0; i <= m_holesPerSide; i++) {
        count += m_NorthSide[i];
        count += m_SouthSide[i];
    }
        
    return count;
}


bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
// If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The function sets the parameters endSide and endHole to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
{
    // Validity Check
    if ( hole <= 0 || hole > m_holesPerSide || beans(s, hole) == 0)
        return false;
    
    // Starting on North's side
    
    else if (s == NORTH)
    {
        int beansToSow = m_NorthSide[hole];
        m_NorthSide[hole] = 0;
        int curHole = hole;
        
        while (beansToSow > 0)           // Keeping looping through board while beans are left
        {
            while (beansToSow > 0 && curHole >= 1)      // Keep sowing while there are beans and are on North's side
            {
                curHole--;                              // curHole is now the hole at which we want to sow
                if (curHole == 0) {                     // Case 1: we reached North's Pot
                    m_NorthSide[0]++;
                    beansToSow--;
                    endHole = 0;
                    break;              // finish at North's pot
                }
                else {                                  // Case 2: in North's holes
                    m_NorthSide[curHole]++;
                    beansToSow--;
                    endHole = curHole;
                }
            }
            
            endSide = NORTH;                        // Finished on North's side
            
            if (beansToSow > 0) {         // If beans remain, shift to South Side and sow
                curHole = 1;                                                        // Begin at South's first Hole
                while (beansToSow > 0 && curHole <= m_holesPerSide)
                {
                    m_SouthSide[curHole]++;
                    beansToSow--;
                    endHole = curHole;
                    curHole++;
                }
                endSide = SOUTH;                    // Finish on South side
            }
        }
    }
    
    // Starting on South's Side
    else
    {
        int beansToSow = m_SouthSide[hole];
        m_SouthSide[hole] = 0;
        int curHole = hole;
        
        while (beansToSow > 0)       // Keeping looping through board while beans are left
        {
            while (beansToSow > 0 && curHole <= m_holesPerSide)      // Keep looping until reach Pot
            {
                curHole++;
                if (curHole == m_holesPerSide + 1) {        // Case 1: current is at the pot (for simiplicity, map pot to holes+1)
                    m_SouthSide[0]++;
                    beansToSow--;
                    endHole = 0;
                    break;
                }
                else {
                    m_SouthSide[curHole]++;
                    beansToSow--;
                    endHole = curHole;
                }
            }
            
            endSide = SOUTH;
            
            if (beansToSow > 0)
            {
                curHole = m_holesPerSide;
                while (beansToSow > 0 && curHole > 0)
                {
                    m_NorthSide[curHole]++;
                    beansToSow--;
                    endHole = curHole;
                    curHole--;
                }
                endSide = NORTH;
            }
        }
    }
        
    return true;
}


bool Board::moveToPot(Side s, int hole, Side potOwner)
// If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
{
    if (hole <= 0 || hole > m_holesPerSide)
        return false;
    
    else
    {
        if (s == NORTH)
        {
            if (potOwner == NORTH) {
                m_NorthSide[0] += m_NorthSide[hole];
                m_NorthSide[hole] = 0;
            }
            else {
                m_SouthSide[0] += m_NorthSide[hole];
                m_NorthSide[hole] = 0;
            }
        }
        
        else
        {
            if (potOwner == NORTH) {
                m_NorthSide[0] += m_SouthSide[hole];
                m_SouthSide[hole] = 0;
            }
            else {
                m_SouthSide[0] += m_SouthSide[hole];
                m_SouthSide[hole] = 0;
            }
        }
    }
    
    return true;
}


bool Board::setBeans(Side s, int hole, int beans)
// If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This could change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
{
    if ( hole < 0 || hole > m_holesPerSide || beans < 0)
        return false;
    else
    {
        if (s == NORTH)
            m_NorthSide[hole] = beans;
        else
            m_SouthSide[hole] = beans;
    }
    
    return true;
}

