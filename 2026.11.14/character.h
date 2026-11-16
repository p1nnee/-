#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct {
    char symbol;
} Character;

void character_init(Character* character, char symbol);

char character_get_symbol(const Character* character);

#endif
