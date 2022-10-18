#include <iostream>
#include <string>
#include <cmath>
#include "./functionalities/utils.h"
#include "./functionalities/node.h"

using namespace std;

struct result
{
    node *root;
    int count;
};

// Task 0: Infix expression (fully bracketed) to rooted binary parse tree

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

// Task 1: Infix expression (fully bracketed) to prefix notation

// Preorder traversal of the parse tree

void printPreorder(node *head)
{
    if (head != nullptr)
    {
        cout << head->data;
        printPreorder(head->left);
        printPreorder(head->right);
    }
}

result *infixToPrefix(string expression)
{
    result *tree = infixToParseTree(expression);
    printPreorder(tree->root);
    return tree;
}

// Task 2: converting prefix notation to parse tree

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
                    success = head->fill(var);
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

// Task 3: Outputting the parse tree in infix notation using inorder traversal

void printInorder(node *head)
{
    if (head != nullptr)
    {
        printInorder(head->left);
        cout << head->data;
        printInorder(head->right);
    }
}

// Extra: Postorder traversal of the parse tree

void printPostorder(node *head)
{
    if (head != nullptr)
    {
        printPostorder(head->left);
        printPostorder(head->right);
        cout << head->data;
    }
}

// Task 4: computing the height of the parse tree

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

// Task 5: evaulaing the truth value of the expression
// 5.1: If no truth values given as input, use the full truth table
// 5.2: If truth values given, parse tree only for that combination
// 5.3 if only some truth values given, parse for possible combinations (optional)

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
    cout << "Using tree generated in task 1..." << endl;
    printInorder(tree->root);
    cout << endl;
    cout << "--------------------------------------------" << endl;

    // Task 4 run
    cout << "Task 4: computing the height of the parse tree" << endl;
    cout << "Using tree generated in task 1..." << endl;
    cout << "Height of the parse tree: " << heightOfParseTree(tree->root) << endl;
    cout << "--------------------------------------------" << endl;

    // Task 5 run
    cout << "Task 5: evaulaing the truth value of the expression" << endl;
    cout << "Task 5.1: All truth values given:" << endl;
    cout << "----------" << endl;
    cout << "Task 5.2: Some truth values given:" << endl;
    cout << "----------" << endl;
    cout << "Task 5.3: No truth values given:" << endl;
    cout << "--------------------------------------------" << endl;
    return 0;
}