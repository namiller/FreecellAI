#ifndef CUSTOM_HEURISTIC_H
#define CUSTOM_HEURISTIC_H

#include "GameState.h"
#include "Heuristic.h"

class CustomHeuristic : public Heuristic {
  public:
    double evaluate(const GameState& gs) const;
};

#endif //CUSTOM_HEURISTIC_H
