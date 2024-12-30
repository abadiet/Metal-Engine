#include "view/renderer_element.hpp"

RendererElement RendererElement::BuildSquare(MTL::Device* device) {
    RendererElement obj;

    std::vector<Vertex> vertices = {
        {{-0.75f, -0.75f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.75f, -0.75f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.75f,  0.75f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.75f,  0.75f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.75f, -0.75f, 0.75f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.75f, -0.75f, 0.75f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.75f,  0.75f, 0.75f}, {0.0f, 0.0f, 1.0f}},
        {{-0.75f,  0.75f, 0.75f}, {0.0f, 0.0f, 1.0f}}
    };

    std::vector<ushort> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
    };

    std::vector<simd::float3> colors = {
        simd::float3{1.0f, 0.0f, 0.0f},
        simd::float3{0.0f, 1.0f, 0.0f},
        simd::float3{0.0f, 0.0f, 1.0f},
        simd::float3{0.0f, 1.0f, 0.0f},
        simd::float3{1.0f, 0.0f, 1.0f},
        simd::float3{0.0f, 1.0f, 0.0f},
        simd::float3{1.0f, 0.0f, 1.0f},
        simd::float3{0.0f, 1.0f, 0.0f}
    };

    obj.setVertices(vertices);
    obj.setIndices(indices);
    obj.setColors(colors);

    obj.update(device);

    obj.setPipeline(Pipeline::BuildGeneral(device));

    return obj;
}

RendererElement RendererElement::BuildCube(MTL::Device* device) {
    RendererElement obj;

    const float s = 0.75f;
    std::vector<Vertex> vertices = {
        { { -s, -s, +s }, { 0.f,  0.f,  1.f } },
        { { +s, -s, +s }, { 0.f,  0.f,  1.f } },
        { { +s, +s, +s }, { 0.f,  0.f,  1.f } },
        { { -s, +s, +s }, { 0.f,  0.f,  1.f } },

        { { +s, -s, +s }, { 1.f,  0.f,  0.f } },
        { { +s, -s, -s }, { 1.f,  0.f,  0.f } },
        { { +s, +s, -s }, { 1.f,  0.f,  0.f } },
        { { +s, +s, +s }, { 1.f,  0.f,  0.f } },

        { { +s, -s, -s }, { 0.f,  0.f, -1.f } },
        { { -s, -s, -s }, { 0.f,  0.f, -1.f } },
        { { -s, +s, -s }, { 0.f,  0.f, -1.f } },
        { { +s, +s, -s }, { 0.f,  0.f, -1.f } },

        { { -s, -s, -s }, { -1.f, 0.f,  0.f } },
        { { -s, -s, +s }, { -1.f, 0.f,  0.f } },
        { { -s, +s, +s }, { -1.f, 0.f,  0.f } },
        { { -s, +s, -s }, { -1.f, 0.f,  0.f } },

        { { -s, +s, +s }, { 0.f,  1.f,  0.f } },
        { { +s, +s, +s }, { 0.f,  1.f,  0.f } },
        { { +s, +s, -s }, { 0.f,  1.f,  0.f } },
        { { -s, +s, -s }, { 0.f,  1.f,  0.f } },

        { { -s, -s, -s }, { 0.f, -1.f,  0.f } },
        { { +s, -s, -s }, { 0.f, -1.f,  0.f } },
        { { +s, -s, +s }, { 0.f, -1.f,  0.f } },
        { { -s, -s, +s }, { 0.f, -1.f,  0.f } }
    };

    std::vector<ushort> indices = {
         0,  1,  2,  2,  3,  0, /* front */
         4,  5,  6,  6,  7,  4, /* right */
         8,  9, 10, 10, 11,  8, /* back */
        12, 13, 14, 14, 15, 12, /* left */
        16, 17, 18, 18, 19, 16, /* top */
        20, 21, 22, 22, 23, 20, /* bottom */
    };

    std::vector<simd::float3> colors = {
        simd::float3{ 1.f,  0.f,  1.f },
        simd::float3{ 0.f,  1.f,  1.f },
        simd::float3{ 1.f,  0.f,  0.f },
        simd::float3{ 0.f,  1.f,  0.f },

        simd::float3{ 0.f,  1.f,  0.f },
        simd::float3{ 0.f,  1.f,  0.f },
        simd::float3{ 0.f,  1.f,  0.f },
        simd::float3{ 0.f,  1.f,  0.f },

        simd::float3{ 0.f,  1.f,  1.f },
        simd::float3{ 0.f,  1.f,  1.f },
        simd::float3{ 0.f,  1.f,  1.f },
        simd::float3{ 0.f,  1.f,  1.f },

        simd::float3{ 1.f,  0.f,  1.f },
        simd::float3{ 1.f,  0.f,  1.f },
        simd::float3{ 1.f,  0.f,  1.f },
        simd::float3{ 1.f,  0.f,  1.f },

        simd::float3{ 1.f,  0.f,  0.f },
        simd::float3{ 1.f,  0.f,  0.f },
        simd::float3{ 1.f,  0.f,  0.f },
        simd::float3{ 1.f,  0.f,  0.f },

        simd::float3{ 1.f,  1.f,  0.f },
        simd::float3{ 1.f,  1.f,  0.f },
        simd::float3{ 1.f,  1.f,  0.f },
        simd::float3{ 1.f,  1.f,  0.f }
    };

    obj.setVertices(vertices);
    obj.setIndices(indices);
    obj.setColors(colors);

    obj.update(device);

    obj.setPipeline(Pipeline::BuildGeneral(device));

    return obj;
}

RendererElement::~RendererElement() {
    /* TODO */
    // vertexBuffer->release();
    // indexBuffer->release();
}

void RendererElement::update(MTL::Device* device) {
    std::vector<CompleteVertex> tosend;
    CompleteVertex tmp;
    size_t i = 0;
    auto colors = getColors();
    auto indices = getIndices();
    auto vertices = getVertices();

    if (colors.size() == 0 || indices.size() == 0 || vertices.size() == 0) {
        throw std::runtime_error("RendererElement::update: invalid data");
    }

    for (const Mesh::Vertex& vertex : vertices) {
        tmp.vertex = vertex;
        tmp.color = colors[i];
        i = (i + 1) % colors.size();
        tosend.push_back(tmp);
    }

    const size_t tosend_sz = tosend.size() * sizeof(tosend[0]);
    vertexBuffer = device->newBuffer(tosend_sz, MTL::ResourceStorageModeShared);
    memcpy(vertexBuffer->contents(), tosend.data(), tosend_sz);

    const size_t indices_sz = indices.size() * sizeof(indices[0]);
    indexBuffer = device->newBuffer(indices_sz, MTL::ResourceStorageModeShared);
    memcpy(indexBuffer->contents(), indices.data(), indices_sz);
}

MTL::RenderPipelineState* RendererElement::getPipeline() const {
    return pipeline;
}

void RendererElement::setPipeline(MTL::RenderPipelineState* pipeline) {
    this->pipeline = pipeline;
}

MTL::Buffer* RendererElement::getVertexBuffer() const {
    return vertexBuffer;
}

MTL::Buffer* RendererElement::getIndexBuffer() const {
    return indexBuffer;
}

RendererElement::RendererElement() {}
