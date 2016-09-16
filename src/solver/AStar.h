#ifndef A_STAR_H
#define A_STAR_H

#include <vector>
#include "GameState.h"
#include "Move.h"
#include "Heuristic.h"

bool solve(const GameState &start, Heuristic* h);

#endif // A_STAR_H
