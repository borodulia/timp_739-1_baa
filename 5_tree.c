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
    node *NODE = (node *)malloc(sizeof(node));
    tree *tmp = (tree *)malloc(sizeof(tree));
    NODE->PARENT = NULL;
    NODE->RIGHT = NULL;
    NODE->LEFT = NULL;
    tmp->root = NODE;

    *t = *tmp;
}

long int remove_min(node *n)
{
    long int value = 0;

    node *NODE;
    NODE = (node *)malloc(sizeof(node));
    NODE = n;

    node *leftNode = (node *)malloc(sizeof(node));
    leftNode = NODE;

    while (NODE->LEFT)
    {
        NODE = NODE->LEFT;
    }
    if (NODE->RIGHT)
    {
        NODE = NODE->RIGHT;
        remove_min(NODE);
    }
    else
    {
        value = NODE->VALUE;
        if (NODE->PARENT->VALUE < NODE->VALUE)
        {
            NODE->PARENT->RIGHT = NULL;
        }
        else
        {
            NODE->PARENT->LEFT = NULL;
        }
        NODE->PARENT = NULL;
        free(NODE);
        return value;
    }
    return value;
}

void clean(tree *t)
{
    node *NODE = (node *)malloc(sizeof(node));
    NODE = t->root;
    while (NODE->LEFT || NODE->RIGHT)
    {
        remove_min(NODE);
    }
    NODE->LEFT = NULL;
    NODE->RIGHT = NULL;
    NODE->PARENT = NULL;
    t->root = NULL;
    t->count = 0;
    free(NODE);
}

