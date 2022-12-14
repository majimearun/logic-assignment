/**
 * @file node.h
 * @author Arunachala Amuda Murugan, Ayush Bhauwala,Suryansh Chandola
 * @brief This file is the header file for the code related to the node of a parse tree.
 * @version 0.1
 * @date 2022-10-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

///@brief This is the class for a node of the parse tree. Each node of the parse tree will contain the name of the operator or the operand stored in it, pointers to the root nodes of the left and right subtrees of that node. Boolean values for telling us whether the value of the node is filled, the left subtree's root node value is filled, the right subtree's root node value is filled, a boolean value for the truth value of the value stored in the node and another boolean value to tell whether the current node value has been assigned a truth value or not.

class node
{
public:
    char data;        /*!< This is the name of the data in the node. Eg- 'p','q','+','*','~','>'*/
    node *left;       /*!< This is a pointer to the node of the root of the left subtree of the current node*/
    node *right;      /*!< This is a pointer to the node of the root of the right subtree of the current node*/
    bool isFilled;    /*!< Boolean for checking whether the current node has a value assigned to it's data variable or not*/
    bool rightFilled; /*!< Boolean for checking whether the root of the right subtree has a value assigned to it's data variable or not*/
    bool leftFilled;  /*!< Boolean for checking whether the root of the left subtree has a value assigned to it's data variable or not.*/

    node(); /*!< This is the constructor*/
    int fillLeft(node *Node);
    int fillRight(node *Node);
    int fill(char data);
    ~node(); /*!< This is the destructor*/
};
#endif