#define STB_IMAGE_IMPLEMENTATION
#include "Headers/stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Headers/Engine/Shader.h"
#include "Headers/Engine/Camera.h"
#include "Headers/Engine/Models/Texture.h"
#include "Headers/Engine/Models/Mesh.h"
#include "Headers/Engine/Models/Entity.h"
#include "Headers/Engine/Terrain/Terrain.h"
#include "Headers/Engine/Terrain/TerrainTextureMap.h"
#include <glm/glm.hpp>
#include "Headers/Game/Player.h"

#include <iostream>
#include <Headers/Engine/Skybox/Skybox.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = 400, lastY = 300;
bool firstMouse = true;

Camera camera;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader entityShader("../source/Engine/Models/Shaders/vertexShader.glsl", "../source/Engine/Models/Shaders/fragmentShader.glsl");
    Shader terrainShader("../source/Engine/Terrain/Shaders/terrainVertexShader.glsl", "../source/Engine/Terrain/Shaders/terrainFragmentShader.glsl");
    Shader normalMappedShader("../source/Engine/Models/Shaders/normalMappedVertex.glsl", "../source/Engine/Models/Shaders/normalMappedFragment.glsl");
    Shader skyboxShader("../source/Engine/Skybox/Shaders/skyboxVertexShader.glsl", "../source/Engine/Skybox/Shaders/skyboxFragmentShader.glsl");
    Texture texture("../res/container.jpg", Texture::JPG, 0);
    Texture normalMap("../res/grass.png", Texture::PNG, 1);
    Texture containerMap("../res/NormalMap.jpg", Texture::JPG, 2);
    std::vector<Texture> containerTextures;
    containerTextures.push_back(texture);
    containerTextures.push_back(normalMap);
    containerTextures.push_back(containerMap);
    Mesh containerMesh("../res/container.obj");
    Mesh containerMesh2("../res/container.obj");
    Mesh dragonMesh("../res/dragon.obj");
    Entity container(containerMesh, containerTextures, glm::vec3(0,10,-15), glm::vec3(0,45,0), glm::vec3(1,1,1));
    Entity container2(containerMesh2, containerTextures, glm::vec3(0,10,-15), glm::vec3(0,45,0), glm::vec3(1,1,1));
    containerTextures.pop_back();
    Entity nonMappedContainer(containerMesh, containerTextures, glm::vec3(-15, 10, -15), glm::vec3(0, 45, 0), glm::vec3(1,1,1));
    containerTextures.pop_back();
    Entity lightExample(containerMesh, containerTextures, glm::vec3(10, 10, 0), glm::vec3(0, 0, 0), glm::vec3(0.1f, 0.1f, 0.1f));
    TerrainTextureMap terrainMap("../res/blendMap.png", "../res/grass.png", "../res/mud.png", "../res/flowers.png", "../res/path.png");
    TerrainMesh terrainMesh(1, "../res/heightmap.png");
    Terrain terrain1(terrainMap, terrainMesh, 0, 0);
    Terrain terrain2(terrainMap, terrainMesh, -1, 0);
    Terrain terrain3(terrainMap, terrainMesh, -1, -1);
    Terrain terrain4(terrainMap, terrainMesh, 0, -1);
    std::vector<const char*> textures
    {
        "../res/right.jpg",
        "../res/left.jpg",
        "../res/top.jpg",
        "../res/bottom.jpg",
        "../res/front.jpg",
        "../res/back.jpg"
    };
    CubeMapTexture cubeMapTexture(textures, 0);
    Skybox skybox(cubeMapTexture);
    glm::vec3 lightPos(-3200, 3200, -3200);
    glm::vec3 lightColor(0.7, 0.7, 0.7);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Player player(&terrain1, &camera, &container2, &entityShader);

    // render Loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        skybox.render(skyboxShader, camera);
        player.setHeight();
        // draw our first triangle
        container.render(camera, entityShader, lightPos, lightColor);
        nonMappedContainer.render(camera, normalMappedShader, lightPos, lightColor);
        lightExample.render(camera, entityShader, lightPos, lightColor);
        container.rotate(1,1,0);
        nonMappedContainer.rotate(1,1,0);
        terrain1.render(camera, terrainShader, lightPos, lightColor);
        terrain2.render(camera, terrainShader, lightPos, lightColor);
        terrain3.render(camera, terrainShader, lightPos, lightColor);
        terrain4.render(camera, terrainShader, lightPos, lightColor);
        player.setHeight();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}