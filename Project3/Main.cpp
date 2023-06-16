//
//  main.cpp
//  Kalah
//
//  Created by Esmail Mozaffari on 5/19/23.
//


#include "Player.h"
#include "Board.h"
#include "Side.h"
#include "Game.h"
#include <iostream>
#include <cassert>
using namespace std;

void doBoardTests()
{
   // The first set of Tests are provided in the spec by Professor Smallberg //////////////////////////////////////
   Board b(3, 2);
   assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
                   b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
   b.setBeans(SOUTH, 1, 1);
   b.moveToPot(SOUTH, 2, SOUTH);
   assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
               b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
       b.beansInPlay(SOUTH) == 3);
   Side es;
   int eh;
   b.sow(SOUTH, 3, es, eh);
   assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
               b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
       b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
   // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

   Board b2(0, -1);
   assert(b2.holes() == 1 && b2.totalBeans() == 0);    // Test invalid for Board()
   assert(b2.beans(NORTH, -1) == -1);      // Test invalid for beans()
   assert(b2.beans(NORTH, 2) == -1);      // Test invalid for beans()

   Board b3(6,4);
   assert(b3.sow(NORTH, 0, es, eh) == false);      // Test out of bounds
   assert(b3.sow(SOUTH, 0, es, eh) == false);
   assert(b3.sow(NORTH, 7, es, eh) == false);
   assert(b3.sow(SOUTH, 7, es, eh) == false);
   b3.setBeans(NORTH, 6, 0);
   assert(b3.sow(NORTH, 6, es, eh) == false);      // Test Empty Hole
   b3.setBeans(SOUTH, 1, 0);
   assert(b3.sow(SOUTH, 1, es, eh) == false);
   assert(b3.sow(SOUTH, 2, es, eh) == true);
   assert(es == SOUTH && eh == 6);

   Board b4(2, 0);
   b4.setBeans(NORTH, 1, 4);
   b4.sow(NORTH, 1, es, eh);           // Test start at North and end at North (loop around)
   assert(es == NORTH && eh == 2);
   b4.setBeans(SOUTH, 1, 5);
   b4.sow(SOUTH, 1, es, eh);           // Test start at South and end at South (loop around)
   assert(es == SOUTH && eh == 1);
   b4.setBeans(NORTH, 1, 9);
   b4.sow(NORTH, 1, es, eh);            // Two loops around
   assert(es == NORTH && eh == 2);
   b4.setBeans(SOUTH, 1, 10);
   b4.sow(SOUTH, 1, es, eh);            // Two loops around
   assert(es == SOUTH && eh == 1);

   assert(b4.moveToPot(SOUTH, 3, SOUTH) == false);     // Test out of bounds
   assert(b4.moveToPot(SOUTH, 3, NORTH) == false);
   assert(b4.moveToPot(NORTH, 3, NORTH) == false);
   assert(b4.moveToPot(NORTH, 3, SOUTH) == false);
   assert(b4.moveToPot(SOUTH, 0, SOUTH) == false);     // Test out of Bounds
   assert(b4.moveToPot(SOUTH, 0, NORTH) == false);
   assert(b4.moveToPot(NORTH, 0, NORTH) == false);
   assert(b4.moveToPot(NORTH, 0, SOUTH) == false);


}


void doPlayerTests()
{
   // The first set of Tests are provided in the spec by Professor Smallberg //////////////////////////////////////
   HumanPlayer hp("Marge");
   assert(hp.name() == "Marge"  &&  hp.isInteractive());
   BadPlayer bp("Homer");
   assert(bp.name() == "Homer"  &&  !bp.isInteractive());
   SmartPlayer sp("Lisa");
   assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
   Board b(3, 2);
   b.setBeans(SOUTH, 2, 0);
   cout << "=========" << endl;
   int n = hp.chooseMove(b, SOUTH);
   cout << "=========" << endl;
   assert(n == 1  ||  n == 3);
   n = bp.chooseMove(b, SOUTH);
   assert(n == 1  ||  n == 3);
   n = sp.chooseMove(b, SOUTH);
   assert(n == 1  ||  n == 3);
   // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

   HumanPlayer hp2("");
   assert(hp2.name() == ""  &&  hp2.isInteractive());
   BadPlayer bp2("");
   assert(bp2.name() == ""  &&  !bp2.isInteractive());
   SmartPlayer sp2("");
   assert(sp2.name() == ""  &&  !sp2.isInteractive());

   Board b2(3, 0);
   b2.setBeans(NORTH, 1, 3);
   b2.setBeans(NORTH, 0, 3);
   b2.setBeans(SOUTH, 1, 3);
   b2.setBeans(SOUTH, 0, 3);

   assert(bp2.chooseMove(b2, NORTH) == 1) ;     // Only non-empty hole, except pot
   assert(bp2.chooseMove(b2, SOUTH) == 1);      // Only non-empty hole, except pot

   Board b3(3,0);
   assert(hp2.chooseMove(b3, NORTH) == -1);     // Test Human player, no beans
   assert(hp2.chooseMove(b3, SOUTH) == -1);


}


