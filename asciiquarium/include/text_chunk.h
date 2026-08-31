#ifndef TEXT_CHUNK_H
#define TEXT_CHUNK_H

#include <stdbool.h>
#include "animation_object.h"

typedef struct
{
    int x;
    int y;
} Position;

typedef struct
{
    int width;
    int height;
} TextDimension;

typedef enum
{
    PRINT_SUCCESS,
    PRINT_OUT_OF_BOUNDS
} PrintResult;

typedef enum
{
    IN_BOUNDS,
    X_FAR_LEFT,
    X_FAR_RIGHT,
    Y_FAR_UP,
    Y_FAR_DOWN
} BoundsResult;

TextDimension calculate_text_chunk_length_and_height(const char *text_chunk);

PrintResult print_text_chunk(
    const char *text_chunk,
    Position *pos
);

void delete_text_chunk(
    const char *text_chunk,
    Position *pos
);

bool check_if_text_chunk_in_bounds(
    TextDimension dimension,
    Position *pos
);

BoundsResult check_out_of_bounds_direction(
    TextDimension dimension,
    Position *pos
);

char *flip_text_chunk(const char *text);

char flip_character(char c);

char *get_text_chunk(
    AnimationObjectType animation_object_type,
    int objectID
);

char *get_flipped_text_chunk_text(
    AnimationObjectType animation_object_type,
    int objectID
);

#endif