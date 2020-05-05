#include "Headers/Engine/Models/Entity.h"

Entity::Entity(
        const std::shared_ptr<Mesh> &mesh,
        const std::vector<Texture> &textures,
        const glm::vec3 &position = glm::vec3(0, 0, 0),
        const glm::vec3 &rotation = glm::vec3(0,0,0),
        const glm::vec3& scale = glm::vec3(1,1,1)) noexcept
        : mesh(mesh), textures(textures), position(position), rotation(rotation), scale(scale)
{
    createModelMatrix();
    moveEntityPlanes(mesh->getVertices());
}

//takes a shader and a Material instead of an array of textures.
Entity::Entity(
        const std::shared_ptr<Mesh> &mesh,
        const Material &material,
        const Shader &shader,
        const glm::vec3 &position,
        const glm::vec3 &rotation,
        const glm::vec3& scale) noexcept
        : mesh(mesh), shader(shader), material(material), position(position), rotation(rotation), scale(scale)
{
    createModelMatrix();
    moveEntityPlanes(mesh->getVertices());
}

void Entity::render(const Camera& camera, const Shader& inputShader, glm::vec3 lightPos, glm::vec3 lightColor) const noexcept {
    inputShader.use();

    mesh->bindVAO();
    for(const Texture &texture : textures) {
        texture.bind(inputShader);
    }

    camera.setMatrices(inputShader);

    const int modelLoc = glGetUniformLocation(inputShader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    const int lightLoc = glGetUniformLocation(inputShader.ID, "lightPos");
    glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));

    const int lightCol = glGetUniformLocation(inputShader.ID, "lightColor");
    glUniform3fv(lightCol, 1, glm::value_ptr(lightColor));

    const int viewLoc = glGetUniformLocation(inputShader.ID, "viewPos");
    glUniform3fv(viewLoc, 1, glm::value_ptr(camera.getPos()));

    glDrawArrays(GL_TRIANGLES, 0, mesh->getNumOfVertices());

    for (const Texture &texture : textures) {
        texture.unbind();
    }

    Mesh::unbindVAO();
}

void Entity::render(const Camera &camera, const std::vector<PointLight> &pointLights) const noexcept {
    shader.use();

    mesh->bindVAO();

    material.getAlbedo().bind(shader);
    material.getAo().bind(shader);
    material.getMetallic().bind(shader);
    material.getNormal().bind(shader);
    material.getRoughness().bind(shader);

    camera.setMatrices(shader);

    const int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    const int viewLoc = glGetUniformLocation(shader.ID, "viewPos");
    glUniform3fv(viewLoc, 1, glm::value_ptr(camera.getPos()));

    for(int i = 0; i < pointLights.size(); ++i) {
        shader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLights[i].position);
        shader.setVec3("pointLights[" + std::to_string(i) + "].color", pointLights[i].color);
        shader.setFloat("pointLights[" + std::to_string(i) + "].intensity", pointLights[i].intensity);
    }

    shader.setFloat("nLights", pointLights.size());
    //shader.setVec3("test", glm::vec3(1,0,0));

    glDrawArrays(GL_TRIANGLES, 0, mesh->getNumOfVertices());

    material.getAlbedo().unbind();
    material.getAo().unbind();
    material.getMetallic().unbind();
    material.getNormal().unbind();
    material.getRoughness().unbind();

    Mesh::unbindVAO();
}

glm::mat4 Entity::createModelMatrix() noexcept {
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1,0,0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0,1,0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0,0,1));
    modelMatrix = glm::scale(modelMatrix, scale);
    return modelMatrix;
}

glm::vec3 Entity::getPos() const noexcept {
    return position;
}

glm::vec3 Entity::getRotation() const noexcept {
    return rotation;
}

void Entity::setRotation(const glm::vec3 newRotation) noexcept {
    rotation = newRotation;
    createModelMatrix();
    moveEntityPlanes(mesh->getCollisionCube());
}

void Entity::setPos(const glm::vec3 newPos) noexcept {
    position = newPos;
    createModelMatrix();
    moveEntityPlanes(mesh->getCollisionCube());
}

void Entity::rotate(const glm::vec3 rotationPar) noexcept {
    rotation += rotationPar;
    limitRotation();
    createModelMatrix();
    moveEntityPlanes(mesh->getCollisionCube());
}

void Entity::translate(const glm::vec3 translation) noexcept {
    position += translation;
    createModelMatrix();
    moveEntityPlanes(mesh->getCollisionCube());
}

void Entity::addScale(const glm::vec3 scalePar) noexcept {
    scale += scalePar;
    createModelMatrix();
    moveEntityPlanes(mesh->getCollisionCube());
}

void Entity::limitRotation() noexcept { //@todo replace with modulo
    for(int i = 0; i < rotation.length(); ++i) {
        if (rotation[i] > 360) {
            rotation[i] -= 360;
        } else if (rotation[i] < 0) {
            rotation[i] += 360;
        }
    }
}

glm::vec3 Entity::getScale() const noexcept {
    return scale;
}

void Entity::moveEntityPlanes(const std::vector<glm::vec3> &vertices) noexcept {
    planes.clear();
    int i = 0;
    while(i < vertices.size()) {
        const glm::vec3 point1 = modelMatrix * glm::vec4(vertices[i++], 1);
        const glm::vec3 point2 = modelMatrix * glm::vec4(vertices[i++], 1);
        const glm::vec3 point3 = modelMatrix * glm::vec4(vertices[i++], 1);
        planes.emplace_back(point1, point2, point3, flipped);
    }
}

void Entity::setFlipped() noexcept {
    flipped = 1;
    moveEntityPlanes(mesh->getVertices());
}
