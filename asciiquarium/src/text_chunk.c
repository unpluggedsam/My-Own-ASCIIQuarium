#include "ASCIIQuarium.h"

#include <string.h>
#include <stdlib.h>


TextDimension calculate_text_chunk_length_and_height(
    const char *text_chunk
)
{
    int highest_width = 0;
    int current_width = 0;
    int height = 1;


    for (int i = 0; text_chunk[i] != '\0'; i++)
    {
        if (text_chunk[i] == '\n')
        {
            if (current_width > highest_width)
            {
                highest_width = current_width;
            }

            current_width = 0;
            height++;
        }
        else
        {
            current_width++;
        }
    }


    if (current_width > highest_width)
    {
        highest_width = current_width;
    }


    TextDimension result = {
        .width = highest_width,
        .height = height
    };


    return result;
}


PrintResult print_text_chunk(
    const char *text_chunk,
    Position *pos
)
{
    TextDimension dimension =
        calculate_text_chunk_length_and_height(
            text_chunk
        );


    if (
        check_if_text_chunk_in_bounds(
            dimension,
            pos
        )
    )
    {
        add_text_to_render(
            (char *)text_chunk,
            pos->x,
            pos->y
        );

        return PRINT_SUCCESS;
    }


    return PRINT_OUT_OF_BOUNDS;
}


void delete_text_chunk(
    const char *text_chunk,
    Position *origin
)
{
    TextDimension dimension =
        calculate_text_chunk_length_and_height(
            text_chunk
        );


    for (int x = 0; x < dimension.width; x++)
    {
        for (int y = 0; y < dimension.height; y++)
        {
            delete_text_from_render(
                origin->x + x,
                origin->y + y
            );
        }
    }
}


bool check_if_text_chunk_in_bounds(
    TextDimension dimension,
    Position *pos
)
{
    return check_out_of_bounds_direction(
        dimension,
        pos
    ) == IN_BOUNDS;
}


BoundsResult check_out_of_bounds_direction(
    TextDimension dimension,
    Position *pos
)
{
    if (pos->x <= 1)
    {
        return X_FAR_LEFT;
    }

    if (pos->x + dimension.width >= frame_x - 1)
    {
        return X_FAR_RIGHT;
    }

    if (pos->y + dimension.height >= frame_y - 5)
    {
        return Y_FAR_DOWN;
    }

    if (pos->y <= 5)
    {
        return Y_FAR_UP;
    }

    return IN_BOUNDS;
}


char *flip_text_chunk(
    const char *text
)
{
    int length = strlen(text);

    int width = 0;
    int line_width = 0;


    for (int i = 0; i <= length; i++)
    {
        if (
            text[i] == '\n' ||
            text[i] == '\0'
        )
        {
            if (line_width > width)
            {
                width = line_width;
            }

            line_width = 0;
        }
        else
        {
            line_width++;
        }
    }


    int height = 1;

    for (int i = 0; i < length; i++)
    {
        if (text[i] == '\n')
        {
            height++;
        }
    }


    char *flipped =
        malloc((width + 1) * height + 1);


    if (flipped == NULL)
    {
        return NULL;
    }


    int output = 0;
    int line_start = 0;


    for (int y = 0; y < height; y++)
    {
        int line_end = line_start;


        while (
            text[line_end] != '\n' &&
            text[line_end] != '\0'
        )
        {
            line_end++;
        }


        int current_line_width =
            line_end - line_start;


        for (
            int x = width - 1;
            x >= 0;
            x--
        )
        {
            if (x < current_line_width)
            {
                flipped[output++] =
                    flip_character(
                        text[line_start + x]
                    );
            }
            else
            {
                flipped[output++] = ' ';
            }
        }


        while (
            output > 0 &&
            flipped[output - 1] == ' '
        )
        {
            output--;
        }


        if (y < height - 1)
        {
            flipped[output++] = '\n';
        }


        line_start = line_end;


        if (text[line_start] == '\n')
        {
            line_start++;
        }
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


char *get_text_chunk(
    AnimationObjectType animation_object_type,
    int objectID
)
{
    return animation_object_linker[
        animation_object_type
    ](objectID);
}


char *get_flipped_text_chunk_text(
    AnimationObjectType animation_object_type,
    int objectID
)
{
    char *text =
        get_text_chunk(
            animation_object_type,
            objectID
        );


    return flip_text_chunk(text);
}