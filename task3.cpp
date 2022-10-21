#include <iostream>
#include <string>
#include <cmath>
#include "./functionalities/utils.h"
#include "./functionalities/node.h"

using namespace std;

/// @brief Function to print the infix expression by inorder traversal of the parse tree.
/// @param head The pointer to the root node of the parse tree is passed as the argument
void printInorder(node *head)
{
    if (head != nullptr)
    {
        printInorder(head->left);
        cout << head->data;
        printInorder(head->right);
    }
}

int main()
{
    string expression;
    cout << "Task 3: Outputting the parse tree in infix notation using inorder traversal" << endl;
    cout << "Enter the infix expression (fully bracketed): ";
    cin >> expression;
    result *tree = utils::infixToParseTree(expression);
    printInorder(tree->root);
    cout << endl;
    cout << "--------------------------------------------" << endl;
    return 0;
}
