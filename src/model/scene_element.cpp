#include "model/scene_element.hpp"


SceneElement::SceneElement(MTL::Device* device) {
    rendererElement = nullptr;
    scaleMatrix = mtlm::identity();
    buffer = device->newBuffer(sizeof(simd::float4x4), MTL::ResourceStorageModeShared);
}

SceneElement::SceneElement(SceneElement&& other) noexcept:
    Movement(std::move(other))
{
    rendererElement = other.rendererElement;
    scaleMatrix = other.scaleMatrix;
    if (other.buffer) {
        buffer = other.buffer->retain();
        other.buffer->release();
    }

    other.rendererElement = nullptr;
    other.scaleMatrix = mtlm::identity();
    other.buffer = nullptr;
}

SceneElement::~SceneElement() {
    if (buffer) buffer->release();
}

void SceneElement::setRendererElement(RendererElement *rendererElement) {
    this->rendererElement = rendererElement;
}

RendererElement* SceneElement::getRendererElement() {
    return rendererElement;
}

MTL::Buffer* SceneElement::getBuffer() {
    const simd::float4x4 transform = getMovementMatrix() * scaleMatrix;
    memcpy(buffer->contents(), &transform, sizeof(transform));
    return buffer;
}

void SceneElement::setScale(simd::float3 ratios) {
    scaleMatrix = mtlm::scale(ratios);
}

void SceneElement::scale(simd::float3 dRatios) {
    scaleMatrix = mtlm::scale(dRatios) * scaleMatrix;
}
