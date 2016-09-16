#include <iostream>
#include <vector>
#include "GameState.h"
#include "Move.h"
#include "AStar.h"
#include "CustomHeuristic.h"

using namespace std;

int main() {
  GameState g(123);
 // GameState g(147);
  cout << (solve(g, new CustomHeuristic()) ? "solvable" : "unsolvable") << endl;
//  GameState g("8;7;20;32;45;51,11,49,9;21,33;;12,50,36,48,34,46;25,37,23,35,47;38,24,10,22;;");
  cout << g.serialize() << endl;
  GameState p(g.serialize());
  cout << p.serialize() << endl;

  vector<Move> moves = g.getMoves();
  cout << g << endl;
  cout << p << endl;
  int i = 0;
  for (const auto& m : moves) {
    cout << i++ << ": " <<  m << endl;
  }
  int move;
  while (cin >> move) {
    g = g.apply(moves[move]);
    if (g.isSolved()) {
      cout << "good job!" << endl;
      return 0;
    }
    moves = g.getMoves();
    cout << g.serialize() << endl;
    cout << g << endl;
    int i = 0;
    for (const auto& m : moves) {
      cout << i++ << ": " <<  m << endl;
    }
  }
  return 0;
}
