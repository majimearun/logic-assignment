/**
 * @file utlils.cpp
 * @author Arunachala Amuda Murugan, Ayush Bhauwala,Suryansh Chandola
 * @brief This file contains the defenitions of all the functions listed in the utils.h file.
 * @version 0.1
 * @date 2022-10-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <iostream>
#include <cmath>
#include "utils.h"
#include "node.h"

using namespace std;

char operators[4] = {'~', '*', '+', '>'}; /*!<Character array of all the operators we are going to be dealing with*/
/// @brief Function to check whether the passed character is a member of the operators array or not.
/// @param c The character to be checked for being an operator is passed as an argument.
/// @return Returns false if c is not an operator and true if it is an operator.
bool utils::isOperator(char c)
{
    for (int i = 0; i < 4; i++)
    {
        if (c == operators[i])
        {
            return true;
        }
    }
    return false;
}
/// @brief Checks whether the passed character is a bracket( '(' or ')' ) or not.
/// @param c The character to be checked for being a bracket.
/// @return Returns false if c is not a bracket and true if it is a brakcet.
bool utils::isBracket(char c)
{
    if (c == '(' || c == ')')
    {
        return true;
    }
    return false;
}
/// @brief Function to make the truth table corresponding to the number of variables in the logical expression.
/// @param nvar The number of variables in the logical expression.The truth table will have nvar columns and 2^nvar rows.
/// @return Returns the truth table as a pointer to an integer array.
int **utils::truthTable(int nvar)
{
    int rows = pow(2, nvar);
    int columns = nvar;
    int **table;
    table = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        table[i] = new int[columns];
        // make all entries 0
        for (int j = 0; j < columns; j++)
        {
            table[i][j] = 0;
        }
    }
    make_truthtable(table, columns, rows, 0, pow(2, nvar - 1));
    return table;
}
/// @brief Function to populate the truth table with truth values.
/// @param arr The pointer to the truth table which is a 2-D array of integers.
/// @param ncol The number of columns in the truth table.
/// @param nrow The number of rows in the truth table.
/// @param column The column which is being filled currently.
/// @param step The number of rows after which the value being filled will be changed. Eg- Step value of 1 means the value will be changed every other row, i.e. 0 1 0 1.... Similarly step of 2 will mean value will change every 2 rows, i.e. 0 0 1 1 0 0 1 1...and so on.
void utils::make_truthtable(int **arr, int ncol, int nrow, int column, int step)
{
    if (column == ncol)
    {
        return;
    }
    bool val = true;
    for (int row = 0; row < nrow; row++)
    {
        if (row % step == 0)
        {
            val = !val;
        }
        arr[row][column] = val;
    }
    make_truthtable(arr, ncol, nrow, column + 1, step / 2);
}
/// @brief Function to identify the unique variables in the given propositional logic formula.
/// @param expression A string which is the propositional formula whose unique atoms have to be taken.
/// @return Returns a string of all the variables in the string expression.
string utils::uniqueAtoms(string expression)
{
    string uniqueChars = "";
    for (int i = 0; i < expression.length(); i++)
    {
        char var = expression[i];
        if (!utils::isOperator(var) && !utils::isBracket(var))
        {
            if (uniqueChars.find(var) == string::npos)
            {
                uniqueChars += var;
            }
        }
    }
    return uniqueChars;
}
/// @brief Function to get truth value of each variable from the user and assign them to correspoding variable in the logical expression.The truth values are stored in an array of booleans.
/// @param uniqueChars The string of all the variables in the logical expression.
/// @return Returns an array of the truth values of all the variables in the expression.
bool *utils::assignTruthValues(string uniqueChars)
{
    bool *truthValues = new bool[uniqueChars.length()];
    for (int i = 0; i < uniqueChars.length(); i++)
    {
        char var = uniqueChars[i];
        cout << "Enter the truth value of " << var << ": ";
        cin >> truthValues[i];
    }
    return truthValues;
}
/// @brief Function to assign truth values to a row of the truth table.
/// @param uniqueChars A string containing all the variables in the logical expression is passed as an argument.
/// @param row An array of integers representing a row of the truth table is passed as an argument.
/// @return An array of truth values for all variables for one row of the truth table.
bool *utils::assignTruthValues(string uniqueChars, int *row)
{
    bool *truthValues = new bool[uniqueChars.length()];
    for (int i = 0; i < uniqueChars.length(); i++)
    {
        truthValues[i] = row[i];
    }
    return truthValues;
}

/// @brief A function to take in the infix expression of a logical formula as a string and make a parse tree.
/// @param expression It takes the infix expression as a string as an argument.
/// @return Returns a pointer to a result struct which has the pointer to the root node of the parse tree created. The integer count keeps a track of which character of the infix expression string is being traversed right now.
result *utils::infixToParseTree(string expression)
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

/// @brief Function to print the infix expression by inorder traversal of the parse tree.
/// @param head The pointer to the root node of the parse tree is passed as the argument
void utils::printInorder(node *head)
{
    if (head != nullptr)
    {
        printInorder(head->left);
        cout << head->data;
        printInorder(head->right);
    }
}

///@brief Function to convert an infix expression into a prefix expression by preorder traversal of the parse tree.
///@param head We pass a pointer to the root node of the parse tree.
void utils::printPreorder(node *head)
{
    if (head != nullptr)
    {
        cout << head->data;
        printPreorder(head->left);
        printPreorder(head->right);
    }
}

/// @brief Function to print the post order expression by post order traversal of the parse tree.
/// @param head The pointer to the root node of the parse tree is passed as the argument.
void utils::printPostorder(node *head)
{
    if (head != nullptr)
    {
        printPostorder(head->left);
        printPostorder(head->right);
        cout << head->data;
    }
}