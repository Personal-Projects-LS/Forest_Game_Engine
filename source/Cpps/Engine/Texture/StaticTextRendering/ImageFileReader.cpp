#include <Headers/Engine/Models/stb_image.h>

#include "Headers/Engine/Texture/StaticTextRendering/ImageFileReader.h"

ImageFileReader::ImageFileReader(const char *filename) {
    int type{};
    if (std::regex_match(filename, std::regex("(.+)(\\.png)"))) {
        type = PNG;
    }
    else if (std::regex_match(filename, std::regex("(.+)(\\.jpg)"))) {
        type = JPG;
    }
    else {
        std::cerr << "File type not supported!. Please supply a JPG or PNG!" << std::endl;
        throw;
    }

    auto desiredChannels = (type == PNG) ? STBI_rgb_alpha : STBI_rgb;
    data = stbi_load(filename, &width, &height, &nrchannels, desiredChannels);
}

int ImageFileReader::getRawBufferWidth() const {
    return width;
}

int ImageFileReader::getRawBufferHeight() const {
    return height;
}

int ImageFileReader::getNR_Channels() const {
    return nrchannels;
}

unsigned char* ImageFileReader::getRawDataBuffer() const {
    return data;
}

ImageFileReader::~ImageFileReader() {
    stbi_image_free(data); //deletes internal heap buffer to stop memory leaking
}