void doGameTests()
{
   // The first set of Tests are provided in the spec by Professor Smallberg //////////////////////////////////////
   SmartPlayer bp1("Bart");
   SmartPlayer bp2("Homer");
   Board b(3, 0);
   b.setBeans(SOUTH, 1, 2);
   b.setBeans(NORTH, 2, 1);
   b.setBeans(NORTH, 3, 2);
   Game g(b, &bp1, &bp2);
   bool over;
   bool hasWinner;
   Side winner;
   //    Homer
   //   0  1  2
   // 0         0
   //   2  0  0
   //    Bart
   g.status(over, hasWinner, winner);
   assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
          g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
          g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

   g.move(SOUTH);
   //   0  1  0
   // 0         3
   //   0  1  0
   g.status(over, hasWinner, winner);
   assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
          g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
          g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

   g.move(NORTH);
   //   1  0  0
   // 0         3
   //   0  1  0
   g.status(over, hasWinner, winner);
   assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
          g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
          g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

   g.move(SOUTH);
   //   1  0  0
   // 0         3
   //   0  0  1
   g.status(over, hasWinner, winner);
   assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
          g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
          g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

   g.move(NORTH);
   //   0  0  0
   // 1         4
   //   0  0  0
   g.status(over, hasWinner, winner);
   assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
          g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
          g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
   assert(hasWinner && winner == SOUTH);
   // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////


//     Replicate the endgame in spec
   SmartPlayer bp3("Bart");
   BadPlayer bp4("Homer");
   Board b2(6, 0);
   b2.setBeans(SOUTH, 0, 16);
   b2.setBeans(NORTH, 0, 22);
   b2.setBeans(SOUTH, 3, 1);
   b2.setBeans(SOUTH, 4, 1);
   b2.setBeans(SOUTH, 5, 1);
   b2.setBeans(SOUTH, 6, 1);
   b2.setBeans(NORTH, 1, 2);
   b2.setBeans(NORTH, 2, 4);
   Game g2(b2, &bp3, &bp4);
   g2.play();      // SmartPlayer v BadPlayer
   /*
    Homer
    2 4 0 0 0 0
    22             16
    0 0 1 1 1 1
    Bart
    Bart chooses hole 6

    Homer
    2 4 0 0 0 0
    22             17
    0 0 1 1 1 0
    Bart
    Bart gets another turn.
    Bart chooses hole 5

    Homer
    2 4 0 0 0 0
    22             17
    0 0 1 1 0 1
    Bart
    Homer chooses hole 1

    Homer
    0 4 0 0 0 0
    23             17
    1 0 1 1 0 1
    Bart
    Bart chooses hole 1

    Homer
    0 0 0 0 0 0
    23             22
    0 0 1 1 0 1
    Bart
    Homer has no beans left to sow.
    Sweeping the remaining beans into Bart's pot.

    Homer
    0 0 0 0 0 0
    23             25
    0 0 0 0 0 0
    Bart
    Bart is the winner.

    */


   // Test if SmartPlayer can beat BadPlayer, regardless of starting side in a proper 6 hole 4 bean Kalah Board from scratch
   SmartPlayer bp5("Bart");        // SmartPlayer on South side
   BadPlayer bp6("Homer");         // BadPlayer on North side
   Board b3(6, 4);
   Game g3(b3, &bp5, &bp6);
   g3.play();                  // Smart Player wins
   // I couldn't show the entire game, and it doesn't make sense to just copy a result, but this is the test I used for testing SmartPlayer in a real game

   BadPlayer bp7("Bart");          // BadPlayer on South side
   SmartPlayer bp8("Homer");       // SmartPlayer on North side
   Board b4(6, 4);
   Game g4(b4, &bp7, &bp8);
   g4.play();                  // Smart Player wins
   // I couldn't show the entire game, and it doesn't make sense to just copy a result, but this is the test I used for testing SmartPlayer in a real game



}



int main()
{
   doBoardTests();
   doPlayerTests();
   doGameTests();
       
   cout << "Passed all tests" << endl;
}
