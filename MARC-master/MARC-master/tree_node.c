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

void insertBST(t_tree* t, int value){
    p_node new_node=createNode(value);
    p_node curr=t->root;
    if (curr==NULL){
        t->root=new_node;
        return;
    }
    while(1){
        if (curr->value<value){
            if (curr->right!=NULL)
                curr=curr->right;
            else {
                curr->right=new_node;
                return;
            }
        } else{
            if (curr->left!=NULL)
                curr=curr->left;
            else {
                curr->left=new_node;
                return;
            }
        }
    }
}