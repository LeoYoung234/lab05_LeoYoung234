// card_list.h
// Author: Leo Young
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
class CardList
{
public:
    CardList();
    ~CardList();

    bool insert(const Card &card);
    bool remove(const Card &c);
    bool contains(const Card &card) const;
    bool isEmpty() const;
    Card getSuccessor(const Card &card) const;
    Card getPredecessor(const Card &card) const;
    Card getMin() const;
    Card getMax() const;
    void printInOrder() const;

private:
    struct Node
    {
        Card info;
        Node *left;
        Node *right;
        Node *parent;

        Node(Card c) : info(c), left(0), right(0), parent(0) { }
    };

    Node *root;

    Node *getSuccessorNode(const Card &card) const;
    Node *getPredecessorNode(const Card &card) const;
    Node *getNodeFor(const Card &card, Node *n) const;

    bool insert(const Card &card, Node *n);
    void clear(Node *n);
    void printInOrder(Node *n) const;
};

#endif
