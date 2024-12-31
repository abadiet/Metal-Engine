#include "model/mtlm.hpp"

simd::float4x4 mtlm::identity() {
    return simd::float4x4{
        simd::float4{1.0f, 0.0f, 0.0f, 0.0f},
        simd::float4{0.0f, 1.0f, 0.0f, 0.0f},
        simd::float4{0.0f, 0.0f, 1.0f, 0.0f},
        simd::float4{0.0f, 0.0f, 0.0f, 1.0f}
    };
}

simd::float4x4 mtlm::translation(simd::float3 dPos) {
    return simd::float4x4{
        simd::float4{   1.0f,    0.0f,    0.0f, 0.0f},
        simd::float4{   0.0f,    1.0f,    0.0f, 0.0f},
        simd::float4{   0.0f,    0.0f,    1.0f, 0.0f},
        simd::float4{dPos[0], dPos[1], dPos[2], 1.0f}
    };
}

simd::float4x4 mtlm::rotation(simd::float3 angles) {
    const float c_x = cos(angles[0]);
    const float s_x = sin(angles[0]);
    const float c_y = cos(angles[1]);
    const float s_y = sin(angles[1]);
    const float c_z = cos(angles[2]);
    const float s_z = sin(angles[2]);
    return simd::float4x4{
        simd::float4{c_z * c_y, c_z * s_y * s_x - s_z * c_x, c_z * s_y * c_x + s_z * s_x, 0.0f},
        simd::float4{s_z * c_y, s_z * s_y * s_x + c_z * c_x, s_z * s_y * c_x - c_z * s_x, 0.0f},
        simd::float4{     -s_y,                   c_y * s_x,                   c_y * c_x, 0.0f},
        simd::float4{     0.0f,                        0.0f,                        0.0f, 1.0f}
    };
}

simd::float4x4 mtlm::scale(simd::float3 ratios) {
    return simd::float4x4{
        simd::float4{ratios[0], 0.0f, 0.0f, 0.0f},
        simd::float4{0.0f, ratios[1], 0.0f, 0.0f},
        simd::float4{0.0f, 0.0f, ratios[2], 0.0f},
        simd::float4{0.0f, 0.0f, 0.0f, 1.0f}
    };
}

simd::float4x4 mtlm::perspectiveProjection(float fovy, float aspect, float near, float far) {
    const float A = 1.0f / (tanf(fovy) * aspect);
    const float B = 1.0f / (tanf(fovy));
    const float C = far / (far - near);
    const float D = -near * far / (far - near);
    return simd::float4x4{
        simd::float4{    A, 0.0f, 0.0f, 0.0f},
        simd::float4{ 0.0f,    B, 0.0f, 0.0f},
        simd::float4{ 0.0f, 0.0f,    C, 1.0f},
        simd::float4{ 0.0f, 0.0f,    D, 0.0f}
    };
}

simd::float3 mtlm::anglesBetween(simd::float3 v1, simd::float3 v2) {
    const simd::float3 axis = simd::normalize(simd::cross(v1, v2));
    const float angle = acos(simd::dot(v1, v2) / (simd::length(v1) * simd::length(v2)));
    return axis * angle;
}
