#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    long int value;
    struct node *right;
    struct node *left;
    struct node *parent;
} node;

typedef struct tree
{
    long int count;
    struct node *root;
} tree;

void init(tree *t)
{
    node *treeNode = (node *)malloc(sizeof(node));
    tree *tempTree = (tree *)malloc(sizeof(tree));
    treeNode->parent = NULL;
    treeNode->right = NULL;
    treeNode->left = NULL;
    tempTree->root = treeNode;

    *t = *tempTree;
}

node *find(tree *t, long int value)
{
    if (t)
    {
        if (t->count > 0)
        {
            node *treeNode;
            treeNode = (node *)malloc(sizeof(node));
            treeNode = t->root;

            while (treeNode)
            {
                if (treeNode->value == value)
                {
                    return treeNode;
                }
                else if (value > treeNode->value && treeNode->right)
                {
                    treeNode = treeNode->right;
                }
                else if (value < treeNode->value && treeNode->left)
                {
                    treeNode = treeNode->left;
                }
                else
                {
                    return NULL;
                }
            }
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
    return NULL;
}

long int insert(tree *t, long int value)
{
    node *addNode;
    addNode = (node *)malloc(sizeof(node));
    addNode->parent = addNode;
    addNode->left = NULL;
    addNode->right = NULL;
    addNode->value = value;

    tree *tempTree = (tree *)malloc(sizeof(tree));
    tempTree = t;

    tree *tempTree1 = (tree *)malloc(sizeof(tree));
    tempTree1 = t;

    node *treeNode = (node *)malloc(sizeof(node));
    treeNode = tempTree->root;

    long int countNode = tempTree->count;
    if (tempTree && treeNode && addNode)
    {
        if (find(tempTree1, value))
        {
            return 1;
        }
        else
        {
            if (countNode != 0)
            {
                treeNode = tempTree->root;
                while (treeNode)
                {
                    if (value > treeNode->value)
                    {
                        if (treeNode->right)
                        {
                            treeNode = treeNode->right;
                            continue;
                        }
                        else
                        {
                            addNode->parent = treeNode;
                            treeNode->right = addNode;
                            tempTree->count = countNode + 1;
                            return 0;
                        }
                    }
                    else
                    {
                        if (treeNode->left)
                        {
                            treeNode = treeNode->left;
                            continue;
                        }
                        else
                        {
                            addNode->parent = treeNode;
                            treeNode->left = addNode;
                            tempTree->count = countNode + 1;
                            return 0;
                        }
                    }
                }
                return 2;
            }
            else
            {
                tempTree->root = addNode;
                tempTree->count = 1;
                return 0;
            }
        }
    }
    else
    {
        return 2;
    }
}

void preorder(node *n)
{
    node *treeNode;
    treeNode = (node *)malloc(sizeof(node));
    treeNode = n;

    node *leftTree = (node *)malloc(sizeof(node));

    if (treeNode && leftTree)
    {
        leftTree = treeNode;
        int i = 0, size = 0, oldI = 0;
        node **arr = NULL;
        printf("%ld ", treeNode->value);
        if (treeNode->left)
        {
            leftTree = treeNode->left;
        }
        else
        {
            leftTree = treeNode->right;
        }
        while (leftTree)
        {
            printf("%ld ", leftTree->value);
            if (leftTree->right)
            {
                size++;
                arr = (node **)realloc(arr, size * sizeof(node *));
                if (size > 1)
                {
                    for (int k = size - 1; k > 0; k--)
                    {
                        arr[k] = arr[k - 1];
                    }
                    arr[0] = leftTree->right;
                }
                else
                {
                    arr[i] = leftTree->right;
                }
                i++;
            }
            if (leftTree->left)
            {
                leftTree = leftTree->left;
            }
            else
            {
                if (size != 0 && oldI < i)
                {
                    leftTree = arr[oldI];
                    oldI++;
                }
                else
                {
                    break;
                }
            }
        }
        if (treeNode->left && treeNode->right)
        {
            arr = NULL;
            size = 0;
            i = 0;
            oldI = 0;
            leftTree = treeNode->right;
            while (leftTree)
            {
                printf("%ld ", leftTree->value);
                if (leftTree->right)
                {
                    size++;
                    arr = (node **)realloc(arr, size * sizeof(node *));
                    if (size > 1)
                    {
                        for (int k = size - 1; k > 0; k--)
                        {
                            arr[k] = arr[k - 1];
                        }
                        arr[0] = leftTree->right;
                    }
                    else
                    {
                        arr[i] = leftTree->right;
                    }
                    i++;
                }
                if (leftTree->left)
                {
                    leftTree = leftTree->left;
                }
                else
                {
                    if (size != 0 && oldI < i)
                    {
                        leftTree = arr[oldI];
                        oldI++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        printf("\n");
    }
    else
    {
        return;
    }
}

int main()
{
    tree *binaryTree = (tree *)malloc(sizeof(tree));
    init(binaryTree);
    long int value;
    for (long int i = 0; i < 7; i++)
    {
        scanf("%ld", &value);
        insert(binaryTree, value);
    }
    preorder(binaryTree->root);
    return 0;
}