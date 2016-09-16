#include <vector>
#include "GameState.h"
#include "Move.h"
#include "Heuristic.h"

#include <queue>
#include <set>
#include <iostream>

using namespace std;

struct node {
  int depth;
  GameState state;

  node(const GameState &s) : state(s){
    depth = 0;
  }
  node(const node& parent, const Move &m) : state(parent.state.apply(m)) {
    depth = parent.depth + 1;
  }
};

bool solve(const GameState &start, Heuristic* h) {
  auto cmp = [h](const node& left, const node &right) {
    double lc = h->evaluate(left.state);
    double rc = h->evaluate(right.state);
    if (lc == rc) {
      return left.state.getMoves().size() > right.state.getMoves().size();
    }
    return lc > rc; 
  };
  
  priority_queue<node, vector<node>, decltype(cmp)> expansions(cmp);
  set<long> seenHashes;

  expansions.push(node(start));
  seenHashes.insert(start.hash());

  while (!expansions.empty()) {
    node top = expansions.top();
    //cout << h->evaluate(top.state) << endl;
    //cout << top.state << endl;
    if (top.state.isSolved()) {
      return true;
    }
    expansions.pop();
    const vector<Move> &options = top.state.getMoves();
    for (const auto &move : options) {
      node child(top, move);
      long hash = child.state.hash();
      if (seenHashes.count(hash)) {
        continue;
      } else {
        expansions.push(child);
        seenHashes.insert(hash);
      }
    }
  }
  return false;
}

