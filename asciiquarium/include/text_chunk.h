#ifndef TEXT_CHUNK_H
#define TEXT_CHUNK_H


typedef enum
{
    SMALL_FISH_ONE,
    SMALL_FISH_TWO,
    SMALL_FISH_THREE,

    LARGE_FISH_ONE,
    LARGE_FISH_TWO,
    LARGE_FISH_THREE,

    TEXT_CHUNK_COUNT
} TextChunkType;

typedef enum
{
    PRINT_SUCCESS,
    PRINT_OUT_OF_BOUNDS
} PrintResult;

typedef struct
{
    int width;
    int height;
} TextDimension;


TextDimension calculate_text_chunk_length_and_height(
    TextChunkType text_chunk
);

void print_text_chunk(
    TextChunkType text_chunk,
    int x,
    int y
);

void delete_text_chunk(
    TextChunkType text_chunk,
    int x,
    int y
);

#endif