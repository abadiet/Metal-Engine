#include "scene.hpp"


Scene::Scene(MTL::Device* device, size_t lenBufferLights) {
    this->lenBufferLights = lenBufferLights;
    this->device = device->retain();
    bufferLights = device->newBuffer(this->lenBufferLights * sizeof(Light_st), MTL::ResourceStorageModeShared);
}

Scene::Scene(Scene&& other) noexcept {
    cameras = std::move(other.cameras);
    lights = std::move(other.lights);
    elements = std::move(other.elements);
    if (other.bufferLights) {
        bufferLights = other.bufferLights->retain();
        other.bufferLights->release();
    }
    lenBufferLights = other.lenBufferLights;
    device = other.device->retain();

    other.cameras.clear();
    other.lights.clear();
    other.elements.clear();
    other.bufferLights = nullptr;
    other.lenBufferLights = 0;
    other.device->release();
}

Scene::~Scene() {
    if (bufferLights) {
        bufferLights->release();
    }
    device->release();
}

size_t Scene::addCamera() {
    cameras.push_back(Camera(device));
    return cameras.size() - 1;
}

Camera* Scene::getCamera(size_t index) {
    return &cameras[index];
}

size_t Scene::getCameraCount() {
    return cameras.size();
}

size_t Scene::addLight() {
    lights.push_back(Light());
    return lights.size() - 1;
}

Light* Scene::getLight(size_t index) {
    return &lights[index];
}

size_t Scene::getLightCount() {
    return lights.size();
}

size_t Scene::addElement() {
    elements.push_back(SceneElement(device));
    return elements.size() - 1;
}

SceneElement* Scene::getElement(size_t index) {
    return &elements[index];
}

size_t Scene::getElementCount() {
    return elements.size();
}

void Scene::updateLight(size_t index) {
    Light_st light_st;

    if (index >= lenBufferLights) {
        updateLights();
    }

    const simd::float3& position = lights[index].getPosition();
    const simd::float3& color = lights[index].getColor();
    light_st.position[0] = position.x;
    light_st.position[1] = position.y;
    light_st.position[2] = position.z;
    light_st.color[0] = color.r;
    light_st.color[1] = color.g;
    light_st.color[2] = color.b;
    light_st.intensity = lights[index].getIntensity();

    memcpy((Light_st*) bufferLights->contents() + index, &light_st, sizeof(light_st));
}

void Scene::updateLights() {
    size_t i = 0;

    if (lights.size() > lenBufferLights) {
        bufferLights->release();
        lenBufferLights = lights.size();
        bufferLights = device->newBuffer(lenBufferLights * sizeof(Light_st), MTL::ResourceStorageModeShared);
    }

    for (i = 0; i < lights.size(); i++) {
        updateLight(i);
    }
}

MTL::Buffer* Scene::getBufferLights() {
    return bufferLights;
}
