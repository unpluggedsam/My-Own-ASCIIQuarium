#include "ASCIIQuarium.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>




#define OUTPUT_BUFFER_SIZE 10000

struct timespec delay = {
    .tv_sec = 0,
    .tv_nsec = 100000000
};


char output_buffer[OUTPUT_BUFFER_SIZE];
int output_buffer_position = 0;


int cursor_x = 0;
int cursor_y = 0;

int x;
int y;


PeriodicTask periodic_tasks[10];
int periodic_task_count = 0;


void get_terminal_size(int *width, int *height)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    {
        // fallback if ioctl fails (e.g. output redirected to a file)
        *width = 80;
        *height = 24;
        return;
    }

    *width = ws.ws_col;
    *height = ws.ws_row;
}

void register_periodic_task(void (*task)(void), int interval_seconds) {
    periodic_tasks[periodic_task_count++] = (PeriodicTask){
        .task = task,
        .interval_seconds = interval_seconds,
        .last_run = time(NULL)
    };
}

void run_periodic_tasks(void) {
    time_t now = time(NULL);
    for (int i = 0; i < periodic_task_count; i++) {
        if (now - periodic_tasks[i].last_run >= periodic_tasks[i].interval_seconds) {
            periodic_tasks[i].task();
            periodic_tasks[i].last_run = now;
        }
    }
}

void add_text_to_render(char text[], int x, int y)
{
    set_cursor_on_render(x, y);

    for (int i = 0; text[i] != '\0'; i++) {

        if (text[i] == '\n') {
            y++;
            set_cursor_on_render(x, y);
        }
        else {
            char character[2] = { text[i], '\0' };
            buffer_write(character);
        }
    }
}

void buffer_write(const char *text)
{
    int length = strlen(text);

    if (output_buffer_position + length >= OUTPUT_BUFFER_SIZE) {
        return; // buffer is full
    }

    memcpy(
        output_buffer + output_buffer_position,
        text,
        length
    );

    output_buffer_position += length;
    output_buffer[output_buffer_position] = '\0';
}

void render_animation_stack(AnimationList *animation_stack) {
    while (1) {
        run_periodic_tasks();
        update_animation_stack_positions(animation_stack);
        update_animation_stack_buffer(animation_stack);
        render();
        nanosleep(&delay, NULL);
    }
}


void update_animation_stack_buffer(AnimationList *animation_stack)
{
    for (int i = 0; i < animation_stack->count;)
        {
            AnimationObject *object =
                &animation_stack->items[i];


            /*
             * Remove its previous rendering.
             */
            delete_text_chunk(
                object->text_chunk,
                &object->previous_pos
            );


            /*
             * Render at the new position.
             */
            if (
                print_text_chunk(
                    object->text_chunk,
                    &object->pos
                ) == PRINT_SUCCESS
            )
            {
                i++;
            }
            else
            {
                remove_animation_from_stack(
                    animation_stack,
                    i
                );
            }
    }
}




void delete_text_from_render(int x, int y) {
    add_text_to_render(" ", x, y);
}


void set_cursor_on_render(int cursor_x, int cursor_y)
{
    char cursor_command[32];

    int target_x = x + cursor_x;
    int target_y = y + cursor_y;

    snprintf(
        cursor_command,
        sizeof(cursor_command),
        "\033[%d;%dH",
        target_y,
        target_x
    );

    buffer_write(cursor_command);
}

void render(void)
{
    printf("%s", output_buffer);
    printf("\033[%d;1H", frame_y + 2);
    fflush(stdout);

    output_buffer_position = 0;
    output_buffer[0] = '\0';

}


   void synchronize_coordinates() {

    printf("\033[2J\033[H");
    printf("\033[?25l");

    struct termios old_terminal, new_terminal;

    tcgetattr(STDIN_FILENO, &old_terminal);
    new_terminal = old_terminal;
    new_terminal.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);

    printf("\033[6n");
    fflush(stdout);

    char buf[32];
    unsigned int i = 0;
    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') {
            i++;
            break;
        }
        i++;
    }
    buf[i] = '\0';

    tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);

    if (sscanf(buf, "\033[%d;%dR", &cursor_y, &cursor_x) == 2) {
        x = cursor_x;
        y = cursor_y;
    } else {
        x = 1;
        y = 1;
        cursor_x = 1;
        cursor_y = 1;
    }

   }