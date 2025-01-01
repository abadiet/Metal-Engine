#include "model/camera.hpp"

Camera::Camera(MTL::Device* device) {
    projectionMatrix = mtlm::identity();
    buffer = device->newBuffer(sizeof(simd::float4x4), MTL::ResourceStorageModeShared);
}

Camera::Camera(Camera&& other) noexcept:
    Movement(std::move(other))
{
    projectionMatrix = other.projectionMatrix;
    if (other.buffer) {
        buffer = other.buffer->retain();
        other.buffer->release();
    }

    other.projectionMatrix = mtlm::identity();
    other.buffer = nullptr;
}

Camera::~Camera() {
    if (buffer) buffer->release();
}

void Camera::setProjection(float fovy, float aspect, float near, float far) {
    projectionMatrix = mtlm::perspectiveProjection(fovy, aspect, near, far);
}

MTL::Buffer* Camera::getBuffer() {
    /* TODO: simd::inverse may be too expensive, manual inversion in Movement could be a solution */
    const simd::float4x4 viewMatrix = projectionMatrix * simd::inverse(getMovementMatrix());
    memcpy(buffer->contents(), &viewMatrix, sizeof(viewMatrix));
    return buffer;
}
