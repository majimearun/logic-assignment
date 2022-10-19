#include "./functionalities/node.h"
#include "./functionalities/utils.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string atoms = "";
int *truthValues;
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
void assignValue(node *head)
{
    for (int i = 0; i < atoms.length(); i++)
    {
        if (head->data == atoms[i])
        {
            head->truth = (bool)truthValues[i];
        }
    }
}
void atomAssignment(node *head)
{
    if (!utils::isOperator(head->data)) // if head is a propositional atom
    {
        if (head->isTruthAssigned == false)
        {
            assignValue(head);
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
            assignValue(head->left);
            head->left->isTruthAssigned = true;
        }
    }
    if (!utils::isOperator(head->right->data) && head->right->isTruthAssigned == false) // if right is an atom
    {
        assignValue(head->right);
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
    char var;

    for (int i = 0; i < expression.length(); i++)
    {
        var = expression[i];
        if (!utils::isBracket(var) && !utils::isOperator(var))
        {
            int ctr = 0;
            for (int j = 0; j < atoms.length(); j++)
            {
                if (atoms[j] == var)
                {
                    ctr = 1;
                }
            }
            if (ctr == 0)
            {
                atoms += var;
            }
        }
    }
    truthValues = new int[atoms.length()];
    for (int i = 0; i < atoms.length(); i++)
    {
        cout << "Enter truth value of " << atoms[i] << " ";
        cin >> truthValues[i];
        cout << "\n";
    }
    cout << "\n";
    result *tree = infixToParseTree(expression);
    atomAssignment(tree->root);
    truthValue(tree->root);
    cout << "The truth value is: ";
    cout << tree->root->truth;
    return 0;
}