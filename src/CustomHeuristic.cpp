#include "GameState.h"
#include "CustomHeuristic"

using namespace std;


// cards in the cells cost the depth of the closest stackable location without the same colored card in front.
// cost is doubled if 2 of the same are up.
// free column is worth -10
//
// each column has a cost of the sum of out of order cards.
double CustomHeuristic::evaluate(const GameState& gs) {
  double score = 0;
  
}
