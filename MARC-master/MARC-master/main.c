#include <stdio.h>
#include "map.h"
#include "tree_node.h"

int main() {
    t_map map;

// The following preprocessor directive checks if the code is being compiled on a Windows system.
// If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
// On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }

// printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }

    displayMap(map);


    srand(time(NULL));
    int movementPerPhase = 5;
    Dispo initDispo = {
            .disponibilities = {22, 15, 7, 7, 21, 21, 7}
    };
    t_move choice[9];
    Dispo dispoNow = initDispo;
    t_localisation loc = loc_init(4, 6, NORTH);
    chooseMovements(&dispoNow, choice, movementPerPhase, time(NULL), map, loc);

/**
    printf("\nMovements availible for this phase :\n");
    for (int i = 0; i < movementPerPhase; i++) {
        printf("%s\n", getMoveAsString(choice[i]));
    }

    t_localisation loc;
    loc.ori = NORTH;
    loc.pos.x = 2;
    int x = loc.pos.x;
    loc.pos.y = 3;
    int y = loc.pos.y;
    int val_start = map.costs[x][y];
    t_node n_start = createNode(val_start);
    p_tree t2 = createTreeFromMap(&n_start, map, &loc, choice, 5);
    displayTree(t2->root,0);
    printf("\nLe chemin le plus court vers '0' vaut : ");
    printf("%d\n", findMinPath(t2->root,0));**/


    p_tree tree = createTreeFromMap(NULL, map, &loc, choice, 5);

    //printf("Arbre des deplacements :\n");
    //displayTree(tree->root, 0);

    //findMinPath(tree->root, 0);

    freeTree(tree->root);

    free(tree);

    for (int i = 0; i < map.y_max; i++) {
        free(map.costs[i]);
    }
    free(map.costs);

    int choix = 999;
    while (choix != 0){
        printf("\n-------- MENU --------\n\n");
        printf("1. Afficher la map\n");
        printf("2. Lancer et afficher la sélection de mouvements aléatoire\n");
        printf("3. Afficher l'arbre complet (! La taille peut-être conséquente !)\n");
        printf("4. Lancer et visualiser la séquence de déplacement\n");
        printf("91 Séquence de présentation orale n°1\n");
        printf("92 Séquence de présentation orale n°2\n");
        printf("93 Séquence de présentation orale n°3\n");
        printf("0. SORTIE DU PROGRAMME");

        printf("\n! Les choix 9X correspondent aux séquences servant à la présentation orale uniquement !\n");
        printf("\n !!! Faites un choix parmis ceux ci-dessus : ");
        scanf("%d",&choix);

        if(choix==1){
            displayMap(map);
        }
        if(choix==2){
            srand(time(NULL));
            int movementPerPhase = 5;
            Dispo initDispo = {
                    .disponibilities = {22, 15, 7, 7, 21, 21, 7}
            };
            t_move choice[9];
            Dispo dispoNow = initDispo;
            t_localisation loc = loc_init(4, 6, NORTH);
            chooseMovements(&dispoNow, choice, movementPerPhase, time(NULL), map, loc);
        }
        if(choix==3){
            printf("! Chaque noeud aura ses fils sur sa droite et sur un meme niveau !\n! Chaque espace correspond a un niveau (ou couche) de l'arbre !\n");

        }
        if(choix==4){


        }
        if(choix==91){
            printf("Test des fonctions de base de création de noeuds et d'arbre :\n");
            t_node n1 = createNode(7);
            p_tree t = createTree(&n1);
            t_node n2 = createNode(4);
            addChild(&n1, &n2);
            t_node n5 = createNode(9);
            addChild(&n2, &n5);
            t_node n6 = createNode(10);
            addChild(&n2, &n6);
            t_node n3 = createNode(3);
            addChild(&n1, &n3);
            t_node n7 = createNode(10);
            addChild(&n3, &n7);
            t_node n8 = createNode(5);
            addChild(&n3, &n8);
            t_node n10 = createNode(7);
            addChild(&n7, &n10);
            t_node n11 = createNode(8);
            addChild(&n7, &n11);
            t_node n12 = createNode(0);
            addChild(&n10, &n12);
            t_node n4 = createNode(8);
            addChild(&n1, &n4);
            t_node n9 = createNode(0);
            addChild(&n4, &n9);
            printf("Test de l'affichage d'un arbre n-aire :\n");
            printf("! Chaque noeud aura ses fils sur sa droite et sur un meme niveau !\n! Chaque espace correspond a un niveau (ou couche) de l'arbre !\n");
            displayTree(t->root, 0);

            printf("Test du chemin le plus court vers la base dans un arbre sans coordonées :\n");
            printf("\nLe chemin le plus court vers un '0' vaut : ");
            printf("%d\n", findMinPath(t->root,0));
        }
        if(choix==92){


        }
        if(choix==93){


        }
    }

    return 0;

}

