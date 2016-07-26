#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <ostream>
#include "Card.h"

class GameState;

/*
 * | 0 | 1 | 2 | 3 | --- | 4 | 5 | 6 | 7 |
 *
 *
 *   8   9  10  11  12  13  14  15
 *   |   |   |   |   |   |   |   |
 *   v   v   v   v   v   v   v   v
 *
 */

class Move {
  public:
    Card mover;
    int src;
    int dest;
    Move(const Card m, int src, int dest) {
      mover = m;
      this->src = src;
      this->dest = dest;
    }

    friend std::ostream& operator <<(std::ostream& stream, const Move&rhs);
};

#endif // MOVE_H
