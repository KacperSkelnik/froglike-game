//
// Created by Kacper Skelnik on 02.01.2025.
//

#ifndef LAYERTYPE_H
#define LAYERTYPE_H
#include <string>

typedef enum LayerType {
    UNKNOWN    = 0,
    BACKGROUND = 1,
    GROUND     = 2,
} LayerType;

inline LayerType fromString(std::string str) {
    std::ranges::transform(str, str.begin(), [](unsigned char c) {
        return std::toupper(c);
    });

    if (str == "BACKGROUND") return BACKGROUND;
    if (str == "GROUND") return GROUND;
    return UNKNOWN;
}

#endif // LAYERTYPE_H
