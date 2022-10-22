#include <iostream>
#include <string>
#include <cmath>
#include "./functionalities/utils.h"
#include "./functionalities/node.h"

using namespace std;

/// @brief Function to get the height of the parse tree by counting the height of all the branches and comparing them to get their maximum as the height of the parse tree.
/// @param head The pointer to the root node of the parse tree is passed as the argument.
/// @return Returns the height of the parse tree as an integer.
int heightOfParseTree(node *head)
{
    int height = 1;
    if (head != nullptr)
    {
        if (utils::isOperator(head->data))
        {
            int left = heightOfParseTree(head->left);
            int right = heightOfParseTree(head->right);
            height = 1 + max(left, right);
        }
    }
    return height;
}

int main()
{
    // string expression = "~((r+(s+a))*((~p)*q))";
    string expression;
    cout << "Task 4: computing the height of the parse tree" << endl;
    cout << "Enter infix (well bracketed) expression: ";
    cin >> expression;
    cout << "Expression is: " << expression << endl;
    result *tree = utils::infixToParseTree(expression);
    cout << "Height of the parse tree: " << heightOfParseTree(tree->root) << endl;
    cout << "--------------------------------------------" << endl;
    delete tree;
    return 0;
}