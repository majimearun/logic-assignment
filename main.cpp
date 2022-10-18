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

int h = 0;

// Task 0: Infix (fully bracketed) to rooted binary parse tree

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

void printPreorder(node *head)
{
    if (head != nullptr)
    {
        cout << head->data;
        printPreorder(head->left);
        printPreorder(head->right);
    }
}
// Task 1: infix to prefix notation
result *infixToPrefix(string expression)
{
    result *tree = infixToParseTree(expression);
    printPreorder(tree->root);
    return tree;
}

// Task 2: converting prefix notation to parse tree

// Task 3: outputting the parse tree in infix notation
void printInorder(node *head)
{
    if (head != nullptr)
    {
        printInorder(head->left);
        cout << head->data;
        printInorder(head->right);
    }
}

// Postorder traversal of the parse tree
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

void findHeight(node *head, int curlen)
{

    if (!utils::isOperator(head->data))
    {
        curlen++;
        if (curlen > h)
        {
            h = curlen;
        }
    }
    else
    {
        curlen++;
        if (head->data == '~')
        {
            findHeight(head->right, curlen);
        }
        else
        {
            findHeight(head->left, curlen);
            findHeight(head->right, curlen);
        }
    }
}

void height(node *head)
{
    int height = 0;
    findHeight(head, 0);
    cout << "height of given parse tree is: " << h << endl;
    h = 0;
}

// Task 5: evaulaing the truth value of the expression
// 5.1: If no truth values given as input, use the full truth table
// 5.2: If truth values given, parse tree only for that combination
// 5.3 if only some truth values given, parse for possible combinations (optional)

int main()
{
    string infixExpression;
    cout << "Enter an infix (well bracketed) expression: " << endl;
    cin >> infixExpression;
    result *result1;
    result1 = infixToParseTree(infixExpression);
    cout << "Inorder traversal of tree results in:" << endl;
    printInorder(result1->root);
    cout << endl;
    cout << "Preorder traversal of tree results in:" << endl;
    printPreorder(result1->root);
    cout << endl;
    cout << "Postorder traversal of tree results in:" << endl;
    printPostorder(result1->root);
    cout << endl;

    height(result1->root);
    cout << "------------------------------------" << endl;
    string infixExpression2;
    cout << "Enter an infix (well bracketed) expression: " << endl;
    cin >> infixExpression2;
    result *tree = infixToPrefix(infixExpression2);
    cout << endl;
    cout << "Inorder traversal of tree results in:" << endl;
    printInorder(tree->root);
    cout << endl;
    cout << "Preorder traversal of tree results in:" << endl;
    printPreorder(tree->root);
    cout << endl;
    cout << "Postorder traversal of tree results in:" << endl;
    printPostorder(tree->root);
    cout << endl;

    height(tree->root);

    return 0;

    // Example run of creating a truth table (nvar)
    // cout << "Truth table for 3 variables:" << endl;
    // int n = 3;
    // int **table = utils::truthtable(n);
    // for (int i = 0; i < pow(2, n); i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << table[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}