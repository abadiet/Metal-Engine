#ifndef SCENE_HPP
#define SCENE_HPP

#include <Metal/Metal.hpp>
#include <vector>
#include "model/camera.hpp"
#include "model/light.hpp"
#include "model/scene_element.hpp"


class Scene {

    public:
        Scene(MTL::Device* device, size_t lenBufferLights = 8);
        Scene(Scene&& other) noexcept;
        ~Scene();

        size_t addCamera();
        Camera* getCamera(size_t index);
        size_t getCameraCount();

        size_t addLight();
        Light* getLight(size_t index);
        size_t getLightCount();

        size_t addElement();
        SceneElement* getElement(size_t index);
        size_t getElementCount();

        void updateLight(size_t index);
        void updateLights();
        MTL::Buffer* getBufferLights();

    private:
        typedef struct __attribute__((packed)) {
            float position[3];
            float color[3];
            float intensity;
        } Light_st;

        std::vector<Camera> cameras;
        std::vector<Light> lights;
        std::vector<SceneElement> elements;
        MTL::Buffer *bufferLights;
        size_t lenBufferLights;
        MTL::Device *device;

};

#endif /* SCENE_HPP */
