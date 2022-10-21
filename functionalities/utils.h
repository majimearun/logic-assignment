/**
 * @file utils.h
 * @author Arunachala Amuda Murugan, Ayush Bhauwala,Suryansh Chandola
 * @brief This file includes all the helper functions used in the project.
 * @version 0.1
 * @date 2022-10-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef UTILS_H
#define UTILS_H

#include "node.h"

/// @brief This is the utility class which contains most of the functions we will be using in our code.
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