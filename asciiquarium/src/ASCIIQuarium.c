#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "ASCIIQuarium.h"
#include "animation.h"
#include "render.h"
#include "text_chunk.h"


int main(void)
{
    run_program();
    return 0;
}

void run_program(void) {

    synchronize_coordinates();
    build_frame(200, 20);
    render();
    Position pos1 = { .x = 5, .y = 11 };
    Position pos2 = { .x = 10, .y = 1 };
    create_animation_object(FISH, SMALL_FISH_TWO, CLASSIC_RIGHT, 1, &pos1);
    //create_animation_object(SEAWEED, 4, CLASSIC_LEFT, 1, &pos2);

    run_animations();
    
   
}






