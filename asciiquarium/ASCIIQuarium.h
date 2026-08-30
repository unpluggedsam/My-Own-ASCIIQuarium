#ifndef ASCIIQUARIUM_H
#define ASCIIQUARIUM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* =========================
   Constants
   ========================= */

extern int frame_x;
extern int frame_y;


/* =========================
   Text chunks
   ========================= */

typedef enum {

    SMALL_FISH_ONE = 0,
    SMALL_FISH_TWO = 1,
    SMALL_FISH_THREE = 2,
    LARGE_FISH_ONE = 3,
    LARGE_FISH_TWO = 4,
    LARGE_FISH_THREE = 5,
    TEXT_CHUNK_COUNT

} TextChunkType;


typedef struct {
    int height;
    int width;
} TextDimension;


/* =========================
   Animations
   ========================= */

typedef enum {

    CLASSIC_LEFT = 0,
    CLASSIC_RIGHT = 1,
    CLASSIC_UP = 2,
    CLASSIC_DOWN = 3,

    ANIMATION_TYPE_COUNT

} AnimationType;


typedef struct {
    TextChunkType text_chunk_type;
    AnimationType animation_type;
    TextDimension dimension;
    bool is_flipped;
    int previous_x;
    int previous_y;
    int speed;
    int x;
    int y;
} AnimationObject;


typedef struct {
    AnimationObject *items;
    int count;
    int capacity;
} AnimationList;


/* =========================
   Text chunk functions
   ========================= */

extern char *(*text_chunk_functions[TEXT_CHUNK_COUNT])(void);

typedef enum {
    IN_BOUNDS,
    X_FAR_RIGHT,
    X_FAR_LEFT,
    Y_FAR_UP,
    Y_FAR_DOWN
} BoundsResult;

typedef enum {
    PRINT_SUCCESS,
    PRINT_OUT_OF_BOUNDS
} PrintResult;

TextDimension calculate_text_chunk_length_and_height(
    TextChunkType text_chunk
);

char *small_fish_one(void);
char *small_fish_two(void);
char *small_fish_three(void);

char *large_fish_one(void);
char *large_fish_two(void);
char *large_fish_three(void);

char *get_text_chunk_text(TextChunkType text_chunk);
char *get_flipped_text_chunk_text(TextChunkType text_chunk);

char *flip_text_chunk(const char *text);

char flip_character(char c);

PrintResult print_text_chunk(TextChunkType text_chunk, bool is_flipped, int x, int y);

void delete_text_chunk(
    TextChunkType text_chunk,
    int x,
    int y
);

bool check_if_text_chunk_in_bounds(TextDimension dimension, int x, int y);

BoundsResult check_out_of_bounds_direction(TextDimension dimension, int x, int y);


/* =========================
   Animation functions
   ========================= */

extern void (*animation_function[ANIMATION_TYPE_COUNT])(
    AnimationObject *
);

void create_animation_object(
    TextChunkType text_chunk_type,
    AnimationType animation_type,
    int speed,
    int x,
    int y
);

void add_animation_object_to_stack(
    AnimationObject animation_object
);

void remove_animation_from_stack(
    AnimationList *list,
    int index
);

void run_animations();

void classic_animate_up(
    AnimationObject *animation_object
);

void classic_animate_down(
    AnimationObject *animation_object
);

void classic_animate_right(
    AnimationObject *animation_object
);

void classic_animate_left(
    AnimationObject *animation_object
);

void correct_animation_object_bounds_error(
    AnimationObject *animation_object
);


/* =========================
   Rendering
   ========================= */

void build_frame(int width, int height);

void add_text_to_render(
    char text[],
    int x,
    int y
);

void delete_text_from_render(
    int x,
    int y
);

void set_cursor_on_render(
    int x,
    int y
);

void buffer_write(
    const char *text
);

void render(void);


/* =========================
   Terminal
   ========================= */

void synchronize_coordinates(void);


/* =========================
   Program
   ========================= */

void run_program(void);


#endif