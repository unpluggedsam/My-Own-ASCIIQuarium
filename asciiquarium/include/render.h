#ifndef RENDER_H
#define RENDER_H

void add_text_to_render(
    char text[],
    int x,
    int y
);

void buffer_write(
    const char *text
);

void delete_text_from_render(
    int x,
    int y
);

void set_cursor_on_render(
    int cursor_x,
    int cursor_y
);

void render(void);

void synchronize_coordinates(void);

void update_animation_stack_buffer(AnimationList *animation_stack);

void render_animation_stack(AnimationList *animation_stack);

#endif