//
// Created by Kacper Skelnik on 15.12.2024.
//

#ifndef SIDE_H
#define SIDE_H

typedef enum ObjectSide {
    NONE  = 0,
    LEFT  = 1,
    RIGHT = 2,
} ObjectSide;

inline const char* toString(const ObjectSide side) {
    switch (side) {
        case NONE:
            return "";
        case LEFT:
            return "_left";
        case RIGHT:
            return "_right";
        default:
            return "[Unknown ObjectSide]";
    }
}

#endif // SIDE_H
