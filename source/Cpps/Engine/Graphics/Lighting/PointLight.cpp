//
// Created by TRAG4 on 1/29/2020.
//
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <Headers/Engine/Graphics/Lighting/PointLight.h>





PointLight::PointLight(glm::vec3 position, glm::vec3 color, float intensity) {
    this->position = position;
    this->color = color;
    this->intensity = intensity;
}
