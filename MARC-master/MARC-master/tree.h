//
// Created by malog on 29/10/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

typedef struct s_node
{
    int value;
    int depth; //jsp pourquoi mais c'était dans le ppt
    struct s_node **sons; //tableau de nodes
    struct s_node *parent; //simple node (pas sûr que ça soit utile)
    int nbSons;
} t_node;

//pour stocker le chemin jusqu'à une feuille on va stocker les nodes dans une pile (PPT 6 page 29)
//le chemin ça va être le coût ducoup (ça rime)




#endif //UNTITLED1_TREE_H
