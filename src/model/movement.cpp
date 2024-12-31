#include "model/movement.hpp"

Movement::Movement() {
    translationMatrix = mtlm::identity();
    rotationMatrix = mtlm::identity();
}

Movement::~Movement() {}

void Movement::setPosition(simd::float3 position) {
    translationMatrix = mtlm::translation(position);
}

simd::float3 Movement::getPosition() {
    return translationMatrix.columns[3].xyz;
}

void Movement::setOrientation(simd::float3 orientation) {
    rotationMatrix = mtlm::rotation(orientation);
}

void Movement::translate(simd::float3 dPos) {
    translationMatrix = mtlm::translation(dPos) * translationMatrix;
}

void Movement::rotate(simd::float3 dAngles) {
    rotationMatrix = mtlm::rotation(dAngles) * rotationMatrix;
}

void Movement::mvmtCircle(simd::float3 center, simd::float3 axis, float speed) {
    const simd::float3 curRadius = getPosition() - center;
    const simd::float3 direction = simd::normalize(simd::cross(axis, curRadius)) * speed;

    /* slightly move the point pointed by direction to be on the circle */
    const simd::float3 wrongRadius = curRadius + direction;
    const simd::float3 newRadius = simd::normalize(wrongRadius) * simd::length(curRadius);
    const simd::float3 dPosition = newRadius - curRadius;

    translate(dPosition);

    const simd::float3 dAngles = mtlm::anglesBetween(newRadius, curRadius);
    rotate(dAngles);
}

simd::float4x4 Movement::getMovementMatrix() {
    return translationMatrix * rotationMatrix;
}
