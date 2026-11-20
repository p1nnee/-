#ifndef WORLD_H
#define WORLD_H

typedef struct {
    int rows;
    int cols;
    char** cells;
} World;

int world_create(World* world, int rows, int cols);

void world_destroy(World* world);

void world_print(const World* world);

int world_is_empty(const World* world, int row, int col);

int world_set_cell(World* world, int row, int col, char symbol);

int world_check_win(const World* world, char symbol);

#endif
