#include "GameState.h"

#include <vector>
#include <deque>
#include <sstream>
#include <cstdlib>
#include "Card.h"
#include "Move.h"
#include <string>

using namespace std;

vector<Card> v_parse(string s) {
  istringstream ss(s);
  string n;
  vector<Card> ret;
  while(getline(ss, n, ',')) {
    ret.push_back(Card(stoi(n)));
  }
  return ret;
}

GameState::GameState(string serial) {
  istringstream ss(serial);
  string vect;
  getline(ss, vect, ';');
  buffer = v_parse(vect);
  for (int i = 0; i < 4; i++) {
    getline(ss, vect, ';');
    dump[i] = v_parse(vect)[0];
  }
  for (int i = 0; i < 7; i++) {
    getline(ss, vect, ';');
    stacks[i] = v_parse(vect);
  }
}

string v_serialize(vector<Card> vc) {
  stringstream ss;
  for (int i = 0; i < vc.size(); i++) {
    ss << vc[i].getVal();
    if (i != vc.size() - 1)
      ss << ",";
  }
  ss << ";";
  return ss.str();
}

string GameState::serialize() const {
  stringstream ss;
  ss << v_serialize(buffer);
  for (int i = 0; i < 4; i++) {
    vector<Card> v;
    v.push_back(dump[i]);
    ss << v_serialize(v);
  }
  for (int i = 0; i < 7; i++) {
    ss << v_serialize(stacks[i]);
  }
  return ss.str();
}

GameState::GameState(const GameState& cpy) {
  this->stacks = cpy.stacks;
  this->buffer = cpy.buffer;
  this->dump = cpy.dump;
}

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

bool GameState::isSolved() const {
  for (const auto stack : stacks) {
    for (int i = 1; i < stack.size(); i++) {
      if (stack[i].getNum() > stack[i-1].getNum()) {
        return false;
      }
    }
  }
  return true;
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
    if (stacks[src - 8].empty()) {
      continue;
    }
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
  GameState nState = *this; //copy.
  vector<Card> moving;
  // Source.
  if (m.src < 4) {
    moving.push_back(nState.buffer[m.src]);
    nState.buffer.erase(nState.buffer.begin() + m.src);
  } else if (m.src < 8) {
    // Illegal move.
  } else {
    do {
      moving.push_back(nState.stacks[m.src - 8].back());
      nState.stacks[m.src - 8].pop_back();
    } while (m.mover != moving.back());
  }
  // Destination.
  if (m.dest < 4) {
    nState.buffer.push_back(moving[0]);
  } else if (m.dest < 8) {
    nState.dump[m.dest - 4] = moving[0];
  } else {
    for (int i = 0; i < moving.size(); i++) {
      nState.stacks[m.dest - 8].push_back(moving[moving.size() - 1 - i]);
    }
  }
  return nState;
}

string private_getString(const GameState& s) {
  stringstream ss;
  ss << s.hash() << endl;
  ss << "|";
  for (int i = 0; i < 4; i++) {
    if (i < s.getBuffer().size()) {
      ss << s.getBuffer()[i] << "|";
    } else {
      ss << "   |";
    }
  }
  ss << "   |";
  for (int i = 0; i < 4; i++) {
    ss << s.getDump()[i] << "|";
  }
  ss << endl;
  int max_depth = 0;
  for (const auto& stack : s.getStacks()) {
    max_depth = max(max_depth, (int)stack.size());
  }
  for (int i = 0; i < max_depth; i++) {
    for (const auto& stack : s.getStacks()) {
      if (stack.size() > i) {
        ss << " " << stack[i] << " ";
      } else {
        ss << "     ";
      }
    }
    ss << endl;
  }
  return ss.str();
}


ostream& operator <<(ostream& stream, const GameState &rhs) {
  return stream << private_getString(rhs);
}
