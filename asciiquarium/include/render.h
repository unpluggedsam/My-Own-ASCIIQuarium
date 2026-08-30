#ifndef RENDER_H
#define RENDER_H

void add_text_to_render(char text[], Position *pos);

void buffer_write(const char *text);

void delete_text_from_render(Position *pos);

void set_cursor_on_render(Position *pos);

void render(void);

void synchronize_coordinates(void);

typedef struct {
    int x;
    int y;
} Position;

#endif