#include "model/camera.hpp"

Camera::Camera() {
    translation_matrix = mtlm::identity();
    rotation_matrix = mtlm::identity();
    projection_matrix = mtlm::identity();
}

Camera::~Camera() {}

void Camera::set_position(simd::float3 position) {
    translation_matrix = mtlm::translation(-position);
}

void Camera::set_rotation(simd::float3 rotation) {
    rotation_matrix = mtlm::rotation(rotation);
}

void Camera::set_projection(float fovy, float aspect, float near, float far) {
    projection_matrix = mtlm::perspective_projection(fovy, aspect, near, far);
}

simd::float4x4 Camera::view_matrix() {
    return projection_matrix * translation_matrix * rotation_matrix;
}
