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
    struct s_node   *left, *right;
    int depth;
};

typedef struct s_node t_node, *p_node;

typedef struct s_tree
{
    p_node root;
} t_tree, *p_tree;

p_node createNode(int value);

p_tree createTree(p_node n);




#endif //UNTITLED1_TREE_NODE_H
