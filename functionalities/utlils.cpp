#include <string>
#include <iostream>
#include <cmath>
#include "utils.h"
#include "node.h"

using namespace std;

char operators[4] = {'~', '*', '+', '>'};

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