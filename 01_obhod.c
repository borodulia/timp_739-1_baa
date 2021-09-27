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

void bfs(node *n)
{
    node *treeNode;
    treeNode = (node *)malloc(sizeof(node));
    treeNode = n;

    node *emptyNode;
    emptyNode = (node *)malloc(sizeof(node));

    if (treeNode && emptyNode)
    {
        long int oldlvl = 1, lvl = 1, cnt = 0, i = 0, j = 0;
        node **nodes = (node **)malloc(lvl * sizeof(node *));
        nodes[0] = treeNode;
        printf("%ld ", nodes[0]->value);
        bool flag = true;
        long int size = oldlvl;
        while (flag)
        {
            flag = false;
            oldlvl = lvl;
            lvl *= 2;
            size += lvl;
            nodes = (node **)realloc(nodes, size * sizeof(node *));
            for (i = oldlvl - 1, j = lvl - 1; i < (lvl - 1); i++, j++)
            {
                if (nodes[i]->left && nodes[i] != emptyNode)
                {
                    flag = true;
                    nodes[j] = nodes[i]->left;
                }
                else
                {
                    nodes[j] = emptyNode;
                }
                j += 1;
                if (nodes[i]->right && nodes[i] != emptyNode)
                {
                    flag = true;
                    nodes[j] = nodes[i]->right;
                }
                else
                {
                    nodes[j] = emptyNode;
                }
            }
            if (flag)
            {
                for (i = oldlvl - 1, j = lvl - 1; i < (lvl - 1); i++, j++)
                {
                    if (nodes[i]->left && nodes[i] != emptyNode)
                    {
                        printf("%ld ", nodes[i]->left->value);
                    }
                    ++j;
                    if (nodes[i]->right && nodes[i] != emptyNode)
                    {
                        printf("%ld ", nodes[i]->right->value);
                    }
                }
            }
        }
        printf("\n");
    }
    else
    {
        printf("\n");
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
    bfs(binaryTree->root);
    return 0;
}