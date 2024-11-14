// card.cpp
// Author: Leo Young
// Implementation of the classes defined in card.h

#include "card.h"

Card::Card(char suit, string rank)
{
    this->suit = suit;
    this->rank = rank;
}

char Card::getSuit() const
{
    return suit;
}
string Card::getRank() const
{
    return rank;
}

string Card::toString() const
{
    return string(1, getSuit()) + " " + getRank();
}

int Card::rankVal() const
{
    if (rank == "a")
        return 1;
    if (rank == "j")
        return 11;
    if (rank == "q")
        return 12;
    if (rank == "k")
        return 13;
    return stoi(rank);
}

int Card::suitVal() const
{
    if (suit == 'c')
        return 1;
    if (suit == 'd')
        return 2;
    if (suit == 's')
        return 3;
    if (suit == 'h')
        return 4;
    return 0;
}

bool Card::operator==(const Card &other) const
{
    return (suit == other.suit && rank == other.rank);
}

bool Card::operator<(const Card &other) const
{
    if (suit != other.suit)
        return (suitVal() < other.suitVal());
    return (rankVal() < other.rankVal());
}

bool Card::operator>(const Card &other) const
{
    if (suit != other.suit)
        return (suitVal() > other.suitVal());
    return (rankVal() > other.rankVal());
}
