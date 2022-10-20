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
/// @brief function to fill the root node of the left subtree of the current node.
/// @param Node The pointer to the root of the left subtree.
/// @return returns an integer value of 0 if everything gets executed succesfully.
///@note filling the node means assigning a value to the pointer left of the current node.It is not to be confused with assigning value to the variable data.
int node::fillLeft(node *Node) /*!< function to fill the root node of the left subtree of the current node.*/
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
/// @brief function to fill the root node of the right subtree of the current node.
/// @param Node The pointer to the root of the right subtree.
/// @return returns an integer value of 0 if everything gets executed succesfully.
///@note filling the node means assigning a value to the pointer right of the current node.It is not to be confused with assigning value to the variable data.
int node::fillRight(node *Node) /*!<function to fill the root node of the right subtree of the current node.*/
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
/// @brief functin to fill the current node's data variable with the passed character.
/// @param data the character to be assigned to the data variable.
/// @return returns 0 on successful execution.
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