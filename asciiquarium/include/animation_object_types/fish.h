typedef enum
{
    SMALL_FISH_ONE = 0,
    SMALL_FISH_TWO = 1,
    SMALL_FISH_THREE = 2,

    LARGE_FISH_ONE = 3,
    LARGE_FISH_TWO = 4,
    LARGE_FISH_THREE = 5,

    FISH_TYPE_COUNT

} FishType;

extern char *get_fish(int objectID);