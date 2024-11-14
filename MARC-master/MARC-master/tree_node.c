//
// Created by malog on 29/10/2024.
//

#include "tree_node.h"

t_node createNode(int value){
    t_node n;
    n.value = value;
    n.nodes = NULL;
    n.nbSons = 0;
    return n;
}

p_tree createTree(p_node root) {
    p_tree newTree = (p_tree)malloc(sizeof(t_tree));
    newTree->root = root;
    return newTree;
}

void displayTree(p_node node, int level) {
    if (level > 0){
        for (int k = 0; k < level; k++){
            printf("    ");
        }
    }
    printf("%d\n", node->value);

    if (node->nbSons > 0) {
        for (int i = 0; i < node->nbSons; i++) {
            if (i == node->nbSons - 1) {
                displayTree(node->nodes[i], level+1);
            } else {
                displayTree(node->nodes[i], level+1);
            }
        }
    }
}

void addChild(p_node parent, p_node child) {
    parent->nbSons++;
    parent->nodes = (p_node *)realloc(parent->nodes, parent->nbSons * sizeof(p_node));
    parent->nodes[parent->nbSons - 1] = child;
}

int findMinPath(p_node node, int currentSum) {

    if (node->value == 0) {
        return currentSum;
    }

    currentSum += node->value;

    if (node->nbSons == 0) {
        return currentSum;
    }

    int minSum = 99999999;

    for (int i = 0; i < node->nbSons; i++) {
        int childMinSum = findMinPath(node->nodes[i], currentSum);
        if (childMinSum < minSum) {
            minSum = childMinSum;
        }
    }

    return minSum;
}

