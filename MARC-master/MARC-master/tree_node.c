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


//ATTENTION DANS CES DEUX FONCTIONS IL FAUDRA RAJOUTER UN TABLEAU AVEC LES MOUVEMENTS DISPO
//LA FONCTION CREATE PERMET DE DEBUTER LA RECURSIVITE
//LA FONCTION BUILD FAIT LA RECURSIVITE DANS LA FNCTION CREATE


//LAST UPDATE


void buildTreeFromMap(p_node currentNode, t_map map, int x, int y, int remainingMoves) {
    // SI ON SORT DES LIMITES OU Y'A PLUS DE MOUVEMENTS DISPO C FINITO
    if (remainingMoves <= 0 || x < 0 || x >= map.y_max || y < 0 || y >= map.x_max) {
        return;
    }

    //on crée le noeud (si la condition au dessus est respectée) du déplacement dans l'arbre
    t_node newNode = createNode(map.costs[x][y]);
    addChild(currentNode, &newNode);

    // EN IMAGINEANT QU'ON AI QUE 4 MOUVEMENTTS UP DOWN LEFT RIGHT
    int movements[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    //on recrée des noeuds pour chaque deplacements en rappelant la fonction
    for (int i = 0; i < 4; i++) {
        int newX = x + movements[i][0];
        int newY = y + movements[i][1];
        buildTreeFromMap(currentNode->nodes[currentNode->nbSons - 1], map, newX, newY, remainingMoves - 1);
    }
}


p_tree createTreeFromMap(t_map map, int startX, int startY, int maxMoves) {
    //je pense qu'on peut utiliser les fonctions deja faites mais vsy flm
    //on alloue dynamiquement et on créer ce qui va nous servir
    p_tree tree = malloc(sizeof(t_tree));
    tree->root = malloc(sizeof(t_node));
    *tree->root = createNode(map.costs[startY][startX]);

    //on lance la fonction réccursive pour créer l'arbre avec la map
    buildTreeFromMap(tree->root, map, startY, startX, maxMoves);
    return tree;
}