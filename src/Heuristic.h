#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "GameState.h"

class Heuristic {
  virtual double evaluate(const GameState& gs);
};

#endif // HEURISTIC_H
