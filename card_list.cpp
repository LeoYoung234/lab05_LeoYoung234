// card_list.cpp
// Author: Leo Young
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include <iostream>

// constructor and destructor
CardList::CardList()
{
    root = nullptr;
}
CardList::~CardList()
{
    clear(root);
}

// destructor helper
void CardList::clear(Node *n)
{
    if (n)
    {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert and insert helper
bool CardList::insert(const Card &card)
{
    if (!root)
    {
        root = new Node(card);
        return true;
    }
    return insert(card, root);
}
bool CardList::insert(const Card &card, Node *n)
{
    if (card < n->info)
    {
        if (n->left)
            return insert(card, n->left);
        n->left = new Node(card);
        n->left->parent = n;
        return true;
    }
    else if (card > n->info)
    {
        if (n->right)
            return insert(card, n->right);
        n->right = new Node(card);
        n->right->parent = n;
        return true;
    }
    return false;
}

// print print helper
void CardList::printInOrder() const
{
    printInOrder(root);
}
void CardList::printInOrder(Node *n) const
{
    if (n)
    {
        printInOrder(n->left);
        cout << n->info.toString() << endl;
        printInOrder(n->right);
    }
}

// get node
CardList::Node *CardList::getNodeFor(const Card &card, Node *n) const
{
    if (!n)
        return nullptr;
    if (card == n->info)
        return n;
    if (card > n->info)
        return getNodeFor(card, n->right);
    if (card < n->info)
        return getNodeFor(card, n->left);
    return nullptr;
}

// contains and isempty
bool CardList::contains(const Card &card) const
{
    return getNodeFor(card, root) != nullptr;
}
bool CardList::isEmpty() const
{
    return (root == nullptr);
}

// getmin and getmax
Card CardList::getMin() const
{
    if (!root)
        return Card('X', "MISSINGRANK");
    Node *curr = root;
    while (curr->left)
    {
        curr = curr->left;
    }
    return curr->info;
}
Card CardList::getMax() const
{
    if (!root)
        return Card('X', "MISSINGRANK");
    Node *curr = root;
    while (curr->right)
    {
        curr = curr->right;
    }
    return curr->info;
}

// getsuccessor and getsuccessornode
Card CardList::getSuccessor(const Card &card) const
{
    CardList::Node *n = getSuccessorNode(card);
    if (!n)
        return Card('X', "MISSINGRANK");
    return n->info;
}
CardList::Node *CardList::getSuccessorNode(const Card &card) const
{
    CardList::Node *n = getNodeFor(card, root);
    CardList::Node *succ = nullptr;

    if (!n)
    {
        return nullptr;
    }
    if (n->right)
    {
        succ = n->right;
        while (succ->left)
            succ = succ->left;
        return succ;
    }
    succ = n->parent;
    while (succ && succ->info < card)
        succ = succ->parent;
    return succ;
}

// getpredecessor and getpredecessornode
Card CardList::getPredecessor(const Card &card) const
{
    CardList::Node *n = getPredecessorNode(card);
    if (!n)
        return Card('X', "MISSINGRANK");
    return n->info;
}
CardList::Node *CardList::getPredecessorNode(const Card &card) const
{
    CardList::Node *n = getNodeFor(card, root);
    CardList::Node *pred = nullptr;
    if (!n)
        return nullptr;
    if (n->left)
    {
        pred = n->left;
        while (pred->right)
            pred = pred->right;
        return pred;
    }
    pred = n->parent;
    while (pred && pred->info > card)
        pred = pred->parent;
    return pred;
}

bool CardList::remove(const Card &card)
{
    CardList::Node *n = getNodeFor(card, root);

    if (!n)
        return false;
    if (!n->left && !n->right)
    {
        if (!n->parent)
            root = nullptr;
        else if (n == n->parent->left)
            n->parent->left = nullptr;
        else
            n->parent->right = nullptr;
        delete n;
        return true;
    }
    if (n->left && n->right)
    {
        Card succ_card = getSuccessor(card);
        remove(succ_card);
        n->info = succ_card;
        return true;
    }
    if (n->left)
    {
        if (!n->parent)
            root = n->left;
        else if (n == n->parent->left)
            n->parent->left = n->left;
        else
            n->parent->right = n->left;
        n->left->parent = n->parent;
        delete n;
        return true;
    }
    if (n->right)
    {
        if (!n->parent)
            root = n->right;
        else if (n == n->parent->left)
            n->parent->left = n->right;
        else
            n->parent->right = n->right;
        n->right->parent = n->parent;
        delete n;
        return true;
    }
    return false;
}