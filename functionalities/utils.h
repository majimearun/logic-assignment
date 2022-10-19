#ifndef UTILS_H
#define UTILS_H

#include "node.h"
class utils
{
public:
    static bool isOperator(char c);
    static bool isBracket(char c);
    static void make_truthtable(int **arr, int ncol, int nrow, int column, int step);
    static int **truthTable(int nvar);
    static bool implicationOperator(node *left, node *right);
    static string uniqueAtoms(string expression);
    static bool *assignTruthValues(string uniqueChars);
    static bool *assignTruthValues(string uniqueChars, int *row);
};

#endif