#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <array>
#include "Card.h"
#include "Move.h"

class GameState {
  private:
    std::array<std::vector<Card>, 7> stacks; // TODO: could be nice as ll
    std::vector<Card> buffer;
    std::array<Card, 4> dump; //only stores top card.
  public:
    GameState(int seed);
    unsigned long hash() const;
    const std::array<std::vector<Card>, 7>& getStacks() const {return stacks;}
    const std::vector<Card>& getBuffer() const {return buffer;}
    const std::array<Card, 4>& getDump() const {return dump;}
    int getMoveCapacity() const {return 5 - buffer.size();}
    std::vector<Move> getMoves() const;
    GameState apply(const Move &m) const;
};

#endif // GAMESTATE_H
