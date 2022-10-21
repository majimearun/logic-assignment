#include <iostream>
#include <string>
#include <cmath>
#include "./functionalities/utils.h"
#include "./functionalities/node.h"

using namespace std;

/// @brief Function to make a parse tree from given prefix expression.
/// @param expression Prefix expression as a string is taken as the argument.
/// @return Returns the pointer to a result struct which contains the pointer to the root node of the parse tree. The integer count is used to keep track of which character of the string for the expression is to be used.
result *prefixToParseTree(string expression)
{
    int success = 0;
    node *head = new node;
    bool end = false;
    int i = 0;
    while (!end)
    {
        char var = expression[i];
        if (!utils::isOperator(var))
        {
            if (head->data != '~')
            {
                if (head->leftFilled)
                {
                    node *right = new node;
                    right->data = var;
                    success = head->fillRight(right);
                    end = true;
                }
                else
                {
                    node *left = new node;
                    left->data = var;
                    success = head->fillLeft(left);
                }
            }
            else
            {
                node *right = new node;
                right->data = var;
                success = head->fillRight(right);
                head->leftFilled = true;
                end = true;
            }
        }
        else
        {
            if (var != '~')
            {
                if (head->isFilled)
                {
                    if (head->leftFilled)
                    {
                        result *temp = prefixToParseTree(expression.substr(i));
                        success = head->fillRight(temp->root);
                        i += temp->count - 1;
                        end = true;
                    }
                    else
                    {
                        result *temp = prefixToParseTree(expression.substr(i));
                        success = head->fillLeft(temp->root);
                        i += temp->count - 1;
                    }
                }
                else
                {
                    success = head->fill(var);
                }
            }
            else
            {
                if (head->isFilled)
                {
                    if (head->data != '~')
                    {
                        if (head->leftFilled)
                        {
                            result *temp = prefixToParseTree(expression.substr(i));
                            success = head->fillRight(temp->root);
                            i += temp->count - 1;
                            end = true;
                        }
                        else
                        {
                            result *temp = prefixToParseTree(expression.substr(i));
                            success = head->fillLeft(temp->root);
                            i += temp->count - 1;
                        }
                    }
                    else
                    {
                        result *temp = prefixToParseTree(expression.substr(i));
                        success = head->fillRight(temp->root);
                        head->leftFilled = true;
                        i += temp->count - 1;
                        end = true;
                    }
                }
                else
                {
                    if (var != '~')
                    {
                        success = head->fill(var);
                    }
                    else
                    {
                        success = head->fill(var);
                        head->leftFilled = true;
                    }
                }
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

int main()
{
    string expression;
    cout << "Task 2: converting prefix notation to parse tree" << endl;
    cout << "Enter the prefix expression: ";
    cin >> expression;
    result *tree = prefixToParseTree(expression);
    cout << "Verification... traversing the tree in multiple ways: " << endl;
    cout << "Inorder: ";
    utils::printInorder(tree->root);
    cout << endl;
    cout << "Preorder: ";
    utils::printPreorder(tree->root);
    cout << endl;
    cout << "Postorder: ";
    utils::printPostorder(tree->root);
    cout << endl;
    cout << "--------------------------------------------" << endl;
    return 0;
}