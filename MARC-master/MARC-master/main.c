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

    //findMinPath(tree->root, 0);

    int choix = 999;
    while (choix != 0) {
        printf("\n-------- MENU --------\n\n");
        printf("1. Afficher la map topographique\n");
        printf("2. Lancer et afficher la selection de mouvements aleatoire et la sequence de deplacement\n");
        printf("3. Afficher l'arbre complet (! La taille peut-etre consequente !)\n");
        printf("4. Afficher les 3 types de map\n");
        printf("91 Sequence de presentation orale no1\n");
        printf("92 Sequence de presentation orale no2\n");
        printf("93 Sequence de presentation orale no3\n");
        printf("0. SORTIE DU PROGRAMME");

        printf("\n!! Les choix 9X correspondent aux sequences servant a la presentation orale uniquement !!\n");
        printf("\nFaites un choix parmi ceux ci-dessus : ");
        scanf("%d", &choix);
        printf("\n");

        switch (choix) {
            case 1:
                displayMap(map);
                break;
            case 2:
                printf("Choisissez les coordonnees de depart du rover (x y) : \n");
                printf("Coordonnees de test :\nCrevasse : 4 0\nBase : 2 1\nDepart : 4 6\n");
                int xInit, yInit;
                scanf("%d %d", &xInit, &yInit);
                srand(time(NULL));
                int movementPerPhase = 5;
                Dispo initDispo = {
                        .disponibilities = {22, 15, 7, 7, 21, 21, 7}
                };
                t_move choice[9];
                Dispo dispoNow = initDispo;
                t_localisation loc = loc_init(xInit, yInit, NORTH);
                chooseMovements(&dispoNow, choice, movementPerPhase, time(NULL), map, loc);
                break;
            case 3:
                printf("! Chaque noeud aura ses fils sur sa droite et sur un meme niveau !\n! Chaque espace correspond a un niveau (ou couche) de l'arbre !\n");

                p_tree tree = createTreeFromMap(NULL, map, &loc, choice, 5);

                printf("Arbre des deplacements :\n");
                displayTree(tree->root, 0);

                freeTree(tree->root);

                free(tree);

                for (int i = 0; i < map.y_max; i++) {
                    free(map.costs[i]);
                }
                free(map.costs);
                break;
            case 4:
                printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
                for (int i = 0; i < map.y_max; i++)
                {
                    for (int j = 0; j < map.x_max; j++)
                    {
                        printf("%d ", map.soils[i][j]);
                    }
                    printf("\n");
                }
                printf("\n");

                // printf the costs, aligned left 5 digits
                for (int i = 0; i < map.y_max; i++)
                {
                    for (int j = 0; j < map.x_max; j++)
                    {
                        printf("%-5d ", map.costs[i][j]);
                    }
                    printf("\n");
                }
                printf("\n");

                displayMap(map);

                break;
            case 91:
                printf("Test des fonctions de base de creation de noeuds et d'arbre :\n");
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
                displayNormalTree(t->root, 0);

                printf("Test du chemin le plus court vers la base dans un arbre sans coordonees :\n");
                int cout = findMinPath(t->root, 0);
                printf("\nLe chemin le plus court vers un '0' vaut : ");
                printf("%d\n", cout);
                break;
            case 92:
                // Add code for option 92 here
                break;
            case 93:
                // Add code for option 93 here
                break;
            case 0:
                printf("SORTIE DU PROGRAMME\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    }
    return 0;
}