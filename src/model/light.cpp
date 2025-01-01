#include "model/light.hpp"

Light::Light(MTL::Device* device) {
    intensity = 1.0f;
    color = simd::float3{1.0f, 1.0f, 1.0f};

    buffer = device->newBuffer(sizeof(Light_st), MTL::ResourceStorageModeShared);
    update();
}

Light::Light(Light&& other) noexcept:
    Movement(std::move(other))
{
    intensity = other.intensity;
    color = other.color;

    if (other.buffer) {
        buffer = other.buffer->retain();
        other.buffer->release();
    }

    other.intensity = 1.0f;
    other.color = simd::float3{1.0f, 1.0f, 1.0f};
    other.buffer = nullptr;
}

Light::~Light() {
    if (buffer) buffer->release();
}

void Light::setIntensity(float intensity) {
    this->intensity = intensity;
}

float Light::getIntensity() {
    return intensity;
}

void Light::setColor(simd::float3 color) {
    this->color = color;
}

simd::float3 Light::getColor() {
    return color;
}

void Light::update() {
    Light_st light = {
        getPosition(),
        color,
        intensity
    };

    memcpy(buffer->contents(), &light, sizeof(light));
}

MTL::Buffer* Light::getBuffer() {
    return buffer;
}
