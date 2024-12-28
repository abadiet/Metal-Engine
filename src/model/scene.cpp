#include "scene.hpp"


Scene::Scene() {}

Scene::~Scene() {}

size_t Scene::addCamera() {
    cameras.push_back(Camera());
    return cameras.size() - 1;
}

Camera* Scene::getCamera(size_t index) {
    return &cameras[index];
}

size_t Scene::getCameraCount() {
    return cameras.size();
}

size_t Scene::addObject() {
    objects.push_back(SceneObject());
    return objects.size() - 1;
}

SceneObject* Scene::getObject(size_t index) {
    return &objects[index];
}

size_t Scene::getObjectCount() {
    return objects.size();
}
