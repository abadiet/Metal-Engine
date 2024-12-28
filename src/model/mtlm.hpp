#ifndef MTL_HPP
#define MTL_HPP

#include <simd/simd.h>

namespace mtlm {

    simd::float4x4 identity();
    simd::float4x4 translation(simd::float3 dPos);
    simd::float4x4 rotation(simd::float3 angles);
    simd::float4x4 scale(simd::float3 ratios);
    simd::float4x4 perspective_projection(float fovy, float aspect, float near, float far);

}

#endif /* MTL_HPP */
