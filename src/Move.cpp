#include "Move.h"
#include <ostream>
#include "Card.h"

using namespace std;

ostream& operator <<(std::ostream& stream, const Move&rhs) {
  return (stream << "(" << rhs.mover << ") " << rhs.src << "->" << rhs.dest);
}

