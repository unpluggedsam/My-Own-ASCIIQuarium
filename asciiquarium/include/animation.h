#ifndef ANIMATION_H
#define ANIMATION_H

#include "text_chunk.h"
#include "animation_object.h"

typedef enum
{
    CLASSIC_LEFT,
    CLASSIC_RIGHT,
    CLASSIC_UP,
    CLASSIC_DOWN,

    ANIMATION_TYPE_COUNT
} AnimationType;

extern int frame_x;
extern int frame_y;

/*
 * AnimationObject is declared here so other types can
 * refer to AnimationObject * before the full struct exists.
 */
typedef struct AnimationObject AnimationObject;


/*
 * Function pointer for updating an animation object.
 */
typedef void (*AnimationUpdateFunction)(AnimationObject *);

extern AnimationObjectGetter
    animation_object_linker[ANIMATION_OBJECT_TYPE_COUNT];


/*
 * The actual AnimationObject.
 */
struct AnimationObject
{
    AnimationUpdateFunction update_animation;

    char *text_chunk;

    Position pos;
    Position previous_pos;

    int speed;

    TextDimension dimension;
};


/*
 * Animation stack.
 */
typedef struct
{
    AnimationObject *items;

    int count;
    int capacity;

} AnimationList;


/*
 * Animation update functions.
 */
void classic_animate_left(AnimationObject *animation_object);
void classic_animate_right(AnimationObject *animation_object);
void classic_animate_up(AnimationObject *animation_object);
void classic_animate_down(AnimationObject *animation_object);

void build_frame(int width, int height);
void update_animation_stack_positions(AnimationList *animation_stack);

/*
 * Function-pointer lookup table.
 */
extern AnimationUpdateFunction
animation_update_functions[ANIMATION_TYPE_COUNT];


/*
 * Returns the appropriate update function.
 */
AnimationUpdateFunction
get_animation_update_function(AnimationType animation_type);


/*
 * Animation stack functions.
 */
void add_animation_object_to_stack(AnimationObject animation_object);

void remove_animation_from_stack(
    AnimationList *list,
    int index
);

void run_animations(void);

void create_animation_object(
    AnimationObjectType animation_object_type,
    int animation_object_type_ID,
    AnimationType animation_type,
    int speed,
    Position *pos
);

void correct_animation_object_bounds_error(
    AnimationObject *animation_object
);

#endif