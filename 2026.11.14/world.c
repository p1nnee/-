#include <stdio.h>
#include <stdlib.h>
#include "world.h"

int world_create(World* world, int rows, int cols) {
    int i;

    world->rows = rows;
    world->cols = cols;

    world->cells = malloc(rows * sizeof(char*));

    if (world->cells == NULL) {
        return 0;
    }

    for (i = 0; i < rows; i++) {
        world->cells[i] = malloc(cols * sizeof(char));

        if (world->cells[i] == NULL) {
            while (i > 0) {
                i--;
                free(world->cells[i]);
            }

            free(world->cells);
            world->cells = NULL;

            return 0;
        }

        for (int j = 0; j < cols; j++) {
            world->cells[i][j] = ' ';
        }
    }

    return 1;
}

void world_destroy(World* world) {
    int i;

    if (world->cells == NULL) {
        return;
    }

    for (i = 0; i < world->rows; i++) {
        free(world->cells[i]);
    }

    free(world->cells);
    world->cells = NULL;
}

void world_print(const World* world) {
    int i, j;

    printf("\n");

    for (i = 0; i < world->rows; i++) {

        for (j = 0; j < world->cols; j++) {
            printf("+---");
        }

        printf("+\n");

        for (j = 0; j < world->cols; j++) {
            printf("| %c ", world->cells[i][j]);
        }

        printf("|\n");
    }

    for (j = 0; j < world->cols; j++) {
        printf("+---");
    }

    printf("+\n\n");
}

int world_is_empty(const World* world, int row, int col) {
    if (row < 0 || row >= world->rows ||
        col < 0 || col >= world->cols) {
        return 0;
    }

    return world->cells[row][col] == ' ';
}

int world_set_cell(World* world, int row, int col, char symbol) {
    if (!world_is_empty(world, row, col)) {
        return 0;
    }

    world->cells[row][col] = symbol;

    return 1;
}

int world_check_win(const World* world, char symbol)
{
    int directions[4][2] = {
        {0, 1},   // horizontal
        {1, 0},   // vertical
        {1, 1},   // diagonal down-right
        {1, -1}   // diagonal down-left
    };

    for (int row = 0; row < world->rows; row++)
    {
        for (int col = 0; col < world->cols; col++)
        {
            if (world->cells[row][col] != symbol)
                continue;

            for (int d = 0; d < 4; d++)
            {
                int dr = directions[d][0];
                int dc = directions[d][1];

                int r1 = row + dr;
                int c1 = col + dc;
                int r2 = row + 2 * dr;
                int c2 = col + 2 * dc;

                if (r1 >= 0 && r1 < world->rows &&
                    c1 >= 0 && c1 < world->cols &&
                    r2 >= 0 && r2 < world->rows &&
                    c2 >= 0 && c2 < world->cols)
                {
                    if (world->cells[r1][c1] == symbol &&
                        world->cells[r2][c2] == symbol)
                    {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}