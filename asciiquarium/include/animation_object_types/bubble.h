#ifndef BUBBLE_H
#define BUBBLE_H

typedef enum
{
    BUBBLE_ONE,
    BUBBLE_TWO,
    BUBBLE_THREE,

    BUBBLE_TYPE_COUNT
} BubbleType;

extern char *(*bubble_type_linker[BUBBLE_TYPE_COUNT])(void);

char *get_bubble(int bubble_type);

char *bubble_one(void);
char *bubble_two(void);
char *bubble_three(void);

AnimationObject create_randomized_bubble(void);

#endif