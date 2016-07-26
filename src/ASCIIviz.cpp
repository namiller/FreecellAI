#include "ASCIIviz.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Card.h"
#include "GameState.h"

using namespace std;

string getString(const Card& c) {
  if (c.getVal() == -1) {
    return "XXX";
  }
  if (c.getVal() == -3) {
    return "XhX";
  }
  if (c.getVal() == -4) {
    return "XsX";
  }
  if (c.getVal() == -5) {
    return "XdX";
  }
  if (c.getVal() == -6) {
    return "XcX";
  }
  string ret = " ";
  int i = c.getNum();
  if (i < 9 && i > 0) {
    ret += char('1' + i);
  } else if (i == 9) {
    ret = "10";
  } else if (i == 0) {
    ret = " A";
  } else if (i == 10) {
    ret = " J";
  } else if (i == 11) {
    ret = " Q";
  } else if (i == 12) {
    ret = " K";
  }
  int s = c.getSuit();
  if (s == 0) {
    ret += 's';
  } else if (s == 1) {
    ret += 'h';
  } else if (s == 2) {
    ret += 'c';
  } else if (s == 3) {
    ret += 'd';
  }
  return ret;
}

string getString(const GameState& s) {
  stringstream ss;
  ss << s.hash() << endl;
  ss << "|";
  for (int i = 0; i < 4; i++) {
    if (i < s.getBuffer().size()) {
      ss << getString(s.getBuffer()[i]) << "|";
    } else {
      ss << "   |";
    }
  }
  ss << "   |";
  for (int i = 0; i < 4; i++) {
    ss << getString(s.getDump()[i]) << "|";
  }
  ss << endl;
  for (const auto& card : s.getBuffer()) {
    ss << getString(card) << "|";
  }
  int max_depth = 0;
  for (const auto& stack : s.getStacks()) {
    max_depth = max(max_depth, (int)stack.size());
  }
  for (int i = 0; i < max_depth; i++) {
    for (const auto& stack : s.getStacks()) {
      if (stack.size() > i) {
        ss << " " << getString(stack[i]) << " ";
      } else {
        ss << "     ";
      }
    }
    ss << endl;
  }
  return ss.str();  
}
