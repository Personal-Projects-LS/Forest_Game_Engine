#pragma once

#include <glad/glad.h>

class TextureResourceContainer {
private:
    const unsigned int ID{};

public:
    TextureResourceContainer(const TextureResourceContainer&) = delete;
    TextureResourceContainer& operator=(const TextureResourceContainer&) = delete;

    explicit TextureResourceContainer(unsigned int IDPar) noexcept;

    [[nodiscard]] unsigned int getID() const noexcept;

    ~TextureResourceContainer() noexcept;
};
