#include "model/movement.hpp"

Movement::Movement() {
    translation_matrix = mtlm::identity();
    rotation_matrix = mtlm::identity();
}

Movement::~Movement() {}

void Movement::set_position(simd::float3 position) {
    translation_matrix = mtlm::translation(position);
}

void Movement::set_orientation(simd::float3 orientation) {
    rotation_matrix = mtlm::rotation(orientation);
}

void Movement::translate(simd::float3 dPos) {
    translation_matrix = mtlm::translation(dPos) * translation_matrix;
}

void Movement::rotate(simd::float3 dAngles) {
    rotation_matrix = mtlm::rotation(dAngles) * rotation_matrix;
}

simd::float4x4 Movement::get_movement_matrix() {
    return translation_matrix * rotation_matrix;
}
