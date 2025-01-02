#include "model/light.hpp"

Light::Light() {
    intensity = 1.0f;
    color = simd::float3{1.0f, 1.0f, 1.0f};
}

Light::Light(Light&& other) noexcept:
    Movement(std::move(other))
{
    intensity = other.intensity;
    color = other.color;

    other.intensity = 1.0f;
    other.color = simd::float3{1.0f, 1.0f, 1.0f};
}

Light::~Light() {}

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
