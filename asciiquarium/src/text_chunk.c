#include "ASCIIQuarium.h"
#include <string.h>
#include <stdbool.h>

extern char *(*text_chunk_functions[TEXT_CHUNK_COUNT])(void);

/* This function calculates the width and height of a textchunk. It tracks
the height by counting the amount of newline escape characters it uses,
and finds the width by calculating the longest distance between newline
escape characters.*/

TextDimension calculate_text_chunk_length_and_height(char text_chunk)
{

    char *text = get_text_chunk_text(text_chunk);

    int highest_width = 0;
    int current_width = 0;
    int height = 0;

    for (int i = 0; get_text_chunk_text(text_chunk)[i] != '\0'; i++)
    {
        if (text[i] == '\n')
        {
            height++;
            if (current_width > highest_width)
            {
                highest_width = current_width;
            }
            current_width = 0;
        } else {
            current_width++;
        }
    }

    if (current_width > highest_width)
        highest_width = current_width;

    TextDimension result;
    result.height = height;
    result.width = highest_width;
    return result;
}

PrintResult print_text_chunk(char text_chunk, bool is_flipped, Position *pos)
{
    if (check_if_text_chunk_in_bounds(calculate_text_chunk_length_and_height(text_chunk), pos->x, pos->y))
    {
        char *text = is_flipped
                   ? get_flipped_text_chunk_text(text_chunk)
                   : get_text_chunk_text(text_chunk);

        add_text_to_render(text, pos->x, pos->y);
        return PRINT_SUCCESS;
    }
    else
    {
        return PRINT_OUT_OF_BOUNDS;
    }
}

void delete_text_chunk(char text_chunk, Position *origin)
{
    TextDimension text_dimensions = calculate_text_chunk_length_and_height(text_chunk);
    for (int x = 0; x <= text_dimensions.width; x++)
    {
        for (int y = 0; y <= text_dimensions.height; y++)
        {
            delete_text_from_render(origin->x + x, origin->y + y);
        }
    }
}

bool check_if_text_chunk_in_bounds(TextDimension dimension, Position *pos)
{
    return check_out_of_bounds_direction(dimension, pos) == IN_BOUNDS ? true : false;
}

BoundsResult check_out_of_bounds_direction(TextDimension dimension, Position *pos)
{

    if (pos->x <= 1)
    {
        return X_FAR_LEFT;
    }
    else if (pos->x + dimension.width >= frame_x - 1)
    {
        return X_FAR_RIGHT;
    }

    else if (pos->y + dimension.height >= frame_y - 1)
    {
        return Y_FAR_DOWN;
    }

    else if (pos->y <= 1)
    {
        return Y_FAR_UP;
    }
    else
    {
        return IN_BOUNDS;
    }
}

char *flip_text_chunk(const char *text)
{
    int length = strlen(text);

    // Find the widest line.
    int width = 0;
    int line_width = 0;

    for (int i = 0; i <= length; i++)
    {
        if (text[i] == '\n' || text[i] == '\0')
        {
            if (line_width > width)
                width = line_width;

            line_width = 0;
        }
        else
        {
            line_width++;
        }
    }

    // Count lines.
    int height = 1;

    for (int i = 0; i < length; i++)
    {
        if (text[i] == '\n')
            height++;
    }

    // Every line gets width characters plus a newline.
    char *flipped = malloc((width + 1) * height + 1);

    if (flipped == NULL)
        return NULL;

    int output = 0;
    int line_start = 0;

    for (int y = 0; y < height; y++)
    {
        // Find end of this line.
        int line_end = line_start;

        while (text[line_end] != '\n' &&
               text[line_end] != '\0')
        {
            line_end++;
        }

        line_width = line_end - line_start;

        /*
         * Read the line from right to left.
         *
         * Characters outside the line are treated as spaces.
         */
        for (int x = width - 1; x >= 0; x--)
        {
            if (x < line_width)
                flipped[output++] =
                    flip_character(text[line_start + x]);
            else
                flipped[output++] = ' ';
        }

        // Remove trailing spaces from the flipped line.
        while (output > 0 && flipped[output - 1] == ' ')
            output--;

        if (y < height - 1)
            flipped[output++] = '\n';

        line_start = line_end;

        if (text[line_start] == '\n')
            line_start++;
    }

    flipped[output] = '\0';

    return flipped;
}

char flip_character(char c)
{
    switch (c)
    {
        case '/': return '\\';
        case '\\': return '/';

        case '<': return '>';
        case '>': return '<';

        case '(': return ')';
        case ')': return '(';

        case '[': return ']';
        case ']': return '[';

        case '{': return '}';
        case '}': return '{';

        default: return c;
    }
}

char *get_text_chunk_text(TextChunkType text_chunk)
{
    return text_chunk_functions[text_chunk]();
}

char *get_flipped_text_chunk_text(TextChunkType text_chunk)
{
    return flip_text_chunk(get_text_chunk_text(text_chunk));
}

