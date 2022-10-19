#include "./functionalities/node.h"
#include "./functionalities/utils.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct result
{
    node *root;
    int count;
};
result *tree;
bool implicationOperator(node *left, node *right)
{
    if (left->truth)
    {
        return right->truth;
    }
    else
    {
        return true;
    }
}
bool andOperator(node *left, node *right)
{
    if (left->truth)
    {
        return right->truth;
    }
    else
    {
        return false;
    }
}
bool orOperator(node *left, node *right)
{
    if (left->truth)
    {
        return true;
    }
    else
    {
        return right->truth;
    }
}
bool notOperator(node *right)
{
    if (right->truth)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void atomAssignment(node *head)
{
    if (!utils::isOperator(head->data)) // if head is a propositional atom
    {
        if (head->isTruthAssigned == false)
        {
            head->truth = true;
            head->isTruthAssigned = true;
        }
        else
        {
            return;
        }
    }
    if (head->data != '~')
    {
        if ((!utils::isOperator(head->left->data)) && (head->left->isTruthAssigned == false)) // if left is an atom
        {
            head->left->truth = true;
            head->left->isTruthAssigned = true;
        }
    }
    if (!utils::isOperator(head->right->data) && head->right->isTruthAssigned == false) // if right is an atom
    {
        head->right->truth = true;
        head->right->isTruthAssigned = true;
    }
    if (head->data != '~')
    {
        if (utils::isOperator(head->left->data))
        {
            atomAssignment(head->left);
        }
    }
    else
    {
        atomAssignment(head->right);
    }
    if (utils::isOperator(head->right->data))
    {
        atomAssignment(head->right);
    }
}

void truthValue(node *head)
{
    if (head->data != '~')
    {
        if (head->left->isTruthAssigned == false)
        {
            truthValue(head->left);
        }
    }
    if (head->right->isTruthAssigned == false)
    {
        truthValue(head->right);
    }

    if (head->data == '+')
    {
        head->truth = orOperator(head->left, head->right);
        head->isTruthAssigned == true;
    }
    else if (head->data == '*')
    {
        head->truth = andOperator(head->left, head->right);
        head->isTruthAssigned == true;
    }
    else if (head->data == '>')
    {
        head->truth = implicationOperator(head->left, head->right);
        head->isTruthAssigned == true;
    }
    else if (head->data == '~')
    {
        head->truth = notOperator(head->right);
        head->isTruthAssigned == true;
    }
}
int main()
{
    string expression;
    cout << "Enter an expression: " << endl;
    cin >> expression;
    result *tree = infixToParseTree(expression);
    atomAssignment(tree->root);
    truthValue(tree->root);
    cout << tree->root->truth;
    return 0;
}