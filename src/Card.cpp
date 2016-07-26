#include "Card.h"
#include <ostream>

using namespace std;

string private_getString(const Card& c) {
  if (c.getVal() == -1) {
    return "XXX";
  }
  if (c.getVal() == -4) {
    return "XsX";
  }
  if (c.getVal() == -5) {
    return "XhX";
  }
  if (c.getVal() == -6) {
    return "XcX";
  }
  if (c.getVal() == -7) {
    return "XdX";
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

ostream& operator <<(ostream& stream, const Card&rhs) {
  return stream << private_getString(rhs);
}
