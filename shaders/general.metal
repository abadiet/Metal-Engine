#include <metal_stdlib>

using namespace metal;

struct VertexInput {
    float3 position [[attribute(0)]];
    float3 normal [[attribute(1)]];
    float3 color [[attribute(2)]];
};

struct Light {
    float3 position;
    float3 color;
    float intensity;
};

struct VertexOutput {
    float4 projectedPosition [[position]];
    float3 normal;
    half3 color;
    float3 realPosition;
};

VertexOutput vertex vertexMainGeneral(
    VertexInput input [[stage_in]],
    constant float4x4& posTransform [[buffer(1)]],
    constant float4x4& normTransform [[buffer(2)]],
    constant float4x4& projection [[buffer(3)]]
) {    
    VertexOutput output;
    const half4 transformedPosMat = half4x4(posTransform) * half4(half3(input.position), 1.0);
    output.realPosition = float3(transformedPosMat.xyz);
    output.projectedPosition = float4(half4x4(projection) * transformedPosMat);
    output.normal = float3((half4x4(normTransform) * half4(half3(input.normal), 1.0)).xyz);
    output.color = half3(input.color);
    return output;
}

half4 fragment fragmentMainGeneral(
    VertexOutput input [[stage_in]],
    constant Light& light [[buffer(0)]]
) {
    const float3 normal = normalize(input.normal);
    const float3 inBetween = input.realPosition - light.position;
    const float distance = length(inBetween);
    const float intensity = max(dot(normal, normalize(inBetween)), 0.0) * light.intensity / (4.0 * 3.14159265359 * distance * distance);
    return half4(input.color * half3(light.color) * half3(intensity), 1.0);
}
