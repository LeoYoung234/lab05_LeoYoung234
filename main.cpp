// This file should implement the game using a custom implementation of a BST (that is based on your implementation from lab02)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
// Do not include set in this file

using namespace std;

Card seeCard(const string &line)
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

  CardList aliceCards;
  CardList bobCards;

  // Read each file
  while (getline(cardFile1, line) && (line.length() > 0))
  {
    aliceCards.insert(seeCard(line));
  }

  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0))
  {
    bobCards.insert(seeCard(line));
  }

  cardFile2.close();

  bool aliceTurn = true;

  Card aliceCurrCard = aliceCards.getMin();
  Card bobCurrCard = bobCards.getMin();

  while (!aliceCards.isEmpty() && !bobCards.isEmpty())
  {
    bool madeMove = false;
    if (aliceTurn)
    {
      aliceCurrCard = aliceCards.getMin();
      while (aliceCurrCard.getSuit() != 'X')
      {
        if (bobCards.contains(aliceCurrCard))
        {
          cout << "Alice picked matching card " << aliceCurrCard.toString() << endl;
          bobCards.remove(aliceCurrCard);
          aliceCards.remove(aliceCurrCard);
          madeMove = true;
          aliceTurn = false;
          break;
        }
        aliceCurrCard = aliceCards.getSuccessor(aliceCurrCard);
      }
      if (aliceCurrCard.getSuit() == 'X')
        break;
    }
    else
    {
      bobCurrCard = bobCards.getMax();
      while (bobCurrCard.getSuit() != 'X')
      {
        if (aliceCards.contains(bobCurrCard))
        {
          cout << "Bob picked matching card " << bobCurrCard.toString() << endl;
          aliceCards.remove(bobCurrCard);
          bobCards.remove(bobCurrCard);
          madeMove = true;
          aliceTurn = true;
          break;
        }
        bobCurrCard = bobCards.getPredecessor(bobCurrCard);
      }
      if (bobCurrCard.getSuit() == 'X')
        break;
    }
    if (madeMove == false)
      break;
  }

  cout << "\n Alice's cards:\n";
  aliceCards.printInOrder();

  cout << "\n Bob's cards: \n";
  bobCards.printInOrder();

  return 0;
}