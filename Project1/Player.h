//
//  Player.hpp
//  Rabbits
//
//  Created by Esmail Mozaffari on 4/6/23.
//

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <string>

class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Player declaration.

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    std::string dropPoisonedCarrot();
    std::string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

#endif /* PLAYER_INCLUDED */
