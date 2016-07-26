#include <iostream>
#include <vector>
#include "src/GameState.h"
#include "src/Move.h"

using namespace std;

int main() {
//  GameState g(123);
  GameState g(147);
  cout << Card(12) << endl;
  vector<Move> moves = g.getMoves();
  cout << g << endl;
  cout << moves.size() << endl;
  for (const auto& m : moves) {
    cout << m << endl;
  }
  return 0;
}
