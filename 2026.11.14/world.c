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

int world_check_win(const World* world) {
    int dr[] = { 0, 1, 1, 1 };
    int dc[] = { 1, 0, 1, -1 };

    int r, c, d;

    for (d = 0; d < 4; d++) {

        for (r = 0; r < world->rows; r++) {

            for (c = 0; c < world->cols; c++) {

                int prev_r = r - dr[d];
                int prev_c = c - dc[d];

                if (prev_r >= 0 && prev_r < world->rows &&
                    prev_c >= 0 && prev_c < world->cols) {
                    continue;
                }

                char symbol = world->cells[r][c];

                if (symbol == ' ') {
                    continue;
                }

                int nr = r;
                int nc = c;
                int length = 0;
                int same = 1;

                while (nr >= 0 && nr < world->rows &&
                    nc >= 0 && nc < world->cols) {

                    if (world->cells[nr][nc] != symbol) {
                        same = 0;
                    }

                    length++;

                    nr += dr[d];
                    nc += dc[d];
                }

                if (same && length > 1) {
                    return 1;
                }
            }
        }
    }

    return 0;
}