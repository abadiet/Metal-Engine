#include "model/scene_element.hpp"


SceneElement::SceneElement() {
    rendererElement = nullptr;
    scaleMatrix = mtlm::identity();
}

SceneElement::~SceneElement() {}

void SceneElement::setRendererElement(RendererElement *rendererElement) {
    this->rendererElement = rendererElement;
}

RendererElement* SceneElement::getRendererElement() {
    return rendererElement;
}

simd::float4x4 SceneElement::getTransform() {
    return getMovementMatrix() * scaleMatrix;
}

void SceneElement::setScale(simd::float3 ratios) {
    scaleMatrix = mtlm::scale(ratios);
}

void SceneElement::scale(simd::float3 dRatios) {
    scaleMatrix = mtlm::scale(dRatios) * scaleMatrix;
}
