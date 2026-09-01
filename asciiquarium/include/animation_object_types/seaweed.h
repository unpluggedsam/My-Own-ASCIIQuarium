#ifndef SEAWEED_H
#define SEAWEED_H

typedef enum
{
    SEAWEED_ONE,
    SEAWEED_TWO,
    SEAWEED_THREE,

    SEAWEED_TYPE_COUNT
} SeaweedType;

extern char *(*seaweed_type_linker[SEAWEED_TYPE_COUNT])(void);

char *get_seaweed(int seaweed_type);

char *seaweed_one(void);
char *seaweed_two(void);
char *seaweed_three(void);

AnimationObject create_randomized_seaweed(void);

#endif