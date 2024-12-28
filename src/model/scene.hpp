#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "model/camera.hpp"
#include "model/scene_object.hpp"


class Scene {

    public:
        Scene();
        ~Scene();

        size_t addCamera();
        Camera* getCamera(size_t index);
        size_t getCameraCount();

        size_t addObject();
        SceneObject* getObject(size_t index);
        size_t getObjectCount();

    private:
        std::vector<Camera> cameras;
        std::vector<SceneObject> objects;

};

#endif /* SCENE_HPP */
