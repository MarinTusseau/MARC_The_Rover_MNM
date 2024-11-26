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

    int choix = 999;
    while (choix != 0) {
        printf("\n-------- MENU --------\n\n");
        printf("1. Afficher la map topographique\n");
        printf("2. Lancer et afficher la selection de mouvements aleatoire et la sequence de deplacement\n");
        printf("3. Afficher l'arbre complet (! La taille peut-etre consequente !)\n");
        printf("4. Afficher la map avec le cout unique de chaque case \n");
        printf("5. Afficher la map avec les cout totaux additones depuis le depart \n");
        printf("6. Presentation et affichage des fonctions de base pour un arbre n-aire sans coordonees \n");
        printf("0. SORTIE DU PROGRAMME");

        printf("\nFaites un choix parmi ceux ci-dessus : ");
        scanf("%d", &choix);
        printf("\n");

        switch (choix) {
            case 1:
                displayMap(map);
                break;
            case 2:
                printf("Coordonnees de test :\nCrevasse : 4 0\nBase : 2 1\nDepart classique : 4 6\n");
                printf("Choisissez les coordonnees de depart du rover (x y) : ");
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
                printf("Map avec les couts uniques par case de dimension %d x %d\n\n", map.y_max, map.x_max);
                for (int i = 0; i < map.y_max; i++)
                {
                    for (int j = 0; j < map.x_max; j++)
                    {
                        printf("%d ", map.soils[i][j]);
                    }
                    printf("\n");
                }
                printf("\n");


                break;
            case 5:
                printf("Map avec les couts totaux pour arriver a la base\n\n");
                for (int i = 0; i < map.y_max; i++)
                {
                    for (int j = 0; j < map.x_max; j++)
                    {
                        printf("%-5d ", map.costs[i][j]);
                    }
                    printf("\n");
                }
                printf("\n");// printf the costs, aligned left 5 digits


                break;

            case 6:
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

            case 0:
                printf("SORTIE DU PROGRAMME\n");
                break;

            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }
    }
    return 0;
}