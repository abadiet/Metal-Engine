#include "model/scene_object.hpp"


SceneObject::SceneObject() {
    mesh = nullptr;
    transform = mtlm::identity();
}

SceneObject::~SceneObject() {}

void SceneObject::set_mesh(Mesh *mesh) {
    this->mesh = mesh;
}

Mesh* SceneObject::get_mesh() {
    return mesh;
}

simd::float4x4 SceneObject::get_transform() {
    return transform;
}

void SceneObject::set_transform(simd::float4x4 transform) {
    this->transform = transform;
}

void SceneObject::rotate(simd::float3 angles) {
    transform = mtlm::rotation(angles) * transform;
}

void SceneObject::translate(simd::float3 dPos) {
    transform = mtlm::translation(dPos) * transform;
}

void SceneObject::scale(simd::float3 ratios) {
    transform = mtlm::scale(ratios) * transform;
}
