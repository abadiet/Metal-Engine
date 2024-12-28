#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "model/camera.hpp"
#include "model/scene_object.hpp"


class Scene {

    public:
        Scene();
        ~Scene();

        size_t add_camera();
        Camera* get_camera(size_t index);
        size_t get_camera_count();

        size_t add_object();
        SceneObject* get_object(size_t index);
        size_t get_object_count();

    private:
        std::vector<Camera> cameras;
        std::vector<SceneObject> objects;

};

#endif /* SCENE_HPP */
