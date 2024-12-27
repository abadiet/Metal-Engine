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
        simd::float4{1.0f, 0.0f, 0.0f, 0.0f},
        simd::float4{0.0f, 1.0f, 0.0f, 0.0f},
        simd::float4{0.0f, 0.0f, 1.0f, 0.0f},
        simd::float4{dPos[0], dPos[1], dPos[2], 1.0f}
    };
}

simd::float4x4 mtlm::z_rotation(float angle) {
    const float c = cos(angle);
    const float s = sin(angle);
    return simd::float4x4{
        simd::float4{c, s, 0.0f, 0.0f},
        simd::float4{-s, c, 0.0f, 0.0f},
        simd::float4{0.0f, 0.0f, 1.0f, 0.0f},
        simd::float4{0.0f, 0.0f, 0.0f, 1.0f}
    };
}

simd::float4x4 mtlm::scale(float scale) {
    return simd::float4x4{
        simd::float4{scale, 0.0f, 0.0f, 0.0f},
        simd::float4{0.0f, scale, 0.0f, 0.0f},
        simd::float4{0.0f, 0.0f, scale, 0.0f},
        simd::float4{0.0f, 0.0f, 0.0f, 1.0f}
    };
}

simd::float4x4 mtlm::perspective_projection(float fovy, float aspect, float near, float far) {
    fovy = fovy * 3.14159f / 360.0f;

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
