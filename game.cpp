#include <iostream>
#include <vector>
#include "src/GameState.h"
#include "src/ASCIIviz.h"
#include "src/Move.h"

using namespace std;

int main() {
//  GameState g(123);
  GameState g(125);
  cout << Card(12) << endl;
  vector<Move> moves = g.getMoves();
  cout << getString(g) << endl;
  cout << moves.size() << endl;
  for (const auto& m : moves) {
    cout << m << endl;
  }
  return 0;
}
