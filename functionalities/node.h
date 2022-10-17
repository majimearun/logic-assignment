#include <iostream>
#include <string>

using namespace std;

struct node
{
    char data;
    node *left;
    node *right;
    node *parent;
    bool isFilled;
    bool rightFilled;
    bool leftFilled;

    node();
    int fillLeft(node *Node);
    int fillRight(node *Node);
    int fill(char data);
};