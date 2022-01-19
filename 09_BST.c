#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int key;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode *search(TreeNode *root, int key)
{
    if (root == NULL)
        return NULL;
    if (key == root->key)
        return root;
    else if (key < root->key)
        search(root->left, key);
    else
        search(root->right, key);
}

TreeNode *search_iter(TreeNode *root, int key)
{
    while (root != NULL)
    {
        if (key == root->key)
            return root;
        else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

TreeNode *new_node(int key)
{
    TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

TreeNode *insert_node(TreeNode *node, int key)
{ //빈 자리를 찾아가자는 느낌
    if (node == NULL)
        return new_node(key);
    else if (key < node->key)
        node->left = insert_node(node->left, key);
    else
        node->right = insert_node(node->right, key);
}

void inorder(TreeNode *node)
{
    if (node != NULL)
    {
        inorder(node->left);
        printf("%d ", node->key);
        inorder(node->right);
    }
}
TreeNode *insert_node_iter(TreeNode *root, int key)
{
    TreeNode *node = root;
    if (root == NULL)
        return new_node(key);
    while (node != NULL)
    {
        if (key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    node = new_node(key);

    inorder(root);
    printf("\n");
    return root;
}

//계승자 구하는 거임 ㅋㅋ
TreeNode *min_value_node(TreeNode *root)
{
    TreeNode *temp = root->right;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

TreeNode *delete_node(TreeNode *root, int key)
{
    //빈 경우
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = delete_node(root->left, key);
    else if (key > root->key)
        root->right = delete_node(root->right, key);
    else if (key == root->key) //지울 놈 찾음
    {                          //지울놈이 root
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            free(root);
            return temp;
            //얘가 root자리로
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            TreeNode *temp = min_value_node(root);
            root->key = temp->key;
            root->right = delete_node(root->right, temp->key);
        }
    }
    return root;
}

int main()
{
    TreeNode *root = NULL;
    root = insert_node(root, 30);
    root = insert_node(root, 20);
    root = insert_node(root, 10);
    root = insert_node(root, 40);
    root = insert_node(root, 50);
    root = insert_node(root, 60);
    printf("inOrder\n");
    inorder(root);
    printf("\n");
    root = delete_node(root, 20);
    root = delete_node(root, 60);

    inorder(root);
    printf("\n\n");
    if (search(root, 30) != NULL)
        printf("found\n");
    else
        printf("not found\n");
    return 0;
}