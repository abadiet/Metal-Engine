#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "model/camera.hpp"
#include "model/scene_element.hpp"


class Scene {

    public:
        Scene();
        ~Scene();

        size_t addCamera(MTL::Device* device);
        Camera* getCamera(size_t index);
        size_t getCameraCount();

        size_t addElement(MTL::Device* device);
        SceneElement* getElement(size_t index);
        size_t getElementCount();

    private:
        std::vector<Camera> cameras;
        std::vector<SceneElement> elements;

};

#endif /* SCENE_HPP */
