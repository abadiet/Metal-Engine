#include "scene.hpp"


Scene::Scene() {}

Scene::~Scene() {}

size_t Scene::addCamera(MTL::Device* device) {
    cameras.push_back(Camera(device));
    return cameras.size() - 1;
}

Camera* Scene::getCamera(size_t index) {
    return &cameras[index];
}

size_t Scene::getCameraCount() {
    return cameras.size();
}

size_t Scene::addLight(MTL::Device* device) {
    lights.push_back(Light(device));
    return lights.size() - 1;
}

Light* Scene::getLight(size_t index) {
    return &lights[index];
}

size_t Scene::getLightCount() {
    return lights.size();
}

size_t Scene::addElement(MTL::Device* device) {
    elements.push_back(SceneElement(device));
    return elements.size() - 1;
}

SceneElement* Scene::getElement(size_t index) {
    return &elements[index];
}

size_t Scene::getElementCount() {
    return elements.size();
}
