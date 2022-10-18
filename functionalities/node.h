#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

class node
{
public:
    char data;
    node *left;
    node *right;
    bool isFilled;
    bool rightFilled;
    bool leftFilled;
    bool truth;

    node();
    int fillLeft(node *Node);
    int fillRight(node *Node);
    int fill(char data);
};

#endif