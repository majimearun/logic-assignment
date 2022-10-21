#include <iostream>
#include <string>
#include <cmath>
#include "./functionalities/utils.h"
#include "./functionalities/node.h"

using namespace std;
/// @brief A structure named result.It contains a pointer to struct node and an integer.
struct result
{
    node *root;
    int count;
};

/// @brief A function to take in the infix expression of a logical formula as a string and make a parse tree.
/// @param expression It takes the infix expression as a string as an argument.
/// @return Returns a pointer to a result struct which has the pointer to the root node of the parse tree created.The integer count keeps a track of which character of the infix expression string is being traversed right now.
result *infixToParseTree(string expression)
{
    node *head = new node;
    bool end = false;
    int i = 0;
    while (!end)
    {
        char var = expression[i];
        if (!utils::isBracket(var))
        {
            if (!utils::isOperator(var))
            {
                if (head->isFilled)
                {
                    if (head->data != '~')
                    {
                        if (head->leftFilled)
                        {
                            node *right = new node;
                            right->data = var;
                            head->fillRight(right);
                        }
                        else
                        {
                            node *left = new node;
                            left->data = var;
                            head->fillLeft(left);
                        }
                    }
                    else
                    {
                        node *right = new node;
                        right->data = var;
                        head->fillRight(right);
                        head->leftFilled = true;
                    }
                }
                else
                {
                    head->data = var;
                    head->isFilled = true;
                }
            }
            else
            {
                if (!(head->isFilled))
                {
                    head->fill(var);
                }
                else
                {
                    node *temp = new node;

                    temp->left = head;
                    temp->leftFilled = true;
                    head = temp;
                    head->fill(var);
                }
            }
        }
        else
        {
            if (var == '(')
            {
                if (head->data != '~')
                {
                    if (head->leftFilled)
                    {
                        result *temp = infixToParseTree(expression.substr(i + 1));
                        head->fillRight(temp->root);
                        i += temp->count;
                    }
                    else
                    {
                        result *temp = infixToParseTree(expression.substr(i + 1));
                        head->fillLeft(temp->root);
                        i += temp->count;
                    }
                }
                else
                {
                    result *temp = infixToParseTree(expression.substr(i + 1));
                    head->fillRight(temp->root);
                    i += temp->count;
                    head->leftFilled = true;
                }
            }
            else
            {
                end = true;
            }
        }
        if (i >= expression.length())
        {
            end = true;
        }
        i++;
    }
    return new result{head, i};
}

///@brief Function to convert an infix expression into a prefix expression by preorder traversal of the parse tree.
///@param head We pass a pointer to the root node of the parse tree.
void printPreorder(node *head)
{
    if (head != nullptr)
    {
        cout << head->data;
        printPreorder(head->left);
        printPreorder(head->right);
    }
}
/// @brief Function to convert infix expression to prefix expression.It first runs the infixToPrefix function to get the the pointer to the root node of the parse tree created from the infix expression.Then the pointer to the root node is passed to the function print preorder to print the prefix expression.
/// @param expression Takes the infix expression as a string as an argument.
/// @return Returns a pointer to a result struct which contains the pointer to the root node of the parse tree created.
result *infixToPrefix(string expression)
{
    result *tree = infixToParseTree(expression);
    printPreorder(tree->root);
    return tree;
}

/// @brief Function to make a parse tree from given prefix expression.
/// @param expression Prefix expression as a string is taken as the argument.
/// @return Returns the pointer to a result struct which contains the pointer to the root node of the parse tree.The integer count is used to keep track of which character of the string for the expression is to be used.
result *prefixToParseTree(string expression)
{
    int success = 0;
    node *head = new node;
    bool end = false;
    int i = 0;
    while (!end)
    {
        char var = expression[i];
        if (!utils::isOperator(var))
        {
            if (head->data != '~')
            {
                if (head->leftFilled)
                {
                    node *right = new node;
                    right->data = var;
                    success = head->fillRight(right);
                    end = true;
                }
                else
                {
                    node *left = new node;
                    left->data = var;
                    success = head->fillLeft(left);
                }
            }
            else
            {
                node *right = new node;
                right->data = var;
                success = head->fillRight(right);
                head->leftFilled = true;
                end = true;
            }
        }
        else
        {
            if (var != '~')
            {
                if (head->isFilled)
                {
                    if (head->leftFilled)
                    {
                        result *temp = prefixToParseTree(expression.substr(i));
                        success = head->fillRight(temp->root);
                        i += temp->count - 1;
                        end = true;
                    }
                    else
                    {
                        result *temp = prefixToParseTree(expression.substr(i));
                        success = head->fillLeft(temp->root);
                        i += temp->count - 1;
                    }
                }
                else
                {
                    success = head->fill(var);
                }
            }
            else
            {
                if (head->isFilled)
                {
                    if (head->data != '~')
                    {
                        if (head->leftFilled)
                        {
                            result *temp = prefixToParseTree(expression.substr(i));
                            success = head->fillRight(temp->root);
                            i += temp->count - 1;
                            end = true;
                        }
                        else
                        {
                            result *temp = prefixToParseTree(expression.substr(i));
                            success = head->fillLeft(temp->root);
                            i += temp->count - 1;
                        }
                    }
                    else
                    {
                        result *temp = prefixToParseTree(expression.substr(i));
                        success = head->fillRight(temp->root);
                        head->leftFilled = true;
                        i += temp->count - 1;
                        end = true;
                    }
                }
                else
                {
                    if (var != '~')
                    {
                        success = head->fill(var);
                    }
                    else
                    {
                        success = head->fill(var);
                        head->leftFilled = true;
                    }
                }
            }
        }
        if (i >= expression.length())
        {
            end = true;
        }
        i++;
    }
    return new result{head, i};
}

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

