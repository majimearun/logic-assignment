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

char operators[4] = {'~', '*', '+', '>'}; /*!<character array of all the operators we are going to be dealing with*/
/// @brief functin to check whether the passed character is a member of the operators array or not.
/// @param c the character to be checked for being an operator
/// @return returns false if c is not an operator and true if it is an operator.
bool utils::isOperator(char c)
{
    for (int i = 0; i < 4; i++) /*!<iterating through members of the operators array and checking if they equal c*/
    {
        if (c == operators[i])
        {
            return true;
        }
    }
    return false;
}
/// @brief checks whether the passed character is a bracket( '(' or ')' ) or not.
/// @param c the character to be checked for being a bracket.
/// @return returns false if c is not a bracket and true if it is a brakcet.
bool utils::isBracket(char c)
{
    if (c == '(' || c == ')')
    {
        return true;
    }
    return false;
}

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
/// @brief function to identify the unique basic propositional atoms in the given propositional logic formula.
/// @param expression a string which is the propositional formula whose unique atoms have to be taken.
/// @return returns a string of all the unique atoms in the string expression.
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

bool *utils::assignTruthValues(string uniqueChars, int *row)
{
    bool *truthValues = new bool[uniqueChars.length()];
    for (int i = 0; i < uniqueChars.length(); i++)
    {
        truthValues[i] = row[i];
    }
    return truthValues;
}