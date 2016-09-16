#include "CustomHeuristic.h"

#include <algorithm>
#include "GameState.h"

using namespace std;


// cards in the cells cost the depth of the closest stackable location without the same colored card in front.
// cost is doubled if 2 of the same are up.
// free column is worth -10
//
// each column has a cost of the sum of out of order cards.
double CustomHeuristic::evaluate(const GameState& gs) const {
  double score = 0;
  int i = 0;
  // TODO: invalidate used cards so that there is no group discount...
  for (const auto & card : gs.getBuffer()) {
    double cost = 100;
    for (const auto & stack : gs.getStacks()) {
      if (stack.size() == 0) {
        cost = 0;
      }
      for (int i = 0; i < stack.size(); i++) {
        if (card.stacksOn(stack[stack.size() - i])) {
          cost = min((double)i, cost);
        }
      }
    }
    // penalty for repeate.. rudimentary.
    for (int j = 0; j < i; j++) {
      if (gs.getBuffer()[i] == gs.getBuffer()[j]) {
        cost *= 2;
      }
    }
    score+=cost;
    i++;
  }
  for (const auto &stack : gs.getStacks()) {
    for (int i = 1; i < stack.size(); i++) {
      if (stack[i].getNum() > stack[i - 1].getNum()) {
        score++; // or score += (stack.size() - i) / 2;
      }
    }
  }
  return score;  
}
