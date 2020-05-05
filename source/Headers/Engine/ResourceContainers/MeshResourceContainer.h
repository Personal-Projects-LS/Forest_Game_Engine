#pragma once

#include <glad/glad.h>

class MeshResourceContainer {
private:
    const unsigned int VAO{}, VBO{}, texCoordBuffer{}, normalBuffer{}, tangentBuffer{}, bitangentBuffer{};

public:
    MeshResourceContainer(const MeshResourceContainer&) = delete;
    MeshResourceContainer& operator=(const MeshResourceContainer&) = delete;

    MeshResourceContainer(
            unsigned int VAOPar,
            unsigned int VBOPar,
            unsigned int texCoordBufferPar,
            unsigned int normalBufferPar,
            unsigned int tangentBufferPar,
            unsigned int bitangentBufferPar
    ) noexcept;

    [[nodiscard]] unsigned int getVAO() const noexcept;

    ~MeshResourceContainer() noexcept;
};
