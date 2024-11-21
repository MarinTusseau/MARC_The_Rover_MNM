//
// Created by malog on 29/10/2024.
//

#ifndef UNTITLED1_TREE_NODE_H
#define UNTITLED1_TREE_NODE_H
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "moves.h"

struct s_node
{
    int value;
    struct s_node **nodes;
    int nbSons;
    t_move dispo;
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

p_tree createTreeFromMap(t_map map, int startX, int startY, int maxMoves);

void buildTreeFromMap(p_node currentNode, t_map map, int x, int y, int remainingMoves);

#endif //UNTITLED1_TREE_NODE_H
