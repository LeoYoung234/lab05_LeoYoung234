// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

Card seeCards(const string &line)
{
  char suitChar = line[0];
  string rankStr = line.substr(2);
  return Card(suitChar, rankStr);
}

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argv[1]);
  ifstream cardFile2(argv[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail())
  {
    cout << "Could not open file " << argv[2];
    return 1;
  }

  set<Card> aliceCards;
  set<Card> bobCards;

  // Read each file
  while (getline(cardFile1, line) && (line.length() > 0))
  {
    aliceCards.insert(seeCards(line));
  }

  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0))
  {
    bobCards.insert(seeCards(line));
  }

  cardFile2.close();

  bool aliceTurn = true;
  auto it = aliceCards.begin();
  auto rit = bobCards.rbegin();

  while (!aliceCards.empty() && !bobCards.empty())
  {
    bool madeMove = false;
    if (aliceTurn)
    {
      while (it != aliceCards.end())
      {
        if (bobCards.find(*it) != bobCards.end())
        {
          cout << "Alice picked matching card " << it->toString() << endl;
          bobCards.erase(*it);
          it = aliceCards.erase(it);
          madeMove = true;
          aliceTurn = false;
          break;
        }
        else
        {
          ++it;
        }
      }
      if (it == aliceCards.end())
        aliceTurn = false;
    }
    else
    {
      while (rit != bobCards.rend())
      {
        if (aliceCards.find(*rit) != aliceCards.end())
        {
          cout << "Bob picked matching card " << rit->toString() << endl;
          aliceCards.erase(*rit);
          rit = decltype(rit)(bobCards.erase(next(rit).base()));
          madeMove = true;
          aliceTurn = true;
          break;
        }
        else
        {
          ++rit;
        }
      }
      if (rit == bobCards.rend())
        aliceTurn = true;
    }
    if (!madeMove)
      break;
  }

  cout << "\n Alice's cards:\n";
  for (const auto &card : aliceCards)
  {
    cout << card.toString() << endl;
  }
  cout << "\n Bob's cards:\n";
  for (const auto &card : bobCards)
  {
    cout << card.toString() << endl;
  }

  return 0;
}