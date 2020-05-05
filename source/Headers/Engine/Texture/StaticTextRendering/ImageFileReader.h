#pragma once

#include <regex>
#include <glad/glad.h>
#include <iostream>
#include <string>

class ImageFileReader {
public:
    explicit ImageFileReader(const char* filename);

    [[nodiscard]] int getRawBufferWidth() const;
    [[nodiscard]] int getRawBufferHeight() const;
    [[nodiscard]] int getNR_Channels() const;
    [[nodiscard]] unsigned char* getRawDataBuffer() const;

    ~ImageFileReader();

private:
    int width{}, height{}, nrchannels{};
    unsigned char *data = nullptr;

    static constexpr int PNG = 0;
    static constexpr int JPG = 1;
};
