#include "model/camera.hpp"

Camera::Camera() {
    projection_matrix = mtlm::identity();
}

Camera::~Camera() {}

void Camera::set_projection(float fovy, float aspect, float near, float far) {
    projection_matrix = mtlm::perspective_projection(fovy, aspect, near, far);
}

simd::float4x4 Camera::view_matrix() {
    return projection_matrix * get_movement_matrix();
}
