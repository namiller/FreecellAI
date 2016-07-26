#include "GameState.h"

#include <vector>
#include <deque>
#include <cstdlib>
#include "Card.h"
#include "Move.h"

using namespace std;

GameState::GameState(int seed) {
  srand(seed);
  deque<int> bank;
  for (int i = 0; i < 52; i++) {
    bank.push_front(i);
  }
  for (int i = 0; i < 7; i++) {
    for (int c = 0; c < (i < 3 ? 8 : 7); c++) {
      int idx = rand() % bank.size();
      stacks[i].push_back(Card(bank[idx], &(stacks[i])));
      bank.erase(bank.begin() + idx);
    }
  }
  for (int i = 0; i < 4; i++) {
    dump[i] = Card(-4-i);
  }
}

unsigned long hash_c(unsigned long seed, Card v) {
  return seed ^ (v.getVal() + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

unsigned long hash_i(unsigned long seed, unsigned long v) {
  return seed ^ (v + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

unsigned long hash_v(unsigned long seed, vector<Card> v) {
  for (auto &e : v) {
    seed = hash_c(seed, e);
  }
  return seed;
}

unsigned long GameState::hash() const {
  unsigned long seed = 0;
  for (const auto& v : stacks) {
    seed = hash_v(seed, v);
    seed = hash_i(seed, 0x12345678);
  }
  seed = hash_i(seed, buffer.size());
  seed = hash_c(seed, dump[0]);
  seed = hash_c(seed, dump[1]);
  seed = hash_c(seed, dump[2]);
  seed = hash_c(seed, dump[3]);
  return seed;
}

vector<Move> GameState::getMoves() const {
  vector<Move> ret;
  // buffer to ...
  int src = 0;
  for (const auto &card : buffer) {
    // dump
    for (int dst = 4; dst < 8; dst++) {
      if (card.dumpsOn(dump[dst - 4])) {
        ret.push_back(Move(card, src, dst));
      }
    }
    int dst = 8;
    // stack
    for (const auto &stack : stacks) {
      if (stack.empty() || card.stacksOn(stack.back())) {
        ret.push_back(Move(card, src, dst));
      }
      dst++;
    }
    src++;
  }
  src = 8;
  // stack to ...
  for (src = 8; src < 15; src++) {
    // stack
    for (int dst = 8; dst < 15; dst++) {
      if (dst == src) continue;
      for (int depth = 1; depth <= getMoveCapacity() && depth <= stacks[src - 8].size(); depth++) {
        int x = stacks[src - 8].size() - depth;
        if (stacks[dst - 8].empty() || stacks[src - 8][x].stacksOn(stacks[dst - 8].back())) {
          ret.push_back(Move(stacks[src - 8][x], src, dst));
        }
        if (x == 0 || !stacks[src - 8][x].stacksOn(stacks[src - 8][x-1])) {
          break;
        }
      }
    }
    Card card = stacks[src - 8].back();
    // dump
    for (int dst = 4; dst < 8; dst++) {
      if (card.dumpsOn(dump[dst - 4])) {
        ret.push_back(Move(card, src, dst));
      }
    }

    // buffer
    if (int dst = buffer.size() < 4) {
      ret.push_back(Move(card, src, dst));
    }
  }
  
  return ret;
}

GameState GameState::apply(const Move &m) const {
  return *this;
}