node *find(tree *t, long int value)
{
    if (t != NULL)
    {
        if (t->count > 0)
        {
            node *NODE;
            NODE = (node *)malloc(sizeof(node));
            NODE = t->root;

            while (NODE)
            {
                if (NODE->VALUE == value)
                {
                    return NODE;
                }
                else if ((NODE->VALUE < value) && NODE->RIGHT)
                {
                    NODE = NODE->RIGHT;
                }
                else if ((NODE->VALUE > value) && NODE->LEFT)
                {
                    NODE = NODE->LEFT;
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
    node *ADD;
    ADD = (node *)malloc(sizeof(node));
    ADD->PARENT = ADD;
    ADD->LEFT = NULL;
    ADD->RIGHT = NULL;
    ADD->VALUE = value;

    tree *tmp = (tree *)malloc(sizeof(tree));
    tmp = t;

    tree *tmp1 = (tree *)malloc(sizeof(tree));
    tmp1 = t;

    node *NODE = (node *)malloc(sizeof(node));
    NODE = tmp->root;
    if (tmp && NODE && ADD)
    {
        if (find(tmp1, value))
        {
            return 1;
        }
        else
        {
            if (tmp->count != 0)
            {
                NODE = tmp->root;
                while (NODE)
                {
                    if (value > NODE->VALUE)
                    {
                        if (NODE->RIGHT)
                        {
                            NODE = NODE->RIGHT;
                            continue;
                        }
                        else
                        {
                            ADD->PARENT = NODE;
                            NODE->RIGHT = ADD;
                            tmp->count = tmp->count + 1;
                            return 0;
                        }
                    }
                    else
                    {
                        if (NODE->LEFT)
                        {
                            NODE = NODE->LEFT;
                            continue;
                        }
                        else
                        {
                            ADD->PARENT = NODE;
                            NODE->LEFT = ADD;
                            tmp->count = tmp->count + 1;
                            return 0;
                        }
                    }
                }
                return 2;
            }
            else
            {
                tmp->root = ADD;
                tmp->count = 1;
                return 0;
            }
        }
    }
    else
    {
        return 2;
    }
}

long int remove_node(tree *t, long int value)
{
    node *FOUND = (node *)malloc(sizeof(node));
    FOUND = find(t, value);

    if (FOUND)
    {
        if (FOUND->LEFT && FOUND->RIGHT)
        {
            node *leftNode = (node *)malloc(sizeof(node));
            node *rightRoot = (node *)malloc(sizeof(node));
            node *leftNODE = (node *)malloc(sizeof(node));
            node *leftRightRootNode = (node *)malloc(sizeof(node));
            node *leftmostRightRootNode = (node *)malloc(sizeof(node));
            rightRoot = FOUND->RIGHT;
            leftNODE = FOUND->LEFT;
            if (rightRoot->LEFT)
            {
                leftNode = rightRoot->LEFT;
                while (leftNode->LEFT)
                {
                    leftNode = leftNode->LEFT;
                }
                if (leftNode->RIGHT)
                {
                    leftRightRootNode = leftNode->RIGHT;
                    if (rightRoot->RIGHT)
                    {
                        leftmostRightRootNode = rightRoot->RIGHT;
                        while (leftmostRightRootNode->LEFT)
                        {
                            leftmostRightRootNode = leftmostRightRootNode->LEFT;
                        }
                    }
                    else
                    {
                        leftmostRightRootNode = leftNode->PARENT;
                    }
                    leftRightRootNode->PARENT = leftmostRightRootNode;
                    leftmostRightRootNode->LEFT = leftRightRootNode;
                    leftNode->RIGHT = NULL;
                }
                leftNode->PARENT->LEFT = NULL;
                leftNode->PARENT = NULL;
                leftNode->RIGHT = rightRoot;
                rightRoot->PARENT = NULL;
                rightRoot->PARENT = leftNode;
                leftNode->LEFT = leftNODE;
                leftNODE->PARENT = NULL;
                leftNODE->PARENT = leftNode;
                leftNode->PARENT = FOUND->PARENT;
                if (leftNode->PARENT == FOUND)
                {
                    leftNode->PARENT = leftNode;
                    t->root = leftNode;
                }
                else
                {
                    if (leftNode->PARENT->VALUE < leftNode->VALUE)
                    {
                        leftNode->PARENT->RIGHT = leftNode;
                    }
                    else
                    {
                        leftNode->PARENT->LEFT = leftNode;
                    }
                }
                FOUND->LEFT = NULL;
                FOUND->RIGHT = NULL;
                FOUND->PARENT = NULL;
                FOUND = NULL;
                return 0;
            }
            else
            {
                rightRoot->LEFT = leftNODE;
                leftNODE->PARENT = NULL;
                leftNODE->PARENT = rightRoot;
                rightRoot->PARENT = FOUND->PARENT;
                if (rightRoot->PARENT == FOUND)
                {
                    rightRoot->PARENT = rightRoot;
                    t->root = rightRoot;
                }
                else
                {
                    if (rightRoot->PARENT->VALUE < rightRoot->VALUE)
                    {
                        rightRoot->PARENT->RIGHT = rightRoot;
                    }
                    else
                    {
                        rightRoot->PARENT->LEFT = rightRoot;
                    }
                }
                FOUND->LEFT = NULL;
                FOUND->RIGHT = NULL;
                FOUND->PARENT = NULL;
                FOUND = NULL;
                return 0;
            }
            return 0;
        }
        else if (FOUND->LEFT)
        {
            node *firstLeftNode = (node *)malloc(sizeof(node));
            firstLeftNode = FOUND->LEFT;
            if (t->root == FOUND)
            {
                firstLeftNode->PARENT = firstLeftNode;
                t->root = firstLeftNode;
            }
            else
            {
                firstLeftNode->PARENT = FOUND->PARENT;
                if (FOUND->VALUE > FOUND->PARENT->VALUE)
                {
                    firstLeftNode->PARENT->RIGHT = firstLeftNode;
                }
                else
                {
                    firstLeftNode->PARENT->LEFT = firstLeftNode;
                }
            }
            return 0;
        }
        else if (FOUND->RIGHT)
        {
            node *firstRightNode = (node *)malloc(sizeof(node));
            firstRightNode = FOUND->RIGHT;
            if (FOUND == t->root)
            {
                firstRightNode->PARENT = firstRightNode;
                t->root = firstRightNode;
            }
            else
            {
                firstRightNode->PARENT = FOUND->PARENT;
                if (FOUND->VALUE > FOUND->PARENT->VALUE)
                {
                    firstRightNode->PARENT->RIGHT = firstRightNode;
                }
                else
                {
                    firstRightNode->PARENT->LEFT = firstRightNode;
                }
            }
            return 0;
        }
        else
        {
            if (FOUND->VALUE > FOUND->PARENT->VALUE)
            {
                FOUND->PARENT->RIGHT = NULL;
            }
            else
            {
                FOUND->PARENT->LEFT = NULL;
            }
            FOUND->PARENT = NULL;
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

long int rotate_right(node *n)
{
    node *NODE = (node *)malloc(sizeof(node));
    NODE = n;

    node *leftNODE = (node *)malloc(sizeof(node));
    leftNODE = NODE->LEFT;

    if (NODE && leftNODE)
    {
        NODE->LEFT = leftNODE->RIGHT;
        if (leftNODE->RIGHT)
        {
            leftNODE->RIGHT->PARENT = NODE;
        }
        leftNODE->PARENT = NODE->PARENT;
        if (leftNODE->PARENT == NODE)
        {
            leftNODE->PARENT = leftNODE;
        }
        else
        {
            if (leftNODE->PARENT->VALUE < leftNODE->VALUE)
            {
                leftNODE->PARENT->RIGHT = leftNODE;
            }
            else
            {
                leftNODE->PARENT->LEFT = leftNODE;
            }
        }
        leftNODE->RIGHT = NODE;
        NODE->PARENT = leftNODE;
        return 0;
    }
    else
    {
        return 1;
    }
}

long int rotate_left(node *n)
{
    node *NODE = (node *)malloc(sizeof(node));
    NODE = n;

    node *rightNODE = (node *)malloc(sizeof(node));
    rightNODE = NODE->RIGHT;

    node *rightNodeLeftTree = (node *)malloc(sizeof(node));

    if (NODE && rightNODE)
    {
        rightNodeLeftTree = rightNODE->LEFT;
        NODE->RIGHT = rightNodeLeftTree;
        if (rightNodeLeftTree)
        {
            rightNodeLeftTree->PARENT = NODE;
        }
        rightNODE->PARENT = NODE->PARENT;
        if (rightNODE->PARENT == NODE)
        {
            rightNODE->PARENT = rightNODE;
        }
        NODE->PARENT = rightNODE;
        rightNODE->LEFT = NODE;
        return 0;
    }
    else
    {
        return 1;
    }
}

void print(node *n)
{
    node *NODE = (node *)malloc(sizeof(node));
    NODE = n;

    node *emptyNode = (node *)malloc(sizeof(node));

    if (NODE && emptyNode)
    {
        long int oldlvl = 1, lvl = 1, cnt = 0, i = 0, j = 0;
        node **nodes = (node **)malloc(lvl * sizeof(node *));
        nodes[0] = NODE;
        printf("%ld\n", nodes[0]->VALUE);
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
                if (nodes[i]->LEFT && nodes[i] != emptyNode)
                {
                    flag = true;
                    nodes[j] = nodes[i]->LEFT;
                }
                else
                {
                    nodes[j] = emptyNode;
                }
                j += 1;
                if (nodes[i]->RIGHT && nodes[i] != emptyNode)
                {
                    flag = true;
                    nodes[j] = nodes[i]->RIGHT;
                }
                else
                {
                    nodes[j] = emptyNode;
                }
            }
            if (flag)
            {
                for (i = oldlvl - 1; i < (lvl - 1); i++)
                {
                    if (nodes[i]->LEFT && nodes[i] != emptyNode)
                    {
                        printf("%ld ", nodes[i]->LEFT->VALUE);
                    }
                    else
                    {
                        printf("_ ");
                    }
                    ++j;
                    if (nodes[i]->RIGHT && nodes[i] != emptyNode)
                    {
                        printf("%ld ", nodes[i]->RIGHT->VALUE);
                    }
                    else
                    {
                        printf("_ ");
                    }
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    else
    {
        printf("-\n");
        printf("\n");
    }
}

// Вывести все значения дерева t, аналогично функции print
void print_tree(tree *t)
{
    node *NODE = (node *)malloc(sizeof(node));
    NODE = t->root;
    if (t->count > 0 && NODE)
        print(NODE);
    else
    {
        printf("-\n");
        printf("\n");
    }
}

int main()
{
    tree *binaryTree = (tree *)malloc(sizeof(tree));
    node *NODE = (node *)malloc(sizeof(node));
    long int value;
    init(binaryTree);
    for (long int i = 0; i < 4; i++)
    {
        scanf("%ld", &value);
        insert(binaryTree, value);
    }
    print_tree(binaryTree);
    for (long int i = 0; i < 3; i++)
    {
        scanf("%ld", &value);
        insert(binaryTree, value);
    }
    print_tree(binaryTree);
    long int m1;
    scanf("%ld", &m1);
    NODE = find(binaryTree, m1);
    if (NODE)
    {
        if (NODE->PARENT && NODE->PARENT != NODE)
            printf("%ld ", NODE->PARENT->VALUE);
        else
            printf("_ ");
        if (NODE->LEFT)
            printf("%ld ", NODE->LEFT->VALUE);
        else
            printf("_ ");
        if (NODE->RIGHT)
            printf("%ld", NODE->RIGHT->VALUE);
        else
            printf("_");
    }
    else
    {
        printf("-");
    }
    printf("\n");
    printf("\n");
    scanf("%ld", &m1);
    NODE = find(binaryTree, m1);
    if (NODE)
    {
        if (NODE->PARENT && NODE->PARENT != NODE)
            printf("%ld ", NODE->PARENT->VALUE);
        else
            printf("_ ");
        if (NODE->LEFT)
            printf("%ld ", NODE->LEFT->VALUE);
        else
            printf("_ ");
        if (NODE->RIGHT)
            printf("%ld", NODE->RIGHT->VALUE);
        else
            printf("_");
    }
    else
    {
        printf("-");
    }
    printf("\n");
    printf("\n");
    scanf("%ld", &m1);
    if (remove_node(binaryTree, m1) == 0)
    {
        binaryTree->count = binaryTree->count - 1;
    }
    if (binaryTree->count > 0)
    {
        NODE = binaryTree->root;
        binaryTree->root = NODE->PARENT;
    }
    print_tree(binaryTree);
    NODE = binaryTree->root;
    while (rotate_left(NODE) == 0)
    {
        binaryTree->root = NODE->PARENT;
        NODE = binaryTree->root;
    }
    print_tree(binaryTree);
    NODE = binaryTree->root;
    while (rotate_right(NODE) == 0)
    {
        binaryTree->root = NODE->PARENT;
        NODE = binaryTree->root;
    }
    print_tree(binaryTree);
    printf("%ld\n", binaryTree->count);
    printf("\n");
    clean(binaryTree);
    print_tree(binaryTree);
    return 0;
}