//
// Created by malog on 29/10/2024.
//

#include "tree_node.h"

t_node createNode(int value){
    t_node n;
    n.value = value;
    n.child = NULL;
    n.nbSons = 0;
    n.x_pos = 0;
    n.y_pos = 0;
    n.dispo = 0;
    return n;
}

p_tree createTree(p_node root) {
    p_tree newTree = (p_tree)malloc(sizeof(t_tree));
    newTree->root = root;
    return newTree;
}

void addChild(p_node parent, p_node child) {
    parent->nbSons++;
    parent->child = (p_node *)realloc(parent->child, parent->nbSons * sizeof(p_node));
    parent->child[parent->nbSons - 1] = child;
}

// Above are the basic functions used before on trees and sons

void displayTree(p_node node, int level) {
    if (!node) {
        return; // To avoid segmentation fault (we had this error many times)
    }

    // For every level we had a tabulation
    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    // We print the different node parameter
    printf("%s, (%d, %d)\n",
           getMoveAsString((t_move)node->dispo),
           node->x_pos,
           node->y_pos);

    // We go through the other sons recursively
    for (int i = 0; i < node->nbSons; i++) {
        displayTree(node->child[i], level + 1);
    }
}



int findMinPath(p_node node, int currentSum) {
    // Check if the current node is the base (cost = 0)
    if (node->value == 0) {
        printf("BASE\n");
        return currentSum;
    }

    // Add the cost of the node to the current sum
    currentSum += node->value;

    // If the node have no child we end it here
    if (node->nbSons == 0) {
        return currentSum;
    }

    // Initialize the minimum with a huge number, so it will change in any case
    int minSum = 99999999;

    // We use the function on every son of the current node and modify the sum depending on the cheapest node
    for (int i = 0; i < node->nbSons; i++) {
        int childMinSum = findMinPath(node->child[i], currentSum);
        if (childMinSum < minSum) {
            minSum = childMinSum;
            int x = node->child[i]->x_pos;
            int y = node->child[i]->y_pos;
            printf("[x : %d, y : %d]\n",x,y);
        }
    }
    printf("END\n");
    return minSum;
}




//LAST UPDATE


void buildTreeFromMap(p_node currentNode, t_map map, t_localisation *loc, t_move *remainingMoves, int nb_moves) {
    // If there are no moves left we don't do anything (stopping condition)
    if (nb_moves <= 0) {
        return;
    }

    // For every move remaining
    for (int i = 0; i < 7; i++) {
        if (remainingMoves[i] > 0) {
            remainingMoves[i]--;

            // Updating the new coord. depending on the move selected
            t_localisation newLoc = *loc;
            updateLocalisation(&newLoc, (t_move)i);

            int x = newLoc.pos.x;
            int y = newLoc.pos.y;

            // If we get out of the map
            if (x < 0 || y < 0 || x >= map.x_max || y >= map.y_max) {
                remainingMoves[i]++;
                continue; // Next iteration (i++)
            }

            // We create a new node with the corrct parameters
            p_node newNode = malloc(sizeof(t_node));
            *newNode = createNode(map.costs[y][x]);
            newNode->x_pos = x;
            newNode->y_pos = y;
            newNode->dispo = i;

            // And we add it to the tree
            addChild(currentNode, newNode);

            // Finally we reload the function
            buildTreeFromMap(newNode, map, &newLoc, remainingMoves, nb_moves - 1);
            remainingMoves[i]++;
        }
    }
}



p_tree createTreeFromMap(p_node currentNode, t_map map, t_localisation *loc, t_move *remainingMoves, int nb_moves) {
    int x = loc->pos.x;
    int y = loc->pos.y;
    // Here to make the use of x and y easier

    p_tree tree = malloc(sizeof(t_tree));
    tree->root = malloc(sizeof(t_node));
    *tree->root = createNode(map.costs[y][x]);
    tree->root->x_pos = x;
    tree->root->y_pos = y;
    // Creation of the tree with the correct parameters

    buildTreeFromMap(tree->root, map, loc, remainingMoves, nb_moves);
    // We launch the recursive function

    return tree;
}

void freeTree(p_node node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < node->nbSons; i++) {
        freeTree(node->child[i]);
    }

    if (node->child != NULL) {
        free(node->child);
    }
    free(node);
}
