#include "model/scene_element.hpp"


SceneElement::SceneElement(MTL::Device* device) {
    rendererElement = nullptr;
    scaleMatrix = mtlm::identity();
    bufferPositionTransform = device->newBuffer(sizeof(simd::float4x4), MTL::ResourceStorageModeShared);
    bufferNormalTransform = device->newBuffer(sizeof(simd::float4x4), MTL::ResourceStorageModeShared);
}

SceneElement::SceneElement(SceneElement&& other) noexcept:
    Movement(std::move(other))
{
    rendererElement = other.rendererElement;
    scaleMatrix = other.scaleMatrix;
    if (other.bufferPositionTransform) {
        bufferPositionTransform = other.bufferPositionTransform->retain();
        other.bufferPositionTransform->release();
    }
    if (other.bufferNormalTransform) {
        bufferNormalTransform = other.bufferNormalTransform->retain();
        other.bufferNormalTransform->release();
    }

    other.rendererElement = nullptr;
    other.scaleMatrix = mtlm::identity();
    other.bufferPositionTransform = nullptr;
    other.bufferNormalTransform = nullptr;
}

SceneElement::~SceneElement() {
    if (bufferPositionTransform) {
        bufferPositionTransform->release();
    }
    if (bufferNormalTransform) {
        bufferNormalTransform->release();
    }
}

void SceneElement::setRendererElement(RendererElement *rendererElement) {
    this->rendererElement = rendererElement;
}

RendererElement* SceneElement::getRendererElement() {
    return rendererElement;
}

void SceneElement::setScale(simd::float3 ratios) {
    scaleMatrix = mtlm::scale(ratios);
}

void SceneElement::scale(simd::float3 dRatios) {
    scaleMatrix = mtlm::scale(dRatios) * scaleMatrix;
}

MTL::Buffer* SceneElement::getBufferPositionTransform() {
    const simd::float4x4 transform = getMovementMatrix() * scaleMatrix;
    memcpy(bufferPositionTransform->contents(), &transform, sizeof(transform));
    return bufferPositionTransform;
}

MTL::Buffer* SceneElement::getBufferNormalTransform() {
    const simd::float4x4 transform = getRotationMatrix();
    memcpy(bufferNormalTransform->contents(), &transform, sizeof(transform));
    return bufferNormalTransform;
}
