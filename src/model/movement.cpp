#include "model/movement.hpp"

Movement::Movement() {
    translation_matrix = mtlm::identity();
    rotation_matrix = mtlm::identity();
}

Movement::~Movement() {}

void Movement::set_position(simd::float3 position) {
    translation_matrix = mtlm::translation(position);
}

simd::float3 Movement::get_position() {
    return translation_matrix.columns[3].xyz;
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

void Movement::mvmt_circle(simd::float3 center, simd::float3 axis, float speed) {
    simd::float3 cur_radius = get_position() - center;
    simd::float3 direction = simd::normalize(simd::cross(axis, cur_radius)) * speed;

    /* slightly move the point pointed by direction to be on the circle */
    simd::float3 wrong_radius = cur_radius + direction;
    simd::float3 new_radius = simd::normalize(wrong_radius) * simd::length(cur_radius);
    simd::float3 dPosition = new_radius - cur_radius;

    translate(dPosition);

    simd::float3 dAngles = mtlm::angles_between(new_radius, cur_radius);
    rotate(dAngles);
}

simd::float4x4 Movement::get_movement_matrix() {
    return translation_matrix * rotation_matrix;
}
