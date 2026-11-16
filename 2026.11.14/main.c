#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "world.h"
#include "character.h"

#define MAX_SIZE 50

int read_int(const char* message, int min, int max) {
    char buffer[128];
    char* end;
    long value;

    while (1) {
        printf("%s", message);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            exit(1);
        }

        value = strtol(buffer, &end, 10);

        while (*end == ' ' || *end == '\t' ||
            *end == '\n' || *end == '\r') {
            end++;
        }

        if (end == buffer || *end != '\0' ||
            value < min || value > max) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        return (int)value;
    }
}

char read_symbol(const char* message, char forbidden) {
    char buffer[128];

    while (1) {
        printf("%s", message);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            exit(1);
        }

        if (strlen(buffer) == 2 &&
            buffer[1] == '\n' &&
            (unsigned char)buffer[0] >= 33 &&
            (unsigned char)buffer[0] <= 126 &&
            buffer[0] != forbidden) {

            return buffer[0];
        }

        printf("Enter one printable ASCII character, different from the other player's symbol.\n");
    }
}

int main(void) {
    World world;

    Character player1;
    Character player2;

    Character* current_player;

    int rows;
    int cols;

    int row;
    int col;

    int moves = 0;
    int game_over = 0;

    printf("=================================\n");
    printf("       TIC-TAC-TOE GAME\n");
    printf("=================================\n\n");

    rows = read_int("Enter number of rows (1-50): ", 1, MAX_SIZE);

    cols = read_int("Enter number of columns (1-50): ", 1, MAX_SIZE);

    character_init(
        &player1,
        read_symbol("Player 1, choose your symbol: ", '\0')
    );

    character_init(
        &player2,
        read_symbol("Player 2, choose your symbol: ",
            character_get_symbol(&player1))
    );

    if (!world_create(&world, rows, cols)) {
        printf("Error: cannot create the game field.\n");
        return 1;
    }

    current_player = &player1;

    printf("\nThe game has started!\n");

    while (!game_over) {

        world_print(&world);

        printf("Player's turn: %c\n",
            character_get_symbol(current_player));

        row = read_int("Enter row: ", 1, rows) - 1;

        col = read_int("Enter column: ", 1, cols) - 1;

        if (!world_is_empty(&world, row, col)) {
            printf("This cell is already occupied! Try again.\n");
            continue;
        }

        world_set_cell(
            &world,
            row,
            col,
            character_get_symbol(current_player)
        );

        moves++;

        if (world_check_win(&world)) {
            world_print(&world);

            printf("Player %c wins!\n",
                character_get_symbol(current_player));

            game_over = 1;
        }
        else if (moves == rows * cols) {
            world_print(&world);

            printf("Draw! No empty cells left.\n");

            game_over = 1;
        }
        else {
            if (current_player == &player1) {
                current_player = &player2;
            }
            else {
                current_player = &player1;
            }
        }
    }

    world_destroy(&world);

    printf("\nGame finished. Thank you for playing!\n");

    return 0;
}