#include <metal_stdlib>

using namespace metal;

struct VertexInput {
    float3 position [[attribute(0)]];
    float3 color [[attribute(1)]];
};

struct VertexOutput {
    float4 position [[position]];
    half3 color;
};

VertexOutput vertex vertexMainGeneral(
    VertexInput input [[stage_in]],
    constant float4x4& transform [[buffer(1)]],
    constant float4x4& projection [[buffer(2)]]
) {    
    VertexOutput payload;
    payload.position = float4(half4x4(projection) * half4x4(transform) * half4(half3(input.position), 1.0));
    payload.color = half3(input.color);
    return payload;
}

half4 fragment fragmentMainGeneral(VertexOutput input [[stage_in]]) {
    return half4(input.color, 1.0);
}
