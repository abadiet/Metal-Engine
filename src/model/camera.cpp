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

void Camera::lookAt(const Movement& target, bool headUp) {
    if (headUp) {
        Movement::lookAt(target, frontVec, upVec, simd::float3{0.0f, 1.0f, 0.0f});
    } else {
        Movement::lookAt(target, frontVec);
    }
}

MTL::Buffer* Camera::getBuffer() {
    /* TODO: simd::inverse may be too expensive, manual inversion in Movement could be a solution */
    const simd::float4x4 viewMatrix = projectionMatrix * simd::inverse(getMovementMatrix());
    memcpy(buffer->contents(), &viewMatrix, sizeof(viewMatrix));
    return buffer;
}
