#include <iostream>
#include <string>
#include <cmath>
#include "./functionalities/utils.h"
#include "./functionalities/node.h"

using namespace std;

/// @brief A function to take in the infix expression of a logical formula as a string and make a parse tree.
/// @param expression It takes the infix expression as a string as an argument.
/// @return Returns a pointer to a result struct which has the pointer to the root node of the parse tree created. The integer count keeps a track of which character of the infix expression string is being traversed right now.
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

/// @brief Function to convert infix expression to prefix expression. It first runs the infixToPrefix function to get the the pointer to the root node of the parse tree created from the infix expression. Then the pointer to the root node is passed to the function print preorder to print the prefix expression.
/// @param expression Takes the infix expression as a string as an argument.
/// @return Returns a pointer to a result structure which contains the pointer to the root node of the parse tree created.
result *infixToPrefix(string expression)
{
    result *tree = infixToParseTree(expression);
    utils::printPreorder(tree->root);
    return tree;
}

int main()
{
    // string expression = "~((r+(s+a))*((~p)*q))";
    string expression;
    cout << "Task 1: Infix expression (fully bracketed) to prefix notation" << endl;
    cout << "Enter infix (well bracketed) expression: ";
    cin >> expression;
    cout << "Expression is: " << expression << endl;
    cout << "correspoding prefix expression: " << endl;
    result *tree = infixToPrefix(expression);
    cout << endl;
    cout << "--------------------------------------------" << endl;
    return 0;
}