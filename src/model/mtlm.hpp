#ifndef MTL_HPP
#define MTL_HPP

#include <simd/simd.h>

#define MTLM_PI 3.1415927f

namespace mtlm {

    simd::float4x4 identity();
    simd::float4x4 translation(simd::float3 dPos);
    simd::float4x4 rotation(simd::float3 angles);
    simd::float4x4 scale(simd::float3 ratios);
    simd::float4x4 perspectiveProjection(float fovy, float aspect, float near, float far);
    simd::float3 anglesBetween(simd::float3 v1, simd::float3 v2);
}

#endif /* MTL_HPP */
