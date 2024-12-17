//
// Created by Kacper Skelnik on 15.12.2024.
//

#ifndef STATUS_H
#define STATUS_H

typedef enum ObjectStatus {
    DEATH = 0,
    HURT  = 1,
    IDLE  = 2,
    FALL  = 3,
    JUMP  = 4,
    LAND  = 5,
    TURN  = 6,
    SQUAT = 8,
    WALK  = 9,
} ObjectStatus;

inline const char* toString(const ObjectStatus status) {
    switch (status) {
        case DEATH:
            return "death";
        case HURT:
            return "hurt";
        case IDLE:
            return "idle";
        case FALL:
            return "fall";
        case JUMP:
            return "jump";
        case LAND:
            return "land";
        case TURN:
            return "turn";
        case SQUAT:
            return "squat";
        case WALK:
            return "walk";
        default:
            return "[Unknown ObjectStatus]";
    }
}

#endif // STATUS_H
