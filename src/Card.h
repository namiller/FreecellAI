#ifndef CARD_H
#define CARD_H
#include <vector>
#include "ASCIIviz.h"

class Card {
  private:
    int v;
    static const int CARDS_PER_SUIT = 13;
    std::vector<Card> *container;
  public:
    Card(int v) {container = NULL; this->v = v;}
    Card(int v, std::vector<Card> * p) {container = p; this->v = v;}
    Card() {container = NULL; this->v = -1;}
    void setVal(int v) {this->v = v;}
    int getVal() const {return v;}
    char getSuit() const {return v/CARDS_PER_SUIT;}
    bool isBlack() const {return getSuit() % 2;}
    bool isRed() const { return !(getSuit() % 2);}
    int getNum() const {return v % CARDS_PER_SUIT;};
    bool stacksOn(const Card& other) const {
      return (other.getNum() == (getNum() + 1)) && (other.isBlack() == isRed());
    }
    bool dumpsOn(const Card& top) const {
      if (getNum() == 0) {
        return -4-top.getVal() == getSuit(); 
      }
      return (top.getSuit() == getSuit()) && (top.getNum() == (getNum() - 1));
    }
    friend std::ostream& operator<<(std::ostream &stream, const Card& rhs);
};

#endif // CARD_H
