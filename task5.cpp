#include "./functionalities/node.h"
#include "./functionalities/utils.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// int *truthValues;
struct result
{
    node *root;
    int count;
};

result *infixToParseTree(string expression)
{
    node *head = new node;
    bool end = false;
    int i = 0;
    while (!end)
    {
        char var = expression[i];
        if (!utils::isBracket(var))
        {
            if (!utils::isOperator(var))
            {
                if (head->isFilled)
                {
                    if (head->data != '~')
                    {
                        if (head->leftFilled)
                        {
                            node *right = new node;
                            right->data = var;
                            head->fillRight(right);
                        }
                        else
                        {
                            node *left = new node;
                            left->data = var;
                            head->fillLeft(left);
                        }
                    }
                    else
                    {
                        node *right = new node;
                        right->data = var;
                        head->fillRight(right);
                        head->leftFilled = true;
                    }
                }
                else
                {
                    head->data = var;
                    head->isFilled = true;
                }
            }
            else
            {
                if (!(head->isFilled))
                {
                    head->fill(var);
                }
                else
                {
                    node *temp = new node;

                    temp->left = head;
                    temp->leftFilled = true;
                    head = temp;
                    head->fill(var);
                }
            }
        }
        else
        {
            if (var == '(')
            {
                if (head->data != '~')
                {
                    if (head->leftFilled)
                    {
                        result *temp = infixToParseTree(expression.substr(i + 1));
                        head->fillRight(temp->root);
                        i += temp->count;
                    }
                    else
                    {
                        result *temp = infixToParseTree(expression.substr(i + 1));
                        head->fillLeft(temp->root);
                        i += temp->count;
                    }
                }
                else
                {
                    result *temp = infixToParseTree(expression.substr(i + 1));
                    head->fillRight(temp->root);
                    i += temp->count;
                    head->leftFilled = true;
                }
            }
            else
            {
                end = true;
            }
        }
        if (i >= expression.length())
        {
            end = true;
        }
        i++;
    }
    return new result{head, i};
}

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
void assignValue(node *head, string atoms, bool *truthValues)
{
    for (int i = 0; i < atoms.length(); i++)
    {
        if (head->data == atoms[i])
        {
            head->truth = (bool)truthValues[i];
        }
    }
}
void atomAssignment(node *head, string atoms, bool *truthValues)
{
    if (!utils::isOperator(head->data)) // if head is a propositional atom
    {
        if (head->isTruthAssigned == false)
        {
            assignValue(head, atoms, truthValues);
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
            assignValue(head->left, atoms, truthValues);
            head->left->isTruthAssigned = true;
        }
    }
    if (!utils::isOperator(head->right->data) && head->right->isTruthAssigned == false) // if right is an atom
    {
        assignValue(head->right, atoms, truthValues);
        head->right->isTruthAssigned = true;
    }
    if (head->data != '~')
    {
        if (utils::isOperator(head->left->data))
        {
            atomAssignment(head->left, atoms, truthValues);
        }
    }
    else
    {
        atomAssignment(head->right, atoms, truthValues);
    }
    if (utils::isOperator(head->right->data))
    {
        atomAssignment(head->right, atoms, truthValues);
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

    string atoms = utils::uniqueAtoms(expression);
    bool *truthValues = utils::assignTruthValues(atoms);

    cout << "\n";
    result *tree = infixToParseTree(expression);
    atomAssignment(tree->root, atoms, truthValues);
    truthValue(tree->root);
    cout << "The truth value is: ";
    cout << tree->root->truth;
    return 0;
}