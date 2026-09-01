// Seaweed.c
#include "ASCIIQuarium.h"
#include <stdlib.h>

char *(*seaweed_type_linker[SEAWEED_TYPE_COUNT])(void) = {
    [SEAWEED_ONE]   = seaweed_one,
    [SEAWEED_TWO]   = seaweed_two,
    [SEAWEED_THREE] = seaweed_three
};

AnimationObject create_randomized_seaweed(void) {
    int seaweed_type = rand() % SEAWEED_TYPE_COUNT;
    int height = 2 + (seaweed_type * 2); // taller variants for later types
    int speed = (rand() % 3) + 1;        // sway speed, 1-3

    Position pos = {
        .x = rand() % (frame_x - 2) + 1,
        .y = frame_y - height - 1        // rooted at the bottom
    };

    AnimationObject seaweed = create_animation_object(
        SEAWEED,
        (SeaweedType)seaweed_type,
        CLASSIC_STATIC,
        speed,
        &pos
    );
    return seaweed;
}

char *get_seaweed(int seaweed_type) {
    return seaweed_type_linker[seaweed_type]();
}

char *seaweed_one(void)
{
    return "  (\n"
           "  )\n"
           "  (\n";
}

char *seaweed_two(void)
{
    return "  (\n"
           "  )\n"
           "  (\n"
           "  )\n";
}

char *seaweed_three(void)
{
    return "  )\n"
           "  (\n"
           "  )\n"
           "  (\n"
           "  )\n";
}