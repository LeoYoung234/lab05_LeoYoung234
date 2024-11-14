// card.h
// Author: Leo Young
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

class Card
{
public:
    Card(char suit, string rank);

    bool operator==(const Card &other) const;
    bool operator<(const Card &other) const;
    bool operator>(const Card &other) const;

    char getSuit() const;
    string getRank() const;
    string toString() const;

private:
    char suit;
    string rank;
    int rankVal() const;
    int suitVal() const;
};
#endif