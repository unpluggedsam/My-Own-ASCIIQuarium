#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

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
    srand(time(NULL));
    synchronize_coordinates();
    build_frame(200, 50);
    run_animations();
}






