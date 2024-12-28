#include "scene.hpp"


Scene::Scene() {}

Scene::~Scene() {}

size_t Scene::add_camera() {
    cameras.push_back(Camera());
    return cameras.size() - 1;
}

Camera* Scene::get_camera(size_t index) {
    return &cameras[index];
}

size_t Scene::get_camera_count() {
    return cameras.size();
}

size_t Scene::add_object() {
    objects.push_back(SceneObject());
    return objects.size() - 1;
}

SceneObject* Scene::get_object(size_t index) {
    return &objects[index];
}

size_t Scene::get_object_count() {
    return objects.size();
}
