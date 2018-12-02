// Suppose there is an expression c = a + b. \
Create a binary tree corresponding to this expression (expression tree).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char val;
    struct node *left, *right;
} node;

typedef enum boolean {false, true} bool;

// UTILITY FUNCTIONS
bool isOperator(char ch)
{
    // Return true if ch is an operator; return false otherwise
    switch(ch)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
            return true;
    }
    return false;
}
void inorder (node *root)
{
    // Inorder traversal (left->root->right) of a tree
    if (root)
    {
        inorder(root->left);
        printf("%c ", root->val);
        inorder(root->right);
    }
}
node *newNode(int val)
{
    // Create a new node, and return it
    node *temp = (node *) malloc(sizeof(node));
    temp->left = temp->right = NULL;
    temp->val = val;
    return temp;
}

// STACK MEMBERS
node *stack[50];
int top = -1;
void push(node* ch)
{
    stack[++top] = ch;
}
node* pop()
{
    return stack[top--];
}

// Expression tree 
node *expressionTree(char *postfix)
{
    node *child1, *child2, *parent;
    int pos = -1;

    while(postfix[++pos])
    {
        // Remember: PUSH operands POP operators
        if (isOperator(postfix[pos]))
        {
            parent = newNode(postfix[pos]);

            // pop the top two nodes for children
            child1 = pop();
            child2 = pop();

            // make them children
            parent->left = child1;
            parent->right = child2;

            // push the parent onto the stack
            push(parent);
        }
        else  // operands
            push( newNode(postfix[pos]) );
    }

    // Pop the root and return it
    return pop();
}

int main(void)
{
    char c[] = "ab+ef*g*-";
    node *root = expressionTree(c);
    printf("Inorder expression, obtained from the expression tree:\n");
    inorder(root);
    printf("\n");

    return 0;
}
