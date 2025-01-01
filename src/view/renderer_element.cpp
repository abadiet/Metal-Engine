#include "view/renderer_element.hpp"

RendererElement RendererElement::BuildSquare(MTL::Device* device) {
    const std::vector<Vertex> vertices = {
        {{-0.75f, -0.75f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.75f, -0.75f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.75f,  0.75f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.75f,  0.75f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.75f, -0.75f, 0.75f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.75f, -0.75f, 0.75f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.75f,  0.75f, 0.75f}, {0.0f, 0.0f, 1.0f}},
        {{-0.75f,  0.75f, 0.75f}, {0.0f, 0.0f, 1.0f}}
    };

    const std::vector<ushort> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
    };

    const std::vector<simd::float3> colors = {
        simd::float3{1.0f, 0.0f, 0.0f},
        simd::float3{0.0f, 1.0f, 0.0f},
        simd::float3{0.0f, 0.0f, 1.0f},
        simd::float3{0.0f, 1.0f, 0.0f},
        simd::float3{1.0f, 0.0f, 1.0f},
        simd::float3{0.0f, 1.0f, 0.0f},
        simd::float3{1.0f, 0.0f, 1.0f},
        simd::float3{0.0f, 1.0f, 0.0f}
    };

    return RendererElement(device, Mesh(vertices, indices), Colors(colors), Pipeline::BuildGeneral(device));
}

RendererElement RendererElement::BuildCube(MTL::Device* device) {
    const float s = 0.75f;
    const std::vector<Vertex> vertices = {
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

    const std::vector<ushort> indices = {
         0,  1,  2,  2,  3,  0, /* front */
         4,  5,  6,  6,  7,  4, /* right */
         8,  9, 10, 10, 11,  8, /* back */
        12, 13, 14, 14, 15, 12, /* left */
        16, 17, 18, 18, 19, 16, /* top */
        20, 21, 22, 22, 23, 20, /* bottom */
    };

    const std::vector<simd::float3> colors = {
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

    return RendererElement(device, Mesh(vertices, indices), Colors(colors), Pipeline::BuildGeneral(device));
}

RendererElement::RendererElement() {}

RendererElement::RendererElement(MTL::Device* device, Mesh mesh, Colors colors, MTL::RenderPipelineState* pipeline):
    Mesh(mesh),
    Colors(colors)
{
    update(device);
    setPipeline(pipeline);
}

RendererElement::RendererElement(RendererElement&& other) noexcept:
    Mesh(std::move(other)),
    Colors(std::move(other))
{
    if (vertexBuffer) {
        vertexBuffer->release();
    }
    if (other.vertexBuffer) {
        vertexBuffer = other.vertexBuffer->retain();
        other.vertexBuffer->release();
    }
    if (indexBuffer) {
        indexBuffer->release();
    }
    if (other.indexBuffer) {
        indexBuffer = other.indexBuffer->retain();
        other.indexBuffer->release();
    }
    if (pipeline) {
        pipeline->release();
    }
    if (other.pipeline) {
        pipeline = other.pipeline->retain();
        other.pipeline->release();
    }

    other.vertexBuffer = nullptr;
    other.indexBuffer = nullptr;
    other.pipeline = nullptr;
}

RendererElement::~RendererElement() {
    if (vertexBuffer) {
        vertexBuffer->release();
    }
    if (indexBuffer) {
        indexBuffer->release();
    }
    if (pipeline) {
        pipeline->release();
    }
}

void RendererElement::update(MTL::Device* device) {
    std::vector<CompleteVertex> tosend;
    CompleteVertex tmp;

    // if (vertexBuffer) {
    //     vertexBuffer->release();
    // }
    // if (indexBuffer) {
    //     indexBuffer->release();
    // }

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
    this->pipeline = pipeline->retain();
}

MTL::Buffer* RendererElement::getVertexBuffer() const {
    return vertexBuffer;
}

MTL::Buffer* RendererElement::getIndexBuffer() const {
    return indexBuffer;
}
