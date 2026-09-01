// Bubble.c
#include "ASCIIQuarium.h"
#include <stdlib.h>

char *(*bubble_type_linker[BUBBLE_TYPE_COUNT])(void) = {
    [BUBBLE_ONE]   = bubble_one,
    [BUBBLE_TWO]   = bubble_two,
    [BUBBLE_THREE] = bubble_three
};

AnimationObject create_randomized_bubble(void) {
    int bubble_type = rand() % BUBBLE_TYPE_COUNT;
    int speed = (rand() % 2) + 1; // rise speed, 1-2

    Position pos = {
        .x = rand() % (frame_x - 2) + 1,
        .y = frame_y // spawn near the bottom, rises from there
    };

    AnimationObject bubble = create_animation_object(
        BUBBLE,
        (BubbleType)bubble_type,
        CLASSIC_UP,
        speed,
        &pos
    );
    return bubble;
}

char *get_bubble(int bubble_type) {
    return bubble_type_linker[bubble_type]();
}

char *bubble_one(void)
{
    return ".";
}

char *bubble_two(void)
{
    return "o";
}

char *bubble_three(void)
{
    return "O";
}