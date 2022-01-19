#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (a > b ? a : b)

typedef struct AVLNode
{
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

int get_height(AVLNode *node)
{
    int height = 0;
    if (node != NULL)
        height = 1 + max(get_height(node->left), get_height(node->right));
}

int get_balance(AVLNode *node)
{
    if (node == NULL)
        return 0;

    return (get_height(node->left) - get_height(node->right));
}

AVLNode *create_node(int key)
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// LL
AVLNode *rotate_right(AVLNode *parent)
{
    AVLNode *child = parent->left;
    parent->left = child->right;
    child->right = parent;
    return child;
}

AVLNode *rotate_left(AVLNode *parent)
{
    AVLNode *child = parent->right;
    parent->right = child->left;
    child->left = parent;
    return child; // new root return(parent)
}

AVLNode *insert(AVLNode *node, int key)
{
    if (node == NULL)
    {
        return create_node(key);
    }

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else //동일 키는 삽입 안함
        return node;

    printf("inter : %d\n", node->key);

    int balance = get_balance(node);
    //여기서 node는 그냥 맨 윗대가리임, 문제가 있을만한 맨 윗대가리?

    // balance = 2 라는 것 자체가, 왼쪽에 일단 치우쳐져 있다는 소리고
    // key<node->left->key라면, 새로운 노드는 또 왼쪽에 있다는 의미
    // LL
    if (balance > 1 && key < node->left->key)
        return rotate_right(node);

    // balance = -2, 오른쪽에 몰림
    // 새로 추가된 애도 node->right의 오른쪽에 삽입 RR
    if (balance < -1 && key > node->right->key)
        return rotate_left(node);
    // balance = 2, 왼쪽에 몰림
    //새로 추가된 애의 key도 node->left의 right에 삽입, LR

    if (balance > 1 && key > node->left->key)
    {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

void preorder(AVLNode *root)
{
    if (root != NULL)
    {
        printf("[%d] ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

#define MAX_QUEUE_SIZE 100

typedef struct
{
    int front;
    int rear;
    AVLNode *queue[MAX_QUEUE_SIZE];
} QueueType;

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

void enqueue(QueueType *Q, AVLNode *node)
{
    if (is_full(Q))
        error("full");
    Q->rear = (Q->rear + 1) % MAX_QUEUE_SIZE;
    Q->queue[Q->rear] = node;
}

AVLNode *dequeue(QueueType *Q)
{
    if (is_empty(Q))
        error("empty");
    Q->front = (Q->front + 1) % MAX_QUEUE_SIZE;
    return (Q->queue[Q->front]);
}

void level_order(AVLNode *root)
{
    QueueType Q;
    init(&Q);
    enqueue(&Q, root);
    AVLNode *temp;
    int height = get_height(root);
    while (!is_empty(&Q))
    {
        temp = dequeue(&Q);
        if (height != get_height(temp))
        {
            height--;
            printf("\n");
        }

        printf("%d(height : %d)     ", temp->key, get_height(temp));
        if (temp->left != NULL)
            enqueue(&Q, temp->left);
        if (temp->right != NULL)
            enqueue(&Q, temp->right);
    }
}

int main(void)
{
    AVLNode *root = NULL;

    // 예제 트리 구축

    // for (int i = 0; i < 100; i++)
    // {
    //     root = insert(root, rand() % 100);
    // }
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 29);

    printf("%d\n", root->key);

    preorder(root);
    printf("\n");
    level_order(root);

    return 0;
}
