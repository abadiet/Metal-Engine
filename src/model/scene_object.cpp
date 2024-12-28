#include "model/scene_object.hpp"


SceneObject::SceneObject() {
    mesh = nullptr;
    scaleMatrix = mtlm::identity();
}

SceneObject::~SceneObject() {}

void SceneObject::setMesh(Mesh *mesh) {
    this->mesh = mesh;
}

Mesh* SceneObject::getMesh() {
    return mesh;
}

simd::float4x4 SceneObject::getTransform() {
    return getMovementMatrix() * scaleMatrix;
}

void SceneObject::setScale(simd::float3 ratios) {
    scaleMatrix = mtlm::scale(ratios);
}

void SceneObject::scale(simd::float3 dRatios) {
    scaleMatrix = mtlm::scale(dRatios) * scaleMatrix;
}
