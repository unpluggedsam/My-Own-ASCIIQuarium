#define _POSIX_C_SOURCE 199309L

#include "ASCIIQuarium.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>




int frame_x;
int frame_y;


AnimationList animation_stack = {
    .items = NULL,
    .count = 0,
    .capacity = 0
};


void build_frame(int width, int height)
{
    frame_x = width;
    frame_y = height;

    for (int x = 1; x <= frame_x - 1; x++)
    {
        add_text_to_render("-", x, 0);
        add_text_to_render("-", x, frame_y);
    }

    for (int y = 0; y <= frame_y; y++)
    {
        add_text_to_render("|", 0, y);
        add_text_to_render("|", frame_x, y);
    }

    add_text_to_render("+", 0, 0);
    add_text_to_render("+", frame_x, 0);
    add_text_to_render("+", 0, frame_y);
    add_text_to_render("+", frame_x, frame_y);
}

void run_animations() {
    register_periodic_task(run_fishies, 5); 
    render_animation_stack(&animation_stack);
}


AnimationUpdateFunction animation_update_functions[
    ANIMATION_TYPE_COUNT
] = {
    [CLASSIC_LEFT]  = classic_animate_left,
    [CLASSIC_RIGHT] = classic_animate_right,
    [CLASSIC_UP]    = classic_animate_up,
    [CLASSIC_DOWN]  = classic_animate_down
};


AnimationUpdateFunction get_animation_update_function(
    AnimationType animation_type
)
{
    return animation_update_functions[animation_type];
}

void run_fishies() {
    add_animation_object_to_stack(create_randomized_fish());
}


void update_animation_stack_positions(AnimationList *animation_stack)
{
    for (int i = 0; i < animation_stack->count; i++)
    {
        AnimationObject *object =
            &animation_stack->items[i];


            /*
             * Save current position before updating.
             */
            object->previous_pos = object->pos;


            /*
             * Update the object's position.
             */
            object->update_animation(object);

    }
}


void add_animation_object_to_stack(
    AnimationObject animation_object
)
{
    if (animation_stack.count == animation_stack.capacity)
    {
        int new_capacity =
            animation_stack.capacity == 0
                ? 4
                : animation_stack.capacity * 2;

        AnimationObject *new_items = realloc(
            animation_stack.items,
            new_capacity * sizeof(AnimationObject)
        );

        if (new_items == NULL)
        {
            return;
        }

        animation_stack.items = new_items;
        animation_stack.capacity = new_capacity;
    }

    animation_stack.items[
        animation_stack.count
    ] = animation_object;

    animation_stack.count++;
}


AnimationObject create_animation_object(
    AnimationObjectType animation_object_type,
    int animation_object_type_ID,
    AnimationType animation_type,
    int speed,
    Position *pos
)
{
    AnimationObject animation_object;


    /*
     * Copy the position into the object.
     *
     * AnimationObject owns its position.
     */
    animation_object.pos = *pos;

    animation_object.previous_pos = *pos;


    animation_object.speed = speed;


    /*
     * Get the correct update function.
     */
    animation_object.update_animation =
        get_animation_update_function(
            animation_type
        );


    /*
     * Get the object's text.
     */
    if (animation_type == CLASSIC_LEFT)
    {
        animation_object.text_chunk =
            get_flipped_text_chunk_text(
                animation_object_type,
                animation_object_type_ID
            );
    }
    else
    {
        animation_object.text_chunk =
            get_text_chunk(
                animation_object_type,
                animation_object_type_ID
            );
    }


    /*
     * Calculate dimensions AFTER getting the text.
     */
    animation_object.dimension =
        calculate_text_chunk_length_and_height(
            animation_object.text_chunk
        );


    /*
     * Make sure it starts inside the frame.
     */
    correct_animation_object_bounds_error(
        &animation_object
    );

    return animation_object;
}


void correct_animation_object_bounds_error(
    AnimationObject *animation_object
)
{
    BoundsResult p_result =
        check_out_of_bounds_direction(
            animation_object->dimension,
            &animation_object->pos
        );


    while (p_result != IN_BOUNDS)
    {
        if (p_result == X_FAR_LEFT)
        {
            animation_object->pos.x++;
        }

        else if (p_result == X_FAR_RIGHT)
        {
            animation_object->pos.x--;
        }

        else if (p_result == Y_FAR_UP)
        {
            animation_object->pos.y++;
        }

        else if (p_result == Y_FAR_DOWN)
        {
            animation_object->pos.y--;
        }


        p_result =
            check_out_of_bounds_direction(
                animation_object->dimension,
                &animation_object->pos
            );
    }
}


void remove_animation_from_stack(
    AnimationList *list,
    int index
)
{
    list->items[index] =
        list->items[list->count - 1];

    list->count--;
}


AnimationObjectGetter animation_object_linker[
    ANIMATION_OBJECT_TYPE_COUNT
] = {
    [FISH]    = get_fish,
    [SEAWEED] = NULL,
    [BUBBLE]  = NULL
};


void classic_animate_up(
    AnimationObject *animation_object
)
{
    animation_object->pos.y -=
        animation_object->speed;
}


void classic_animate_down(
    AnimationObject *animation_object
)
{
    animation_object->pos.y +=
        animation_object->speed;
}


void classic_animate_right(
    AnimationObject *animation_object
)
{
    animation_object->pos.x +=
        animation_object->speed;
}


void classic_animate_left(
    AnimationObject *animation_object
)
{
    animation_object->pos.x -=
        animation_object->speed;
}