#include "character.h"

void character_init(Character* character, char symbol) {
    character->symbol = symbol;
}

char character_get_symbol(const Character* character) {
    return character->symbol;
}