#include <iostream>
#include <vector>
#include "GameState.h"
#include "Move.h"

using namespace std;

string t1 = "8;7;20;32;45;51,11,49,9;21,33;;12,50,36,48,34,46;25,37,23,35,47;38,24,10,22;;";

int main(){
  GameState g(t1);
  cout << g << endl;
  cout << "getting moves" << endl;
  vector<Move> moves = g.getMoves();
  cout << "applying" << endl;
  cout << moves.back() << endl;
  g = g.apply(moves.back());
  cout << "done" << endl;
  cout << g << endl;
  cout << "new moves:" << endl;
  cout << g.getMoves().size() << endl;
  return 0;
}
