//
//  Player.cpp
//  Kalah
//
//  Created by Esmail Mozaffari on 5/19/23.
//

#include "Player.h"
#include "Board.h"
#include <iostream>
#include <stdio.h>
#include "Side.h"

#include <limits>

using namespace std;



// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Player

Player::Player(string name) {m_name = name;}
// Create a Player with the indicated name.


std::string Player::name() const {return m_name;}
// Return the name of the player.


bool Player::isInteractive() const {return false;}
// Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.

Player::~Player() {}
// Since this class is designed as a base class, it should have a virtual destructor.





// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HumanPlayer

HumanPlayer::HumanPlayer(string name) : Player(name) {}

bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    if (b.beansInPlay(s) == 0)
        return -1;
    
    int playerMove;
    while (1)
    {
        cout << "Select a hole, " << name() << ": ";
        cin >> playerMove;
        if (playerMove <= 0 || playerMove > b.holes())
            cout << "The hole number must be from 1 to " << b.holes() << endl;
        
        else if (b.beans(s, playerMove) == 0)
            cout << "There are no beans in that hole" << endl;
        
        else
            break;
    }
     
    return playerMove;
}

HumanPlayer::~HumanPlayer() {}


// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BadPlayer

BadPlayer::BadPlayer(string name) : Player(name) {}

int BadPlayer::chooseMove(const Board &b, Side s) const
{
    
    if (b.beansInPlay(s) == 0)
        return -1;
    
    int hole = 1;
    
    while (b.beans(s, hole) == 0)       // start at the first hole, if hole is empty, move to next hole
        hole++;
    
    return hole;
}

BadPlayer::~BadPlayer() {}

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GoodPlayer

SmartPlayer::SmartPlayer(string name) : Player(name) {}


int SmartPlayer::chooseMove(const Board &b, Side s) const
{
    int bestHole = 1;
    int value;
    int currentDepth = 0;
    int maxDepth = 10;
    
    if (b.beansInPlay(s) == 0)
        return -1;
    
    while (b.beans(s, bestHole) == 0)       // start at the first hole, if hole is empty, move to next hole
        bestHole++;
    
    double timeLimit = 4990;
    JumpyTimer timer(1000);
    
    minimax(s, b, bestHole, value, currentDepth, maxDepth, timer, timeLimit);
    
    cerr << timer.elapsed() << " ms" << endl;
    
    return bestHole;
}

SmartPlayer::~SmartPlayer() {}





int SmartPlayer::evaluate(const Board& b) const
{
    // When the game is over
    if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0)
    {
        // South has no more beans, "sweep" North's Beans
        if (b.beansInPlay(SOUTH) == 0)
        {
            if (b.beansInPlay(NORTH) + b.beans(NORTH, 0) > b.beans(SOUTH, 0))       // North is in Winning position
                return std::numeric_limits<int>::min();
            
            else if (b.beansInPlay(NORTH) + b.beans(NORTH, 0) < b.beans(SOUTH, 0))      // South is in Winning position
                return std::numeric_limits<int>::max();
            
            else                                                    // Tie
                return 0;
        }
        
        // North has no more beans, "sweep" South's Beans
        if (b.beansInPlay(NORTH) == 0)
        {
            if (b.beansInPlay(SOUTH) + b.beans(SOUTH, 0) > b.beans(NORTH, 0))       // South is in Winning Position
                return std::numeric_limits<int>::max();
            
            else if (b.beansInPlay(SOUTH) + b.beans(SOUTH, 0) < b.beans(NORTH, 0))      // North is in Winning Position
                return std::numeric_limits<int>::min();
            
            else                                                    // Tie
                return 0;
        }
    }
    
    // Check for Board Control (i.e. if either side has a majority at a certain state)
    if (b.beansInPlay(SOUTH) + b.beansInPlay(NORTH) + b.beans(NORTH, 0) < b.beans(SOUTH, 0) )       // South has majority of beans, South will win
        return std::numeric_limits<int>::max();

    if (b.beansInPlay(SOUTH) + b.beansInPlay(NORTH) + b.beans(SOUTH, 0) < b.beans(NORTH, 0) )       // North has majority of Beans, Norgh will win
        return std::numeric_limits<int>::min();
        
    
    return ( b.beans(SOUTH, 0) - (b.beans(NORTH, 0)) );         // OTHERWISE, return the difference between SOUTH and NORTH's Pot
}

