//
//  Game.cpp
//  Kalah
//
//  Created by Esmail Mozaffari on 5/19/23.
//

#include "Game.h"
#include "Board.h"
#include "Side.h"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

Game::Game(const Board& b, Player* south, Player* north) : m_board(b)
// Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
{
    m_SouthPlayer = south;
    m_NorthPlayer = north;
    m_currentTurn = SOUTH;
}


void Game::display() const
// Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
{
    // North's Name
    cout << string(m_board.holes(), ' ') << m_NorthPlayer->name() << endl;
    
    // North's Holes
    cout << string(2, ' ');
    for (int i = 1; i <= m_board.holes(); i++)
        cout << ' ' << m_board.beans(NORTH, i);
    
    // North's Pot
    cout << endl << ' ' << m_board.beans(NORTH, 0);
    
    cout << string( (m_board.holes() * 2) + 1, ' ');
    
    // South's Pot
    cout << m_board.beans(SOUTH, 0) << endl;
    
    // South's Holes
    cout << string(2, ' ');
    for (int i = 1; i <= m_board.holes(); i++)
        cout << ' ' << m_board.beans(SOUTH, i);
    
    // South's Name
    cout << endl << string(m_board.holes(), ' ') << m_SouthPlayer->name() << endl;
    
}


void Game::status(bool& over, bool& hasWinner, Side& winner) const
// If the game is over (i.e., the move member function has been called and returned false), set over to true; otherwise, set over to false and do not change anything else. If the game is over, set hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
{
    // There are still beans in play, game is not over
    if (!isOver) {
        over = false;
        return;
    }
    
    // Otherwise, the game is over
    over = true;
    
    if (m_board.beans(NORTH, 0) > m_board.beans(SOUTH, 0)) {        // North Wins
        winner = NORTH;
        hasWinner = true;
    }
    else if (m_board.beans(NORTH, 0) < m_board.beans(SOUTH, 0)) {       // South Wins
        winner = SOUTH;
        hasWinner = true;
    }
    else                                        // Tie
        hasWinner = false;
    
}


bool Game::move(Side s)
// Attempt to make a complete move for the player playing side s. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. Whenever the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening. If the move can be completed, return true; if not, because the move is not yet completed but side s has no holes with beans to pick up and sow, sweep any beans in s's opponent's holes into that opponent's pot and return false.
{
    int chosenHole, endHole;
    Side endSide;
    Player* currentPlayer;
    
    if (s == NORTH)
        currentPlayer = m_NorthPlayer;
    else
        currentPlayer = m_SouthPlayer;
    
    // The game is over
    if (m_board.beansInPlay(s) == 0)
    {
        Sweep(s);                       // If our side has no beans, Sweeps Opponent's Beans
        isOver = true;
        return false;
    }
    
    
    chosenHole = currentPlayer->chooseMove(m_board, s);
    m_board.sow(s, chosenHole, endSide, endHole);
    cout << currentPlayer->name() << " chooses hole " << chosenHole << endl << endl;
    
//    cerr << chosenHole << endl;
//    cerr << endHole << endl;
    
    // Capture
    if (endSide == s && m_board.beans(s, endHole) - 1 == 0 && m_board.beans(opponent(s), endHole) != 0 && endHole != 0)
    {
        m_board.moveToPot(s, endHole, s);
        m_board.moveToPot(opponent(s), endHole, s);
    }
    
    
    
    // Landing in a pot gets another turn
    while (endSide == s && endHole == 0)
    {
        display();
        cout << currentPlayer->name() << " gets another turn." << endl;
//        cout << "Press enter to continue." << endl;
//        cin.ignore();
        
        if (m_board.beansInPlay(s) == 0)
        {
            Sweep(s);   // Player on Side s cannot make any moves, sweep the opponenets beans into their pot, end game
            isOver = true;
            return false;
        }
        
        chosenHole = currentPlayer->chooseMove(m_board, s);
        
        m_board.sow(s, chosenHole, endSide, endHole);
        cout << currentPlayer->name() << " chooses hole " << chosenHole << endl << endl;
        
        // Capture
        if (endSide == s && m_board.beans(s, endHole) - 1 == 0 && m_board.beans(opponent(s), endHole) != 0 && endHole != 0)
        {
            m_board.moveToPot(s, endHole, s);
            m_board.moveToPot(opponent(s), endHole, s);
            break;
        }
        
    }
    
    
    isOver = false;
    return true;
    
}


void Game::play()
// Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function.
{
    bool hasWinner;
    Side winner;
    
    
    do
    {
        display();
        
        if ( !m_SouthPlayer->isInteractive() && !m_NorthPlayer->isInteractive() )
        {
            cout << "Press ENTER to continue." << endl;
            cin.ignore();
        }
        
        move(m_currentTurn);
        status(isOver, hasWinner, winner);
        m_currentTurn = opponent(m_currentTurn);
        
    } while (!isOver);
    
    if (hasWinner)
    {
        if (winner ==  NORTH)
            cout << m_NorthPlayer->name() << " is the winner." << endl;
        else
            cout << m_SouthPlayer->name() << " is the winner." << endl;
    }
    
    else
        cout << "The game resulted in a tie." << endl;
    
    
    
}


int Game::beans(Side s, int hole) const
// Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
{
    if (hole < 0 || hole > m_board.holes())
        return -1;
    
    return m_board.beans(s, hole);
}


void Game::Sweep(Side s)
{
    // If it's North's turn, and North has no more beans in play, sweep South's beans into South's pot
    if (s == NORTH)
    {
        for (int i = 1; i <= m_board.holes(); i++)
            m_board.moveToPot(SOUTH, i, SOUTH);
        
        cout << m_NorthPlayer->name() << " has no beans left to sow." << endl;
        cout << "Sweeping the remaining beans into " << m_SouthPlayer->name() << "'s pot." << endl;
        cout << endl;
        display();
    }
    // If it's South's turn, and South has no more beans in play, sweep North's beans in North's pot
    else
    {
        for (int i = 1; i <= m_board.holes(); i++)
            m_board.moveToPot(NORTH, i, NORTH);
        
        cout << m_SouthPlayer->name() << " has no beans left to sow." << endl;
        cout << "Sweeping the remaining beans into " << m_NorthPlayer->name() << "'s pot." << endl;
        cout << endl;
        display();
    }
}
