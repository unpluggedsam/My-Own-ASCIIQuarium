#ifndef ANIMATION_OBJECT_H
#define ANIMATION_OBJECT_H

typedef enum
{
    FISH,
    SEAWEED,
    BUBBLE,

    ANIMATION_OBJECT_TYPE_COUNT
} AnimationObjectType;


typedef char *(*AnimationObjectGetter)(int objectID);

#endif