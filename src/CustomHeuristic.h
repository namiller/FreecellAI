#ifndef CUSTOM_HEURISTIC_H
#define CUSTOM_HEURISTIC_H

#include "GameState.h"

class CustomHeuristic : Heuristic {
  double evaluate(const GameState& gs);
};

#endif //CUSTOM_HEURISTIC_H
