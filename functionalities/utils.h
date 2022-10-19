#ifndef UTILS_H
#define UTILS_H

#include "node.h"
class utils
{
public:
    static bool isOperator(char c);
    static bool isBracket(char c);
    static void make_truthtable(int **arr, int ncol, int nrow, int column, int step);
    static int **truthtable(int nvar);
    static bool implicationOperator(node *left, node *right);
    
};

#endif