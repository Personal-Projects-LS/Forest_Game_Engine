#include "Headers/Engine/ResourceContainers/MeshResourceContainer.h"

MeshResourceContainer::MeshResourceContainer(
        const unsigned int VAOPar,
        const unsigned int VBOPar,
        const unsigned int texCoordBufferPar,
        const unsigned int normalBufferPar,
        const unsigned int tangentBufferPar,
        const unsigned int bitangentBufferPar) noexcept
: VAO(VAOPar), VBO(VBOPar), texCoordBuffer(texCoordBufferPar),
    normalBuffer(normalBufferPar), tangentBuffer(tangentBufferPar),
    bitangentBuffer(bitangentBufferPar)
{}

[[nodiscard]] unsigned int MeshResourceContainer::getVAO() const noexcept {
    return VAO;
}

MeshResourceContainer::~MeshResourceContainer() noexcept {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &texCoordBuffer);
    glDeleteBuffers(1, &normalBuffer);
    glDeleteBuffers(1, &tangentBuffer);
    glDeleteBuffers(1, &bitangentBuffer);
    glDeleteVertexArrays(1, &VAO);
}


