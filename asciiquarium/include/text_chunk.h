#ifndef TEXT_CHUNK_H
#define TEXT_CHUNK_H


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
    char text_chunk
);

PrintResult print_text_chunk(
    char text_chunk,
    Position *pos
);  

void delete_text_chunk(
    char text_chunk,
    Position *pos
);

typedef struct {
    int x;
    int y;
} Position;


#endif