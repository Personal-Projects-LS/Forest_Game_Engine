#pragma once

#include <cassert> //for debugging, will remove later

#include <iostream>
#include <fstream>

#include <array>
#include <string>
#include <unordered_map>

#include "Character.h"
#include "Headers/Engine/Utils/MathUtils.h"

class FontFileReader {
public:
    explicit FontFileReader(const char *filename);

    Character getChar(char id);

private:
    std::unordered_map<char, Character> fontInfo;
};
