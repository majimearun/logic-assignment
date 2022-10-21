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
/// @brief Functin to check whether the passed character is a member of the operators array or not.
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
/// @param step The number of rows after which the value being filled will be changed.Eg-step value of 1 means the value will be changed every other row,ie 0 1 0 1.... Similarly step of 2 will mean value will change every 2 rows.ie 0 0 1 1 0 0 1 1...and so on.
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