#ifndef ANIMATION_H
#define ANIMATION_H

#include "text_chunk.h"
#include <stdbool.h>

typedef char *(*AnimationObjectGetter)(int objectID);

extern AnimationObjectGetter
    animation_object_linker[ANIMATION_OBJECT_TYPE_COUNT];

typedef enum
{
    CLASSIC_LEFT,
    CLASSIC_RIGHT,
    CLASSIC_UP,
    CLASSIC_DOWN, 
    ANIMATION_TYPE_COUNT
} AnimationType;

typedef void *(*AnimationUpdateFunction)(AnimationObject *);

typedef struct
{

    void *update_animation;
    char *text_chunk;   
    Position *pos;
    Position *previous_pos;

    int speed;
    TextDimension dimension;

} AnimationObject;

typedef struct
{
    AnimationObject *items;

    int count;
    int capacity;
} AnimationList;

typedef enum
{
    IN_BOUNDS,
    X_FAR_LEFT,
    X_FAR_RIGHT,
    Y_FAR_UP,
    Y_FAR_DOWN
} BoundsResult;

/*
 * Animation object types
 */
typedef enum
{
    FISH,
    SEAWEED,
    BUBBLE,
    ANIMATION_OBJECT_TYPE_COUNT
} AnimationObjectType;



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