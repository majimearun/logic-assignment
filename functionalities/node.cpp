/**
 * @file node.cpp
 * @author Arunachala Amuda Murugan, Ayush Bhauwala,Suryansh Chandola
 * @brief This file has the defenitions of all the functions of node.h.
 * @version 0.1
 * @date 2022-10-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>
#include "node.h"

using namespace std;
/// @brief The constructor for the node class. Variable data represents what operator or operand is stored in the current node of the parse tree; left and right are pointers to the root nodes of the left and right subtees of the current node. The boolean truth is the truth value assigned to the current node. In the case that the data variable is an operator then truth value assigned is the truth value obtained by evaluating the parse tree of which the current node is the root node of and isFilled is a boolean which tells us whether the current node has a truth value assigned to it or not. The booleans isFilled, leftFilled and rightFilled tell us whether the current node has a value assigned to its data variable, the left subtree's root has a value assigned to it's data variable and the right subtree has a value assigned to the data variable of it's root node respectively.
node::node()
{
    data = ' ';
    left = nullptr;
    right = nullptr;
    isFilled = false;
    rightFilled = false;
    leftFilled = false;
    truth = false;
    isTruthAssigned = false;
}
/// @brief Function to fill the root node of the left subtree of the current node.
/// @param Node The pointer to the node which is going to be the root node of the left subtree.
/// @return Returns an integer value of 0 if everything gets executed succesfully and -1 in case of error in execution.
///@note Filling the node means assigning a value to the pointer left of the current node.It is not to be confused with assigning value to the variable data.
int node::fillLeft(node *Node)
{
    if (leftFilled == false)
    {
        left = Node;
        leftFilled = true;
        return 0;
    }
    else
    {
        return -1;
    }
}
/// @brief Function to fill the root node of the right subtree of the current node.
/// @param Node The pointer to the node which is going to be the root node of the right subtree is passed as an argument.
/// @return Returns an integer value of 0 if everything gets executed succesfully and -1 in case of an error.
///@note Filling the node means assigning a value to the pointer right of the current node.It is not to be confused with assigning value to the variable data.
int node::fillRight(node *Node)
{
    if (rightFilled == false)
    {
        right = Node;
        rightFilled = true;
        return 0;
    }
    else
    {
        return -1;
    }
}
/// @brief Function to fill the current node's data variable with the passed character.
/// @param data The character to be assigned to the data variable.
/// @return Returns 0 on successful execution.
int node::fill(char data)
{
    if (isFilled == false)
    {
        this->data = data;
        isFilled = true;
        return 0;
    }
    else
    {
        return -1;
    }
}