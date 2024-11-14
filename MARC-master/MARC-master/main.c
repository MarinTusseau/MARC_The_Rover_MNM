#include <stdio.h>
#include "map.h"
#include "tree_node.h"

int main() {
    /**
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
**/

    printf("--------------------------------------------\n");

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

    displayTree(t->root, 0);

    printf("\nLe chemin le plus court vers un '0' est : ");
    printf("%d\n", findMinPath(t->root,0));







    return 0;
}

