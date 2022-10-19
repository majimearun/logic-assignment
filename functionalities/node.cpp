#include <iostream>
#include <string>
#include "node.h"

using namespace std;

node::node()
{
    data = ' ';
    left = nullptr;
    right = nullptr;
    isFilled = false;
    rightFilled = false;
    leftFilled = false;
    truth = false;
    isTruthAssigned = false;
}

int node::fillLeft(node *Node)
{
    if (leftFilled == false)
    {
        left = Node;
        leftFilled = true;
        return 0;
    }
    else
    {
        return -1;
    }
}

int node::fillRight(node *Node)
{
    if (rightFilled == false)
    {
        right = Node;
        rightFilled = true;
        return 0;
    }
    else
    {
        return -1;
    }
}

int node::fill(char data)
{
    if (isFilled == false)
    {
        this->data = data;
        isFilled = true;
        return 0;
    }
    else
    {
        return -1;
    }
}