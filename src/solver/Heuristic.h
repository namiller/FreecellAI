#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "GameState.h"

class Heuristic {
  public:
    virtual double evaluate(const GameState& gs) const = 0;
};

#endif // HEURISTIC_H
