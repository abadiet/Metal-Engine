#include "model/camera.hpp"

Camera::Camera() {
    projectionMatrix = mtlm::identity();
}

Camera::~Camera() {}

void Camera::setProjection(float fovy, float aspect, float near, float far) {
    projectionMatrix = mtlm::perspectiveProjection(fovy, aspect, near, far);
}

simd::float4x4 Camera::viewMatrix() {
    /* TODO: simd::inverse may be too expensive, manual inversion in Movement could be a solution */
    return projectionMatrix * simd::inverse(getMovementMatrix());
}
