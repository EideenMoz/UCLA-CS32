//
//  Game.hpp
//  Rabbits
//
//  Created by Esmail Mozaffari on 4/6/23.
//

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <string>

class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};

#endif /* Game_INCLUDED */
