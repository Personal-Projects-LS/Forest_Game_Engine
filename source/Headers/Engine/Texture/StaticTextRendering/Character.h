#pragma once

#include <array>

struct Character { //I put it all in the constructor because their are no side effects in this struct
    Character() = default;

    explicit Character(const std::array<int, 8> &numbersInLine)
    : id(static_cast<char>(numbersInLine[0])),
            x(numbersInLine[1]),
            y(numbersInLine[2]),
            width(numbersInLine[3]),
            height(numbersInLine[4]),
            xOffset(numbersInLine[5]),
            yOffset(numbersInLine[6]),
            xAdvance(numbersInLine[7])
    {} //@todo try to make this less verbose

    char id;

    int x;
    int y;
    int width;
    int height;
    int xOffset;
    int yOffset;
    int xAdvance;
};
