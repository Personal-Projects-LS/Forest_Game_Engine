#include <Headers/Engine/Models/stb_image.h>

#include "Headers/Engine/ResourceContainers/stb_PointerContainer.h"

stb_PointerContainer::stb_PointerContainer(unsigned char *const image) noexcept : data(image) {}

const unsigned char *stb_PointerContainer::getData() const noexcept {
    return data;
}

stb_PointerContainer::~stb_PointerContainer() {
    stbi_image_free(data);
}
