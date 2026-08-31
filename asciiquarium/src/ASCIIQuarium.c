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
    
    // Position pos1 = { .x = 1, .y = 11 };
    // create_animation_object(FISH, 3, CLASSIC_RIGHT, 2, &pos1);

    
   
}






