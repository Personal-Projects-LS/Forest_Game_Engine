#pragma once

#include <glad/glad.h>

class QuadResourceContainer {
private:
    const unsigned int VAO{}, VBO{}, TBO{}, IBO{};

public:
    QuadResourceContainer(const QuadResourceContainer&) = delete;
    QuadResourceContainer& operator=(const QuadResourceContainer&) = delete;

    QuadResourceContainer(unsigned int VAOPar, unsigned int VBOPar, unsigned int TBOPar, unsigned int IBOPar) noexcept;

    [[nodiscard]] unsigned int getVAO() const noexcept;

    ~QuadResourceContainer() noexcept;
};
