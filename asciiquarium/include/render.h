#ifndef RENDER_H
#define RENDER_H

typedef struct {
    void (*task)(void);
    int interval_seconds;
    time_t last_run;
} PeriodicTask;

void register_periodic_task(void (*task)(void), int interval_seconds);
void run_periodic_tasks(void);
void get_terminal_size(int *width, int *height);
int amount_of_object_type_in_animation_stack(AnimationList *animation_stack, AnimationObjectType animation_object_type);

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