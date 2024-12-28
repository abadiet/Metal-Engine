#include <metal_stdlib>

using namespace metal;

struct VertexInput {
    float3 position [[attribute(0)]];
    float3 normal [[attribute(1)]];
    float3 color [[attribute(2)]];
};

struct VertexOutput {
    float4 position [[position]];
    float3 normal;
    half3 color;
};

VertexOutput vertex vertexMainGeneral(
    VertexInput input [[stage_in]],
    constant float4x4& transform [[buffer(1)]],
    constant float4x4& projection [[buffer(2)]]
) {    
    VertexOutput output;
    output.position = float4(half4x4(projection) * half4x4(transform) * half4(half3(input.position), 1.0));
    output.normal = float3(input.normal);
    output.color = half3(input.color);
    return output;
}

half4 fragment fragmentMainGeneral(VertexOutput input [[stage_in]]) {
    /* assume light coming from (front-top-right), Lambertian reflectance */
    float3 l = normalize(float3(1.0, 1.0, 0.8));
    float3 n = normalize(input.normal);
    return half4(input.color * (0.1 + saturate(dot(n, l))), 1.0);
}
