#include "ASCIIQuarium.h"


char *(*fish_type_linker[FISH_TYPE_COUNT])(void) = {
    [SMALL_FISH_ONE] = small_fish_one,
    [SMALL_FISH_TWO] = small_fish_two,
    [SMALL_FISH_THREE] = small_fish_three,
    [LARGE_FISH_ONE] = large_fish_one,
    [LARGE_FISH_TWO] = large_fish_two,
    [LARGE_FISH_THREE] = large_fish_three
};

char *get_fish(FishType fish_type) {
    return fish_type_linker[fish_type]();
}
    
    
    char *small_fish_one(void)
{
    return "><(((o>";
}

char *small_fish_two(void)
{
    return "><((o))>";
}

char *small_fish_three(void)
{
    return "><((o)))>";
}

char *large_fish_one(void)
{
    return "      __\n"
           "  ___/  \\__\n"
           " /         _\\\n"
           "<          _)\n"
           " \\________/\n";
}

char *large_fish_two(void)
{
    return "       ___\n"
           "  ____/   \\___\n"
           " /           _\\\n"
           "<           _)\n"
           " \\_________/\n";
}

char *large_fish_three(void)
{
    return "        ___\n"
           "   ____/   \\____\n"
           "  /             _\\\n"
           " <       o      _)\n"
           "  \\____________/\n";
}

