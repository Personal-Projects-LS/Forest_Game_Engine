#include "Headers/Engine/ResourceContainers/TextureResourceContainer.h"

TextureResourceContainer::TextureResourceContainer(const unsigned int IDPar) noexcept : ID(IDPar)
{}

[[nodiscard]] unsigned int TextureResourceContainer::getID() const noexcept {
    return ID;
}

TextureResourceContainer::~TextureResourceContainer() noexcept {
    glDeleteTextures(1, &ID);
}
