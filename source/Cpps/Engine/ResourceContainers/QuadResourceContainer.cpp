#include "Headers/Engine/ResourceContainers/QuadResourceContainer.h"

QuadResourceContainer::QuadResourceContainer(const unsigned int VAOPar, const unsigned int VBOPar, const unsigned int TBOPar, const unsigned int IBOPar) noexcept
: VAO(VAOPar), VBO(VBOPar), TBO(TBOPar), IBO(IBOPar)
{}

[[nodiscard]] unsigned int QuadResourceContainer::getVAO() const noexcept {
    return VAO;
}

QuadResourceContainer::~QuadResourceContainer() noexcept {
    glDeleteBuffers(1, &IBO);
    glDeleteBuffers(1, &TBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}