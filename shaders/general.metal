#include <metal_stdlib>

using namespace metal;

struct VertexInput {
    float3 position [[attribute(0)]];
    float3 normal [[attribute(1)]];
    float3 color [[attribute(2)]];
    float2 texCoord [[attribute(3)]];
};

struct  __attribute__((packed)) Light {
    packed_float3 position;
    packed_float3 color;
    float intensity;
};

struct VertexOutput {
    float4 projectedPosition [[position]];
    float3 realPosition;
    float3 normal;
    half3 color;
    float2 texCoord;
};

VertexOutput vertex vertexMainGeneral(
    VertexInput input [[stage_in]],
    constant float4x4 &posTransform [[buffer(1)]],
    constant float4x4 &normTransform [[buffer(2)]],
    constant float4x4 &projection [[buffer(3)]]
) {
    VertexOutput output;
    const float4 transformedPosMat = float4x4(posTransform) * float4(input.position, 1.0);
    output.realPosition = transformedPosMat.xyz;
    output.projectedPosition = float4x4(projection) * transformedPosMat;
    output.normal = normalize(float3((half4x4(normTransform) * half4(half3(input.normal), 1.0)).xyz));
    output.color = half3(input.color);
    output.texCoord = input.texCoord;
    return output;
}

half4 fragment fragmentMainGeneral(
    VertexOutput input [[stage_in]],
    constant Light *light [[buffer(0)]],
    constant int &lightCount [[buffer(1)]],
    texture2d< half, access::sample > texture [[texture(0)]]
) {
    int i;
    half3 lightColor = half3(0.0, 0.0, 0.0);
    for (i = 0; i < lightCount; i++) {
        const Light l = light[i];
        const float3 inBetween = l.position - input.realPosition;
        const float distance = length(inBetween);
        const float intensity = max(dot(input.normal, normalize(inBetween)), 0.0) * l.intensity / (distance * distance);
        lightColor += half3(l.color) * intensity;
    }
    // color = clamp(color, half3(0.0, 0.0, 0.0), half3(1.0, 1.0, 1.0));
    // input.color = clamp(input.color, half3(0.0, 0.0, 0.0), half3(1.0, 1.0, 1.0));

    if (input.texCoord.x < 0.0 || input.texCoord.y < 0.0 || input.texCoord.x > 1.0 || input.texCoord.y > 1.0) {
        return half4(input.color * lightColor, 1.0);
    }
    constexpr sampler s(address::repeat, filter::linear);
    const half3 texel = texture.sample(s, input.texCoord).rgb;

    return half4(input.color * lightColor * texel, 1.0);
}
