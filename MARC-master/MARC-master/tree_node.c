//
// Created by malog on 29/10/2024.
//

#include "tree_node.h"

t_node createNode(int value){
    t_node n;
    n.value = value;
    n.child = NULL;
    n.nbSons = 0;
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

void displayTree(p_node node, int level) {
    if (!node) {
        return; // Évite les erreurs de segmentation
    }

    // Indentation pour le niveau actuel
    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    // Affiche les détails du nœud
    printf("%s, (%d, %d)\n",
           getMoveAsString((t_move)node->dispo),
           node->x_pos,
           node->y_pos);

    // Parcourt les enfants récursivement
    for (int i = 0; i < node->nbSons; i++) {
        displayTree(node->child[i], level + 1);
    }
}



int findMinPath(p_node node, int currentSum) {
    // Vérifie si le nœud courant contient la valeur 0 (arrivée à la base)
    if (node->value == 0) {
        return currentSum;
    }

    // Ajoute la valeur du nœud courant à la somme
    currentSum += node->value;
    // Si le nœud n'a pas d'enfants (fin du chemin)
    if (node->nbSons == 0) {
        return currentSum;
    }

    // Initialise la somme minimale avec une grande valeur
    int minSum = 99999999;

    // Parcourt chaque enfant pour calculer les sommes minimales récursivement
    for (int i = 0; i < node->nbSons; i++) {
        int childMinSum = findMinPath(node->child[i], currentSum);
        if (childMinSum < minSum) {
            minSum = childMinSum;
        }
    }

    return minSum;
}

//ATTENTION DANS CES DEUX FONCTIONS IL FAUDRA RAJOUTER UN TABLEAU AVEC LES MOUVEMENTS DISPO
//LA FONCTION CREATE PERMET DE DEBUTER LA RECURSIVITE
//LA FONCTION BUILD FAIT LA RECURSIVITE DANS LA FNCTION CREATE


//LAST UPDATE


void buildTreeFromMap(p_node currentNode, t_map map, t_localisation *loc, t_move *remainingMoves, int nb_moves) {
    if (nb_moves <= 0) {
        return;
    }

    for (int i = 0; i < 7; i++) {
        if (remainingMoves[i] > 0) {
            remainingMoves[i]--;

            t_localisation newLoc = *loc;
            updateLocalisation(&newLoc, (t_move)i);

            int x = newLoc.pos.x;
            int y = newLoc.pos.y;
            if (x < 0 || y < 0 || x >= map.x_max || y >= map.y_max) {
                remainingMoves[i]++;
                continue;
            }

            p_node newNode = malloc(sizeof(t_node));
            *newNode = createNode(map.costs[y][x]);
            newNode->x_pos = x;
            newNode->y_pos = y;
            newNode->dispo = i;

            addChild(currentNode, newNode);

            buildTreeFromMap(newNode, map, &newLoc, remainingMoves, nb_moves - 1);
            remainingMoves[i]++;
        }
    }
}



p_tree createTreeFromMap(p_node currentNode, t_map map, t_localisation *loc, t_move *remainingMoves, int nb_moves) {
    int x = loc->pos.x;
    int y = loc->pos.y;

    p_tree tree = malloc(sizeof(t_tree));
    tree->root = malloc(sizeof(t_node));
    *tree->root = createNode(map.costs[y][x]);
    tree->root->x_pos = x;
    tree->root->y_pos = y;

    buildTreeFromMap(tree->root, map, loc, remainingMoves, nb_moves);
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
