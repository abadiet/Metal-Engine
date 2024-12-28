#include "model/scene_object.hpp"


SceneObject::SceneObject() {
    mesh = nullptr;
    scale_matrix = mtlm::identity();
}

SceneObject::~SceneObject() {}

void SceneObject::set_mesh(Mesh *mesh) {
    this->mesh = mesh;
}

Mesh* SceneObject::get_mesh() {
    return mesh;
}

simd::float4x4 SceneObject::get_transform() {
    return get_movement_matrix() * scale_matrix;
}

void SceneObject::set_scale(simd::float3 ratios) {
    scale_matrix = mtlm::scale(ratios);
}

void SceneObject::scale(simd::float3 dRatios) {
    scale_matrix = mtlm::scale(dRatios) * scale_matrix;
}
