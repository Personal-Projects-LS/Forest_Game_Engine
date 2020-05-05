#define STB_IMAGE_IMPLEMENTATION
#include <Headers/Engine/Models/stb_image.h> //needs to be imported here because of an issue in stb_image

#include <memory>
#include <vector>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Headers/Engine/IO/Audio.h"
#include "Headers/Engine/Audio/Listener.h"
#include "Headers/Engine/Audio/Sound.h"
#include "Headers/Engine/Shader/Shader.h"
#include "Headers/Engine/Camera/Camera.h"
#include "Headers/Engine/Texture/Texture.h"
#include "Headers/Engine/Models/Mesh.h"
#include "Headers/Engine/Models/Entity.h"
#include "Headers/Engine/Terrain/Terrain.h"
#include "Headers/Engine/Terrain/TerrainTextureMap.h"
#include "Headers/Engine/IO/Input.h"
#include "Headers/Engine/Skybox/Skybox.h"
#include "Headers/Engine/GUI/Button.h"
#include "Headers/Engine/IO/Window.h"
#include "Headers/Engine/Graphics/HDR.h"
#include "Headers/Engine/Graphics/Lighting/PointLight.h"
#include "Headers/Engine/Graphics/Materials/Material.h"
//#include "Headers/Engine/Graphics/Lighting/IBL/HDRI.h"
//#include "Headers/Engine/Graphics/Lighting/IBL/IBL.h"

//#include "Headers/Game/Player/Player.h"
//#include "Headers/Game/Environment/BoundingBox.h"
//#include "Headers/Game/Entities/Spirit.h"
//#include "Headers/Game/Player/Shooter.h"
//#include "Headers/Game/Environment/Item.h"

//@todo find out why collision engine broke
//@todo find out why health and damage to player system is completely broken
//@todo rewrite or refactor most of the code in the Game folder
//@todo optimize startup time so that not so much time is spent (look into advanced C++, vectorization, allocators, etc.)
//@todo move raii for opengl texture resources into a heap allocated data class managed by shared_ptr (stops leaking while avoiding copy constructor calls). This will speed up start up time quite a lot.

