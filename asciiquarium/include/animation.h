#ifndef ANIMATION_H
#define ANIMATION_H

#include "text_chunk.h"

typedef enum
{
    CLASSIC_LEFT,
    CLASSIC_RIGHT,
    CLASSIC_UP,
    CLASSIC_DOWN
} AnimationType;

typedef struct
{
    int animationID;
    void *update_animation;
    char *text_chunk;

    int x;
    int y;

    int speed;
} AnimationObject;

typedef struct
{
    AnimationObject *items;

    int count;
    int capacity;
} AnimationList;


void add_animation_object_to_stack(
    AnimationList *animations,
    AnimationObject object
);

void remove_animation_from_stack(
    AnimationList *animations,
    int index
);

void run_animations(
    AnimationList *animations
);

void classic_animate_left(
    AnimationObject *animation_object
);

void classic_animate_right(
    AnimationObject *animation_object
);

void classic_animate_up(
    AnimationObject *animation_object
);

void classic_animate_down(
    AnimationObject *animation_object
);

#endif