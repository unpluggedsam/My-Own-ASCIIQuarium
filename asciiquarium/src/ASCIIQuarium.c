#include <stdio.h>
#include <termios.h>
#include <unistd.h>

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
   
    create_animation_object(LARGE_FISH_ONE, CLASSIC_RIGHT, 1, 1, 11);
     
    create_animation_object(SMALL_FISH_THREE, CLASSIC_LEFT, 2, 3, 11);

   
}






