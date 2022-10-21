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
/// @brief A structure named result. It contains a pointer to struct node and an integer.
struct result
{
    node *root; /*!<This is a pointer to the struct node.It will hold the pointer to the root node of the parse tree.*/
    int count;  /*!</This integer keeps track of the number of characters passed in the expression string.*/

    ~result();
};

/// @brief This is the utility class which contains most of the functions we will be using in our code.
class utils
{
public:
    static bool isOperator(char c);
    static bool isBracket(char c);
    static void make_truthtable(int **arr, int ncol, int nrow, int column, int step);
    static int **truthTable(int nvar);
    static string uniqueAtoms(string expression);
    static bool *assignTruthValues(string uniqueChars);
    static bool *assignTruthValues(string uniqueChars, int *row);
    static result *infixToParseTree(string expression);
    static void printInorder(node *head);
    static void printPreorder(node *head);
    static void printPostorder(node *head);
    static string readFile(string filename);
};

#endif