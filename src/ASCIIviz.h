#ifndef ASCII_VIZ_H
#define ASCII_VIZ_H
#include <string>

class Card;
class GameState;

std::string getString(const Card& c);
std::string getString(const GameState& s);

#endif // ASCII_VIZ_H
