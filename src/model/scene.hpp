#ifndef SCENE_HPP
#define SCENE_HPP

#include <Metal/Metal.hpp>
#include <vector>
#include "model/camera.hpp"
#include "model/light.hpp"
#include "model/scene_element.hpp"


class Scene {

    public:
        Scene();
        ~Scene();

        size_t addCamera(MTL::Device* device);
        Camera* getCamera(size_t index);
        size_t getCameraCount();

        size_t addLight(MTL::Device* device);
        Light* getLight(size_t index);
        size_t getLightCount();

        size_t addElement(MTL::Device* device);
        SceneElement* getElement(size_t index);
        size_t getElementCount();

    private:
        std::vector<Camera> cameras;
        std::vector<Light> lights;
        std::vector<SceneElement> elements;

};

#endif /* SCENE_HPP */
