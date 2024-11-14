//
// Created by malog on 29/10/2024.
//

#include "tree_node.h"

p_node createNode(int value){
    p_node n;
    n->value = value;
    n->left = NULL;
    n->left = NULL;
    return n;
}

p_tree createTree(p_node n){
    p_tree t;
    t->root = n;
    return t;
}