#pragma once

#include <memory>
#include <functional>
#include <glm/vec2.hpp>
#include <vector>
#include <utility>
#include <GLFW/glfw3.h>
#include "Headers/Engine/Models/Texture.h"
#include "Headers/Engine/Camera/Camera.h"
#include "Headers/Engine/GUI/Quad.h"
#include "Headers/Engine/Models/Texture.h"

class Quad {
public:
    Quad();
    explicit Quad(const Texture& texturePar, glm::vec2 &position, glm::vec2 &scale, std::vector <glm::vec2> verts, std::vector <glm::vec2> texts, std::vector<unsigned int> inds);

    void render(Shader& shader);
    
    std::vector<glm::vec2> getVertices();

    glm::vec2 getScale();
    glm::vec2 getPos();
    glm::vec2 getOffset();

    void setOffsetX(float x);
    void setOffsetY(float y);

    ~Quad();
private:
    void bindVAO();
    void unbindVAO();
    void createBuffers();

    std::vector<glm::vec2> vertices, textureCoords;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, TBO, IBO;

    glm::vec2 position, scale, offset;
    Texture texture;
};