int main() {
    Camera camera;
    Window window(&camera);
    Input input(&window, &camera);

    Audio audio;

    Listener::updatePos(glm::vec3(0, 0, 1.0f));
    Listener::updateVelocity(glm::vec3(0, 0, 0));
    Listener::updateOrientation({ 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f });

    Sound sound("../res/DuskHowl.wav");

    HDR hdr(window);

    glm::vec3 lightPos(-3200, 3200, -3200);
    glm::vec3 lightColor(0.7, 0.7, 0.7);

    std::vector<PointLight> pointLights {
            PointLight(glm::vec3(-10, 10, 16)+glm::vec3(-8.75,-8.75,0), glm::vec3(1), 1000),
            PointLight(glm::vec3(-10, -10, 16)+glm::vec3(-8.75,-8.75,0), glm::vec3(1), 1000),
            PointLight(glm::vec3(10, -10, 16)+glm::vec3(-8.75,-8.75,0), glm::vec3(1), 1000),
            PointLight(glm::vec3(10, 10, 16)+glm::vec3(-8.75,-8.75,0), glm::vec3(1), 1000)
    };

    std::vector<Entity*> entities;

    Shader pbrShader(
            "../source/Cpps/Engine/Models/Shaders/PBR/pbrVertexShader.glsl",
            "../source/Cpps/Engine/Models/Shaders/PBR/pbrFragmentShader.glsl"
    );
    Shader entityShader(
            "../source/Cpps/Engine/Models/Shaders/vertexShader.glsl",
            "../source/Cpps/Engine/Models/Shaders/fragmentShader.glsl"
    );
    Shader terrainShader(
            "../source/Cpps/Engine/Terrain/Shaders/terrainVertexShader.glsl",
            "../source/Cpps/Engine/Terrain/Shaders/terrainFragmentShader.glsl"
    );
    Shader normalMappedShader(
            "../source/Cpps/Engine/Models/Shaders/normalMappedVertex.glsl",
            "../source/Cpps/Engine/Models/Shaders/normalMappedFragment.glsl"
    );
    Shader skyboxShader(
            "../source/Cpps/Engine/Skybox/Shaders/skyboxVertexShader.glsl",
            "../source/Cpps/Engine/Skybox/Shaders/skyboxFragmentShader.glsl"
    );
    Shader buttonShader(
            "../source/Cpps/Engine/GUI/Shaders/vertexShader.glsl",
            "../source/Cpps/Engine/GUI/Shaders/fragmentShader.glsl"
    );

    //IBL Shaders
    /*Shader backgroundShader(
            "../source/Cpps/Engine/Graphics/Lighting/IBL/Shaders/backgroundVertex.glsl",
            "../source/Cpps/Engine/Graphics/Lighting/IBL/Shaders/backgroundFragment.glsl"
    );
    Shader equirectangularToCubemapShader(
            "../source/Cpps/Engine/Graphics/Lighting/IBL/Shaders/cubemapVertex.glsl",
            "../source/Cpps/Engine/Graphics/Lighting/IBL/Shaders/equirectangularToCubemapFragment.glsl"
    );
    Shader irradianceShader(
            "../source/Cpps/Engine/Graphics/Lighting/IBL/Shaders/cubemapVertex.glsl",
            "../source/Cpps/Engine/Graphics/Lighting/IBL/Shaders/irradianceConvolution.glsl"
    );
    Shader prefilterShader(
            "../source/Cpps/Engine/Graphics/Lighting/IBL/Shaders/cubemapVertex.glsl",
            "../source/Cpps/Engine/Graphics/Lighting/IBL/Shaders/prefilterFragment.glsl"
    );
    Shader brdfShader(
            "../source/Cpps/Engine/Graphics/Lighting/IBL/Shaders/brdfVertex.glsl",
            "../source/Cpps/Engine/Graphics/Lighting/IBL/Shaders/brdfFragment.glsl"
    );*/

/*
    HDRI hdri("../res/Creek.hdr");
    IBL ibl(hdri, equirectangularToCubemapShader, irradianceShader, prefilterShader, brdfShader, backgroundShader);
    ibl.setProjection(glm::perspective(glm::radians(camera.Zoom), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f));

    pbrShader.use();
    pbrShader.setInt("irradianceMap", 0);
    pbrShader.setInt("prefilterMap", 1);
    pbrShader.setInt("brdfLUT", 6);
*/
    std::shared_ptr<Mesh> containerMesh = std::make_shared<Mesh>("../res/container.obj", true);
    std::shared_ptr<Mesh> wolfMesh = std::make_shared<Mesh>("../res/wolf.obj", false);
    std::shared_ptr<Mesh> deerMesh = std::make_shared<Mesh>("../res/deer.obj", false);
    //std::shared_ptr<Mesh> sphereMesh = std::make_shared<Mesh>("../res/Sphere.obj", true);


    std::array<TerrainMesh, 2> terrainMeshes {
            TerrainMesh("../res/heightmap.png"),
            TerrainMesh("../res/heightmap2.png"),
    };

    Material pavement("../res/mud", 0);

    TerrainTextureMap terrainMap (
            "../res/blendMap.png",
            "../res/grass.png",
            "../res/mud.png",
            "../res/flowers.png",
            "../res/path.png"
    );
    std::array<const char*, 6> textures {
            "../res/Standard-Cube-Map2/px.bmp",
            "../res/Standard-Cube-Map2/nx.bmp",
            "../res/Standard-Cube-Map2/py.bmp",
            "../res/Standard-Cube-Map2/ny.bmp",
            "../res/Standard-Cube-Map2/pz.bmp",
            "../res/Standard-Cube-Map2/nz.bmp",
    };

    Texture texture("../res/container.jpg", 0, "texture0");
    Texture normalMap("../res/grass.png", 1, "texture1");
    Texture containerMap("../res/NormalMap.jpg", 2, "texture2");
    Texture specularMap("../res/SpecularMap.jpg", 3, "texture3");
    Texture wolfTexture("../res/wolfTexture.png", 0, "texture0");
    Texture deerTexture("../res/deerTexture.png", 0, "texture0");
    Texture human("../res/human.jpg", 0, "texture0");
    Texture ghostTexture("../res/ghost.png", 0, "texture0");
    Texture noteTexture("../res/note.png", 0, "texture0");

    Skybox skybox(CubeMapTexture (textures, 0));

    FontFileReader fontFile("../res/calibri.fnt");
    ImageFileReader imageFile("../res/calibri.png");

    /*Button textButton(
            std::make_unique<Text>(fontFile, imageFile, std::string("Donnette")),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.5, 1.5),
            nullptr,
            &window
    );*/

    Button textureButton(
            std::make_unique<Texture>(texture),
            glm::vec2(2.0f, -2.0f),
            glm::vec2(1.5, 1.5),
            [&hdr]()->void{hdr.setHDRStatus(!hdr.getHDRStatus());},
            &window
    );

    //Entity centerEntity(sphereMesh, pavement, pbrShader, glm::vec3(0,5,0), glm::vec3(0,0,0), glm::vec3(5,5,5));

    Entity playerEntity(
            containerMesh,
            {human},
            glm::vec3(0, 10, 0),
            glm::vec3(0, 0, 0),
            glm::vec3(1, 1, 1)
    );

    std::array<Entity, 5> containers;
    //for loop values xTranslate, yTranslate, zTranslate build a staircase with containers
    for (int i = 0, xTranslate = 0, yTranslate = 0, zTranslate = 0; i < containers.size(); ++i, xTranslate += 0, yTranslate += 20, zTranslate += 25)
    {
        containers[i] = Entity(
                containerMesh,{texture, normalMap, containerMap, specularMap},
                glm::vec3(-250 + xTranslate, 10 + yTranslate, 100 + zTranslate),
                glm::vec3(0),glm::vec3(10)
        );
        entities.push_back(&containers[i]);
    }

    CollisionHandler playerCollider(&playerEntity);
    Player player(&camera, &playerEntity, playerCollider);

    std::array<Terrain, 9> terrains;
    for (int x0 = 0, index = 0; x0 < 3 && index < terrains.size(); ++x0) {
        for (int x1 = 0; x1 < 3; ++x1, ++index) {
            terrains[index] = Terrain(terrainMap, &terrainMeshes[0], x0-1, x1-1);
        }
    }

    //sound.play();

    while (!glfwWindowShouldClose(window.getWindow())) { //&& player.getHealth() > 0) {
        Input::processInput(&player);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(static_cast<unsigned int>(GL_COLOR_BUFFER_BIT) | static_cast<unsigned int>(GL_DEPTH_BUFFER_BIT));

        hdr.bind();

        skybox.render(skyboxShader, camera);

        player.movePlayer(entities, terrains);

        player.render(normalMappedShader, lightPos, lightColor);

        for(const Entity *const entity : entities) {
            entity->render(camera, normalMappedShader, lightPos, lightColor);
        }

        for(const Terrain &terrain : terrains) {
            terrain.render(camera, terrainShader, lightPos, lightColor);
        }

        textureButton.render(buttonShader);
        //textButton.render(buttonShader); //@todo get rid of the order of rendering of quads mattering

        pbrShader.use();
        pbrShader.setInt("textured", false);
        //ibl.bindMaps();
        //centerEntity.render(camera, pointLights);


        hdr.render(entityShader, 1);

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    return 0;
}