/// @brief Function to print the post order expression by post order traversal of the parse tree.
/// @param head The pointer to the root node of the parse tree is passed as the argument.
void printPostorder(node *head)
{
    if (head != nullptr)
    {
        printPostorder(head->left);
        printPostorder(head->right);
        cout << head->data;
    }
}

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
    result *parseTree = infixToParseTree(expression);
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
        result *parseTree = infixToParseTree(expression);
        bool result = evaluteParseTree(parseTree->root, truthValues, uniqueChars);
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < uniqueChars.length(); j++)
        {
            cout << uniqueChars[j] << " = " << truthValues[j] << ", ";
        }
        cout << "Result = " << result << endl;
    }
}

int main()
{
    // Task 0 run
    cout << "Task 0: Infix expression (fully bracketed) to rooted binary parse tree" << endl;
    string expression;
    cout << "Enter the infix expression (fully bracketed): ";
    cin >> expression;
    result *tree = infixToParseTree(expression);
    cout << "Traversing the parse tree in various ways: " << endl;
    cout << "Preorder: ";
    printPreorder(tree->root);
    cout << endl;
    cout << "Inorder: ";
    printInorder(tree->root);
    cout << endl;
    cout << "Postorder: ";
    printPostorder(tree->root);
    cout << endl;
    cout << "--------------------------------------------" << endl;

    // Task 1 run
    cout << "Task 1: Infix expression (fully bracketed) to prefix notation" << endl;
    cout << "Enter the infix expression (fully bracketed): ";
    cin >> expression;
    tree = infixToPrefix(expression);
    cout << endl;
    cout << "--------------------------------------------" << endl;

    // Task 2 run
    cout << "Task 2: converting prefix notation to parse tree" << endl;
    cout << "Enter the prefix expression: ";
    cin >> expression;
    tree = prefixToParseTree(expression);
    cout << "Traversing the parse tree in various ways: " << endl;
    cout << "Preorder: ";
    printPreorder(tree->root);
    cout << endl;
    cout << "Inorder: ";
    printInorder(tree->root);
    cout << endl;
    cout << "Postorder: ";
    printPostorder(tree->root);
    cout << endl;
    cout << "--------------------------------------------" << endl;

    // Task 3 run
    cout << "Task 3: Outputting the parse tree in infix notation using inorder traversal" << endl;
    cout << "Enter the infix expression (fully bracketed): ";
    cin >> expression;
    tree = infixToParseTree(expression);
    printInorder(tree->root);
    cout << endl;
    cout << "--------------------------------------------" << endl;

    // Task 4 run
    cout << "Task 4: computing the height of the parse tree" << endl;
    cout << "Enter the infix expression (fully bracketed): ";
    cin >> expression;
    tree = infixToParseTree(expression);
    cout << "Height of the parse tree: " << heightOfParseTree(tree->root) << endl;
    cout << "--------------------------------------------" << endl;

    // Task 5 run
    cout << "Task 5: evaulaing the truth value of the expression" << endl;
    cout << "Enter the infix expression (fully bracketed): ";
    cin >> expression;
    bool truth = evaluateExpression(expression);
    cout << "The truth value of the expression is: " << truth << endl;
    cout << "--------------------------------------------" << endl;

    cout << "Evaluating whole truth table for expression:" << endl;
    cout << "Enter the infix expression (fully bracketed): ";
    cin >> expression;
    showTruthTable(expression);
    return 0;
}