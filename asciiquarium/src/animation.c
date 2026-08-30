
#define _POSIX_C_SOURCE 199309L
#include "ASCIIQuarium.h"
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

struct timespec delay = {
    .tv_sec = 0,
    .tv_nsec = 100000000};

int frame_x;
int frame_y;

AnimationList animation_stack = {
    .items = NULL,
    .count = 0,
    .capacity = 0};

void build_frame(int width, int height)
{

    frame_y = height;
    frame_x = width;

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

void (*animation_function[ANIMATION_TYPE_COUNT])(AnimationObject *) = {

    [CLASSIC_LEFT] = classic_animate_left,
    [CLASSIC_RIGHT] = classic_animate_right,
    [CLASSIC_UP] = classic_animate_up,
    [CLASSIC_DOWN] = classic_animate_down};

void run_animations(AnimationList *animation_stack)
{

    while (animation_stack->count > 0)
    {

        for (int i = 0; i < animation_stack->count;)
        {

            AnimationObject *object =
            &animation_stack->items[i];

  
            object->previous_pos->x = object->pos->x;
            object->previous_pos->y = object->pos->y;

            animation_function[object->animation_type](object);
            delete_text_chunk(object->text_chunk_type, object->previous_x, object->previous_y);

            if (print_text_chunk(object->text_chunk_type, object->is_flipped, object->x, object->y) == PRINT_SUCCESS)
            {
                i++;
            }
            else
            {
                remove_animation_from_stack(animation_stack, i);
            }
        }

        render();
        nanosleep(&delay, NULL);
    }
}

void add_randomized_fish_animations(AnimationList *animation_stack, int amount_of_fish) {
    // for(int i = 0; i < amount_of_fish; i++) {
    //     int type_of_fish = rand() % TEXT_CHUNK_COUNT;
    // }
}


void add_animation_object_to_stack(AnimationObject animation_object)
{
    if (animation_stack.count == animation_stack.capacity)
    {

        int new_capacity = animation_stack.capacity == 0
                               ? 4
                               : animation_stack.capacity * 2;

        animation_stack.items = realloc(
            animation_stack.items,
            new_capacity * sizeof(AnimationObject));

        animation_stack.capacity = new_capacity;
    }

    animation_stack.items[animation_stack.count] = animation_object;
    animation_stack.count++;
}

void create_animation_object(AnimationObjectType animation_object_type, int animation_object_type_ID, AnimationType animation_type, int speed, Position *pos)
{
    AnimationObject animation_object;
    animation_object.pos = &pos;
    animation_object.update_animation = get_animation_update_function(animation_type, &animation_object);
    Position previous_pos = { .x = -1, .y = -1 };
    animation_object.previous_pos = &previous_pos;
    animation_object.speed = speed;

    animation_object.dimension = calculate_text_chunk_length_and_height(animation_object.text_chunk);

    animation_object.text_chunk = animation_type == CLASSIC_LEFT
                   ? get_flipped_text_chunk_text(animation_object_type, animation_object_type_ID)
                   : get_text_chunk_text(animation_object_type, animation_object_type_ID);

    correct_animation_object_bounds_error(&animation_object);
    add_animation_object_to_stack(animation_object);
}

void correct_animation_object_bounds_error(AnimationObject *animation_object)
{

    PrintResult p_result = check_out_of_bounds_direction(animation_object);

    while (p_result != IN_BOUNDS)
    {
        if (p_result == X_FAR_LEFT)
        {
            animation_object->pos->x++;
        }
        if (p_result == X_FAR_RIGHT)
        {
            animation_object->pos->x--;
        }
        if (p_result == Y_FAR_UP)
        {
            animation_object->pos->y--;
        }
        if (p_result == Y_FAR_DOWN)
        {
            animation_object->pos->y++;
        }
        p_result = check_out_of_bounds_direction(animation_object->dimension, animation_object->pos->x, animation_object->pos->y);
    }
}

void remove_animation_from_stack(AnimationList *list, int index)
{
    list->items[index] =
        list->items[list->count - 1];

    list->count--;
}

 AnimationObjectGetter animation_object_linker[ANIMATION_OBJECT_TYPE_COUNT] = {
    [FISH] = get_fish,
    [SEAWEED] = NULL,
    [BUBBLE] = NULL
};



void *get_animation_update_function(AnimationType animation_type, AnimationObject *animation_object)
{
    return animation_update_functions[animation_type](animation_object);
}

AnimationUpdateFunction animation_update_functions[ANIMATION_TYPE_COUNT] = {
    [CLASSIC_UP]    = classic_animate_up,
    [CLASSIC_DOWN]  = classic_animate_down,
    [CLASSIC_RIGHT] = classic_animate_right,
    [CLASSIC_LEFT]  = classic_animate_left
};


void classic_animate_up(AnimationObject *animation_object)
{

    animation_object->pos->y = animation_object->pos->y - animation_object->speed;
}

void classic_animate_down(AnimationObject *animation_object)
{
    animation_object->pos->y = animation_object->pos->y + animation_object->speed;
}

void classic_animate_right(AnimationObject *animation_object)
{
    animation_object->pos->x = animation_object->pos->x + animation_object->speed;
}

void classic_animate_left(AnimationObject *animation_object)
{
    animation_object->pos->x = animation_object->pos->x - animation_object->speed;
}
