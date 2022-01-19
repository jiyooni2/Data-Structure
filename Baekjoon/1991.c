#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char data;
    struct Node *left, *right;
} Node;

typedef struct Tree
{
    Node *root
} Tree;

void init(Tree *T)
{
    T->root = NULL;
}

void find

    Node *
    newNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *searchTree(B)

    void insertNode(char t, char l, char r)
{
    Node *T = (Node *)malloc(sizeof(Node));
    T->data = t;

    Node *left = (Node *)malloc(sizeof(Node));
    Node *right = (Node *)malloc(sizeof(Node));
    left->data = l;
    right->data = r;

    T->left = left;
    T->right = right;
}

int main()
{
    Node root;
    init(&root);

    char sen[1000];

    fgets(sen, 1000, stdin);
    sen[strlen(sen) - 1] = '\0';

    char *token = strtok(sen, " ");
    while (token != NULL)
    {
        printf("%s ", token);
        token = strtok(NULL, " ");
    }

    return 0;
}