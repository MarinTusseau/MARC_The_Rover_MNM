#include "moves.h"
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <time.h>
#include <string.h>

/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */

/**
 * @brief Function to rotate the robot according to a move and its actual orientation
 * @param ori : the actual orientation of the robot
 * @param move : the move to do
 * @return the new orientation of the robot
 */
t_orientation rotate(t_orientation, t_move );

/**
 * @brief function to translate the robot according to a move and its actual position
 * @param loc : the actual localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation translate(t_localisation , t_move);

/* definition of local functions */

t_orientation rotate(t_orientation ori, t_move move)
{
    int rst;
    switch (move)
    {
        case T_LEFT:
            rst=3;
            break;
        case T_RIGHT:
            rst=1;
            break;
        case U_TURN:
            rst=2;
            break;
        default:
            break;
    }
    return (ori+rst)%4;
}

t_localisation translate(t_localisation loc, t_move move)
{
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */
    t_position res = loc.pos;
    switch (move) {
        case F_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 3;
                    break;
                case EAST:
                    res.x = loc.pos.x + 3;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 3;
                    break;
                case WEST:
                    res.x = loc.pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y + 1;
                    break;
                case EAST:
                    res.x = loc.pos.x - 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y - 1;
                    break;
                case WEST:
                    res.x = loc.pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return loc_init(res.x, res.y, loc.ori);

}

/* definitions of exported functions */

char *getMoveAsString(t_move move)
{
    return _moves[move];
}

t_localisation move(t_localisation loc, t_move move)
{
    t_localisation new_loc=loc;
    if ((move >=T_LEFT) && (move <= U_TURN))
    {
        new_loc.ori = rotate(loc.ori, move);
    } else {
        new_loc = translate(loc, move);
    }

    return new_loc;
}

void updateLocalisation(t_localisation *p_loc, t_move m)
{
    *p_loc = move(*p_loc, m);
    return;
}

#define NUM_MOVES 7

void chooseMovements(Dispo *dispo, t_move choice[], int nbChoice, unsigned int seed, t_map map, t_localisation loc) {
    srand(seed);
    printf("Movement disponibilities at the beginning:\n");
    for (int k = 0; k < NUM_MOVES; k++) {
        printf("%d ", dispo->disponibilities[k]);
    }

    printf("\n\n");
    displayMapWithRover(map, loc);
    printf("Current cost: %d\n", map.costs[loc.pos.y][loc.pos.x]);
    int totalMoves = 0;
    while (totalMoves < nbChoice) {
        for (int i = 0; i < 5 && totalMoves < nbChoice; i++, totalMoves++) {
            int movementChosen = -1;
            for (int attempt = 0; attempt < NUM_MOVES; attempt++) {
                int candidateMove = rand() % NUM_MOVES;
                if (dispo->disponibilities[candidateMove] > 0) {
                    t_localisation newLoc = loc;
                    updateLocalisation(&newLoc, (t_move) candidateMove);
                    if (newLoc.pos.x >= 0 && newLoc.pos.x < map.x_max && newLoc.pos.y >= 0 && newLoc.pos.y < map.y_max) {
                        movementChosen = candidateMove;
                        break;
                    }
                }
            }

            if (movementChosen == -1) {
                printf("No valid moves available. Rover would go out of bounds.\n");
                return;
            }

            choice[totalMoves] = (t_move) movementChosen;
            dispo->disponibilities[movementChosen]--;
            printf("Movement chosen: %s\n", getMoveAsString(choice[totalMoves]));
        }
        printf("\n");

        for (int i = totalMoves - 5; i < totalMoves; i++) {
            updateLocalisation(&loc, choice[i]);
            printf("Movement applied: %s\n", getMoveAsString(choice[i]));
            printf("Current position: (%d, %d)\n", loc.pos.x, loc.pos.y);
            printf("Current cost: %d\n", map.costs[loc.pos.y][loc.pos.x]);
            displayMapWithRover(map, loc);

            if (map.costs[loc.pos.y][loc.pos.x] == 0) {
                printf("Rover reached the base.\n");
                return;
            }
        }
        if (map.costs[loc.pos.y][loc.pos.x] != 0) {
            printf("Rover did not reach the base after 5 moves. Removing 5 random moves.\n");
            for (int i = 0; i < 5 && totalMoves > 0; i++, totalMoves--) {
                int moveToRemove = rand() % totalMoves;
                dispo->disponibilities[choice[moveToRemove]]++;
                for (int j = moveToRemove; j < totalMoves - 1; j++) {
                    choice[j] = choice[j + 1];

                }
            }
        }
    }

    printf("Rover did not reach the base within the given moves.\n");
}

void displayMapWithRover(t_map map, t_localisation loc) {
    for (int i = 0; i < map.y_max; i++) {
        for (int rep = 0; rep < 3; rep++) {
            for (int j = 0; j < map.x_max; j++) {
                if (i == loc.pos.y && j == loc.pos.x && rep == 1) {
                    printf(" Ro ");
                } else {
                    char c[4];
                    switch (map.soils[i][j]) {
                        case BASE_STATION:
                            if (rep == 1) {
                                strcpy(c, " B ");
                            } else {
                                strcpy(c, "   ");
                            }
                            break;
                        case PLAIN:
                            strcpy(c, "---");
                            break;
                        case ERG:
                            strcpy(c, "~~~");
                            break;
                        case REG:
                            strcpy(c, "^^^");
                            break;
                        case CREVASSE:
                            sprintf(c, "%c%c%c", 219, 219, 219);
                            break;
                        default:
                            strcpy(c, "???");
                            break;
                    }
                    printf("%s", c);
                }
            }
            printf("\n");
        }
    }
}