#include <iostream>
#include <string>
#include <cmath>
#include "./functionalities/utils.h"
#include "./functionalities/node.h"

using namespace std;

/// @brief Function to print the truth value obtained by evaluating the passed logical expression with the help of the parse tree of the expression.
/// @param head The pointer to the root node of the parse tree is passed as an argument.
/// @param truthValues An array of boolean values storing the truth values of all the atoms in the given expression is passed as an argument.
/// @param uniqueChars A string comprising of all the unique characters of the expression is passed as an argument.
/// @return The truth value obtained by evaluating the parse tree.
bool evaluteParseTree(node *head, bool *truthValues, string uniqueChars)
{
    bool result = false;
    if (head != nullptr)
    {
        if (utils::isOperator(head->data))
        {
            bool left = evaluteParseTree(head->left, truthValues, uniqueChars);
            bool right = evaluteParseTree(head->right, truthValues, uniqueChars);
            switch (head->data)
            {
            case '>':
                result = !left || right;
                break;
            case '*':
                result = left && right;
                break;
            case '~':
                result = !right;
                break;
            case '+':
                result = left || right;
                break;
            }
        }
        else
        {
            int index = uniqueChars.find(head->data);
            result = truthValues[index];
        }
    }
    return result;
}
/// @brief Function to evaluate the truth value of the expression given in infix notation as a string and return it as a boolean value.
/// @param expression The infix expression in the form of a string is passed as an argument.
/// @return returns the evaluated truth value of the expression passed.
bool evaluateExpression(string expression)
{
    string uniqueChars = utils::uniqueAtoms(expression);
    bool *truthValues = utils::assignTruthValues(uniqueChars);
    result *parseTree = utils::infixToParseTree(expression);
    bool result = evaluteParseTree(parseTree->root, truthValues, uniqueChars);
    return result;
}

/// @brief Function to print the truth table of a given logical expression.
/// @param expression The logical expression in infix form is passed as a string.
void showTruthTable(string expression)
{
    string uniqueChars = utils::uniqueAtoms(expression);
    int **table = utils::truthTable(uniqueChars.length());
    for (int i = 0; i < pow(2, uniqueChars.length()); i++)
    {
        bool *truthValues = utils::assignTruthValues(uniqueChars, table[i]);
        result *parseTree = utils::infixToParseTree(expression);
        bool result = evaluteParseTree(parseTree->root, truthValues, uniqueChars);
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < uniqueChars.length(); j++)
        {
            cout << uniqueChars[j] << " = " << truthValues[j] << ", ";
        }
        cout << "Result = " << result << endl;
        delete parseTree;
        delete truthValues;
    }
    delete table;
}

int main()
{
    string expression = "~((r+(s+a))*((~p)*q))";
    cout << "Task 5: evaulaing the truth value of the expression" << endl;
    cout << "Expression is: " << expression << endl;
    bool truth = evaluateExpression(expression);

    cout << "The truth value of the expression is: " << truth << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Evaluating whole truth table for expression:" << endl;
    showTruthTable(expression);
    return 0;
}