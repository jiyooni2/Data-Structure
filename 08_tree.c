#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a < b) ? b : a)
#define MAX_QUEUE_SIZE 100

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
} TreeNode;

typedef struct
{
    int front;
    int rear;
    TreeNode *queue[MAX_QUEUE_SIZE];
} QueueType;

#define SIZE 100
int top = -1;
TreeNode *stack[SIZE];

void push(TreeNode *p)
{
    if (top < SIZE - 1)
        stack[++top] = p;
}

TreeNode *pop()
{
    TreeNode *p = NULL;
    if (top >= 0)
        p = stack[top--];
    return p;
}

void init(QueueType *Q)
{
    Q->front = Q->rear = 0;
}

int is_empty(QueueType *Q)
{
    return (Q->front == Q->rear);
}

void error(char *message)
{
    fprintf(stderr, message);
    exit(-1);
}

int is_full(QueueType *Q)
{
    return ((Q->rear + 1) % MAX_QUEUE_SIZE == Q->front);
}

void enqueue(QueueType *Q, TreeNode *item)
{
    if (is_full(Q))
        error("full");
    Q->rear = (Q->rear + 1) % MAX_QUEUE_SIZE;
    Q->queue[Q->rear] = item;
}

TreeNode *dequeue(QueueType *Q)
{
    if (is_empty(Q))
        error("empty");
    Q->front = (Q->front + 1) % MAX_QUEUE_SIZE;
    return (Q->queue[Q->front]);
}

void print(QueueType *Q)
{
    for (int i = Q->front + 1; i != Q->rear; i = ((i + 1) % MAX_QUEUE_SIZE))
        printf("%d->", Q->queue[i]);
    printf("%d\n", Q->queue[Q->rear]);
}

void preorder(TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void inorder(TreeNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void inorder_iter(TreeNode *root)
{
    while (1)
    {
        for (; root; root = root->left)
            push(root);
        root = pop();
        if (root == NULL)
            break;
        printf("[%d] ", root->data); // L이후, V로 감
        root = root->right;          // R
    }
}

void level_order(TreeNode *root)
{
    QueueType Q;
    init(&Q);
    enqueue(&Q, root);
    while (!is_empty(&Q))
    {
        root = dequeue(&Q);
        printf("%d ", root->data);
        if (root->left)
            enqueue(&Q, root->left);
        if (root->right)
            enqueue(&Q, root->right);
    }
}

int get_node_count(TreeNode *root)
{
    int count = 0;
    if (root != NULL)
    {
        count = 1 + get_node_count(root->left) + get_node_count(root->right);
    }
    return count;
}

int get_height(TreeNode *root)
{
    int count = 0;
    if (root != NULL)
    {
        count = 1 + max(get_height(root->left), get_height(root->right));
    }
    return count;
}

int get_leaf_count(TreeNode *root)
{
    int count = 0;
    if (root != NULL)
    {
        if (root->left == NULL && root->right == NULL)
            return 1;
        else
        {
            count = get_leaf_count(root->left) + get_leaf_count(root->right);
        }
    }
    return count;
}

int main()
{
    TreeNode n1 = {1, NULL, NULL};
    TreeNode n2 = {4, &n1, NULL};
    TreeNode n3 = {16, NULL, NULL};
    TreeNode n4 = {25, NULL, NULL};
    TreeNode n5 = {20, &n3, &n4};
    TreeNode n6 = {15, &n2, &n5};
    TreeNode *root = &n6;

    preorder(root);
    printf("\n");
    postorder(root);

    printf("\n");
    inorder(root);
    printf("\n");
    inorder_iter(root);
    printf("\n");
    level_order(root);
    printf("\n");
    printf("node count : %d\n", get_node_count(root));
    printf("node height : %d\n", get_height(root));
    printf("leaf count : %d\n", get_leaf_count(root));
    return 0;
}