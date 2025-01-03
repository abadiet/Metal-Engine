#include "model/movement.hpp"

Movement::Movement() {
    translationMatrix = mtlm::identity();
    rotationMatrix = mtlm::identity();
}

Movement::Movement(Movement&& other) noexcept {
    translationMatrix = other.translationMatrix;
    rotationMatrix = other.rotationMatrix;

    other.translationMatrix = mtlm::identity();
    other.rotationMatrix = mtlm::identity();
}

Movement::~Movement() {}

void Movement::setPosition(simd::float3 position) {
    translationMatrix = mtlm::translation(position);
}

simd::float3 Movement::getPosition() const {
    return translationMatrix.columns[3].xyz;
}

void Movement::setOrientation(simd::float3 orientation) {
    rotationMatrix = mtlm::rotation(orientation);
}

void Movement::translate(simd::float3 dPos, bool realtive) {
    if (realtive) {
        dPos = Relative2World(dPos);
    }
    translationMatrix = mtlm::translation(dPos) * translationMatrix;
}

void Movement::rotate(simd::float3 dAngles, bool relative) {
    if (relative) {
        dAngles = Relative2World(dAngles);
    }
    rotationMatrix = mtlm::rotation(dAngles) * rotationMatrix;
}

void Movement::mvmtCircle(simd::float3 center, simd::float3 axis, float speed, bool lookAtCenter) {
    const simd::float3 curRadius = getPosition() - center;
    const simd::float3 direction = simd::normalize(simd::cross(axis, curRadius)) * speed;

    /* slightly move the point pointed by direction to be on the circle */
    const simd::float3 wrongRadius = curRadius + direction;
    const simd::float3 newRadius = simd::normalize(wrongRadius) * simd::length(curRadius);
    const simd::float3 dPosition = newRadius - curRadius;

    translate(dPosition);

    if (lookAtCenter) {
        const simd::float3 dAngles = mtlm::anglesBetween(newRadius, curRadius);
        rotate(dAngles);
    }
}

void Movement::lookAt(const Movement& target, simd::float3 front) {
    const simd::float3 direction = simd::normalize(target.getPosition() - getPosition());
    const simd::float3 angles = mtlm::anglesBetween(direction, front);
    setOrientation(angles);
}

void Movement::lookAt(const Movement& target, simd::float3 front, simd::float3 selfVec, simd::float3 worldVec) {
    simd::float3 dAnglesRelative;
    lookAt(target, front);
    const simd::float3 dAngles = -mtlm::anglesBetween(worldVec, World2Relative(selfVec));
    dAnglesRelative = World2Relative(dAngles);
    dAnglesRelative.x = 0.0f;
    dAnglesRelative.y = 0.0f;
    rotate(dAnglesRelative, true);
}

simd::float3 Movement::World2Relative(simd::float3 worldVec) {
    return (rotationMatrix * simd::float4{worldVec.x, worldVec.y, worldVec.z, 1.0f}).xyz;
}

simd::float3 Movement::Relative2World(simd::float3 relativeVec) {
    return (simd::inverse(rotationMatrix) * simd::float4{relativeVec.x, relativeVec.y, relativeVec.z, 1.0f}).xyz;
}

simd::float4x4 Movement::getMovementMatrix() {
    return translationMatrix * rotationMatrix;
}

simd::float4x4 Movement::getTranslationMatrix() {
    return translationMatrix;
}

simd::float4x4 Movement::getRotationMatrix() {
    return rotationMatrix;
}
