#include <stdio.h>
#include "ASCIIQuarium.h"
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define OUTPUT_BUFFER_SIZE 10000

char output_buffer[OUTPUT_BUFFER_SIZE];
int output_buffer_position = 0;


int cursor_x = 0;
int cursor_y = 0;

int x;
int y;

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