/*
 void chooseMove(in: player, board; out: bestHole, value):
         if no move for player exists (i.e., game is over),
             bestHole = -1
             value = value of this position (i.e., +∞, -∞, or 0)
             return
         if the criterion says we should not search below this node
             bestHole = -1
             value = value of this position
             return
         for every hole h the player can choose
             "make" the move h
             chooseMove(opponent, board, h2, v2)
             "unmake" the move
             if v2 is better for the player than best seen so far,
                 bestHole = h
                 value = v2
         return
 */


void SmartPlayer::minimax(Side s, const Board &b, int &bestHole, int &value, int currentDepth, int maxDepth, JumpyTimer& timer, double timeLimit) const
{
    if (s == NORTH)
        value = std::numeric_limits<int>::max();        // Initialize Minimizer side to max value
    else
        value = std::numeric_limits<int>::min();        // Initialize Maximizer side to min value
    
    // The game is over when any side cannot make a move
    if ( b.beansInPlay(s) == 0)
    {
        bestHole = -1;
        value = evaluate(b);
        return;
    }
    
    if (timeLimit <= 0)
    {
        bestHole = -1;
        value = evaluate(b);
        return;
    }

    
    // Cap the Search Depth
    if (currentDepth == maxDepth)
    {
        bestHole = -1;
        value = evaluate(b);
        return;
    }


    Side endSide;
    int endHole;
    
    for (int i = 1; i <= b.holes(); i ++)
    {
        // Start timer
        
        // Allocate remaining time limit equally among remaining braches to explore
        double thisBranchTimeLimit = timeLimit / b.holes();
        
        // Save branch start time so can compute the time the branch took
        double startTime = timer.elapsed();
        
        
        // Make the move
        Board temp_Board = b;
        if ( !temp_Board.sow(s, i, endSide, endHole) )
            continue;                                           // If the hole is empty, move to next hole
        
        // Capture
        if (endSide == s && temp_Board.beans(endSide, endHole) - 1 == 0 && temp_Board.beans(opponent(endSide), endHole) != 0)
        {
            temp_Board.moveToPot(endSide, endHole, endSide);
            temp_Board.moveToPot(opponent(endSide), endHole, endSide);
        }
        
        // additional moves, if endhole is pot, sow again while (endshide
        else if (endSide == s && endHole == 0)
        {
            
            if (temp_Board.beansInPlay(endSide) == 0) {
                for (int i = 1; i <= temp_Board.holes(); i++)
                    temp_Board.moveToPot(opponent(endSide), i, opponent(endSide));
               
            }
            
            //            else{
            //
            //                int n = 1;
            //                while (b.beans(s, n) == 0)       // start at the first hole, if hole is empty, move to next hole
            //                    n++;
            //
            //
            //                minimax(endSide, temp_Board, n, value, currentDepth+1, maxDepth, timer, thisBranchTimeLimit);
            //            }
            //
            else
                
                minimax(endSide, temp_Board, endHole, value, currentDepth + 1, maxDepth, timer, thisBranchTimeLimit / temp_Board.holes());
            
        }
        
        
        int bestHole2;
        int value2;
        
        minimax(opponent(s), temp_Board, bestHole2, value2, currentDepth + 1, maxDepth, timer, thisBranchTimeLimit);
        
        if (s == SOUTH)
        {
            if (value <= value2)            // Maximize South's value
            {
                value = value2;
                bestHole = i;
            }
            
        }
        
        if (s == NORTH)
        {
            if (value >= value2)            // Minimize North's value
            {
                value = value2;
                bestHole = i;
            }
        }
        
        timeLimit -= (timer.elapsed() - startTime);
        if (timeLimit <= 0)
            timeLimit = 0;
        
    }
        
    return;
    
}
        

