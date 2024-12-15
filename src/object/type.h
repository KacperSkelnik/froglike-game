//
// Created by Kacper Skelnik on 15.12.2024.
//

#ifndef TYPE_H
#define TYPE_H

typedef enum ObjectType {
    HERO = 0,
    FROG = 1,
} ObjectType;

inline const char* toString(const ObjectType type) {
    switch (type) {
        case HERO:
            return "hero";
        case FROG:
            return "frog";
        default:
            return "[Unknown ObjectType]";
    }
}

#endif // TYPE_H
