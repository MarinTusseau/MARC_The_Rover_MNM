//
// Created by malog on 29/10/2024.
//

#ifndef UNTITLED1_TREE_NODE_H
#define UNTITLED1_TREE_NODE_H
#include <stdio.h>
#include <stdlib.h>
struct s_node
{
    int value;
    struct s_node **nodes;
    int nbSons;
};

typedef struct s_node t_node, *p_node;

typedef struct s_tree
{
    p_node root;
} t_tree, *p_tree;

t_node createNode(int value);

p_tree createTree(p_node n);

void addChild(p_node parent, p_node child);

int findMinPath(p_node node, int currentSum);

void displayTree(p_node node, int level);

#endif //UNTITLED1_TREE_NODE_H
