#ifndef FISH_H
#define FISH_H

typedef enum
{
    SMALL_FISH_ONE,
    SMALL_FISH_TWO,
    SMALL_FISH_THREE,
    LARGE_FISH_ONE,
    LARGE_FISH_TWO,
    LARGE_FISH_THREE,

    FISH_TYPE_COUNT
} FishType;

extern char *(*fish_type_linker[FISH_TYPE_COUNT])(void);

char *get_fish(FishType fish_type);

char *small_fish_one(void);
char *small_fish_two(void);
char *small_fish_three(void);
char *large_fish_one(void);
char *large_fish_two(void);
char *large_fish_three(void);

#endif