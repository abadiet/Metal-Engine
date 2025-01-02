#include "view/renderer_element.hpp"

RendererElement RendererElement::BuildSquare(MTL::Device* device) {
    const std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}}
    };

    const std::vector<ushort> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
    };

    const std::vector<simd::float3> colors = {
        simd::float3{0.5f, 0.5f, 0.5f}
    };

    return RendererElement(device, Mesh(vertices, indices), Colors(colors), nullptr, {}, Pipeline::BuildGeneral(device));
}

RendererElement RendererElement::BuildCube(MTL::Device* device) {
    const std::vector<Vertex> vertices = {
        { { -0.5f, -0.5f, 0.5f }, { 0.0f,  0.0f,  1.0f } },
        { { 0.5f, -0.5f, 0.5f }, { 0.0f,  0.0f,  1.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 0.0f,  0.0f,  1.0f } },
        { { -0.5f, 0.5f, 0.5f }, { 0.0f,  0.0f,  1.0f } },

        { { 0.5f, -0.5f, 0.5f }, { 1.0f,  0.0f,  0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f } },
        { { 0.5f, 0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 1.0f,  0.0f,  0.0f } },

        { { 0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { { -0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { { -0.5f, 0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { { 0.5f, 0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },

        { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f,  0.0f } },
        { { -0.5f, -0.5f, 0.5f }, { -1.0f, 0.0f,  0.0f } },
        { { -0.5f, 0.5f, 0.5f }, { -1.0f, 0.0f,  0.0f } },
        { { -0.5f, 0.5f, -0.5f }, { -1.0f, 0.0f,  0.0f } },

        { { -0.5f, 0.5f, 0.5f }, { 0.0f,  1.0f,  0.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 0.0f,  1.0f,  0.0f } },
        { { 0.5f, 0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f } },
        { { -0.5f, 0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f } },

        { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f } },
        { { 0.5f, -0.5f, 0.5f }, { 0.0f, -1.0f,  0.0f } },
        { { -0.5f, -0.5f, 0.5f }, { 0.0f, -1.0f,  0.0f } }
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
        simd::float3{ 1.0f,  0.0f,  1.0f },
        simd::float3{ 0.0f,  1.0f,  1.0f },
        simd::float3{ 1.0f,  0.0f,  0.0f },
        simd::float3{ 0.0f,  1.0f,  0.0f },

        simd::float3{ 0.0f,  1.0f,  0.0f },
        simd::float3{ 0.0f,  1.0f,  0.0f },
        simd::float3{ 0.0f,  1.0f,  0.0f },
        simd::float3{ 0.0f,  1.0f,  0.0f },

        simd::float3{ 0.0f,  1.0f,  1.0f },
        simd::float3{ 0.0f,  1.0f,  1.0f },
        simd::float3{ 0.0f,  1.0f,  1.0f },
        simd::float3{ 0.0f,  1.0f,  1.0f },

        simd::float3{ 1.0f,  0.0f,  1.0f },
        simd::float3{ 1.0f,  0.0f,  1.0f },
        simd::float3{ 1.0f,  0.0f,  1.0f },
        simd::float3{ 1.0f,  0.0f,  1.0f },

        simd::float3{ 1.0f,  0.0f,  0.0f },
        simd::float3{ 1.0f,  0.0f,  0.0f },
        simd::float3{ 1.0f,  0.0f,  0.0f },
        simd::float3{ 1.0f,  0.0f,  0.0f },

        simd::float3{ 1.0f,  1.0f,  0.0f },
        simd::float3{ 1.0f,  1.0f,  0.0f },
        simd::float3{ 1.0f,  1.0f,  0.0f },
        simd::float3{ 1.0f,  1.0f,  0.0f }
    };

    const std::vector<simd::float2> texCoords = {
        simd::float2{0.0f, 0.0f},
        simd::float2{1.0f, 0.0f},
        simd::float2{1.0f, 1.0f},
        simd::float2{0.0f, 1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f}
    };

    return RendererElement(device, Mesh(vertices, indices), Colors(colors), Texture::Build(device, "../textures/abadiet.jpg"), texCoords, Pipeline::BuildGeneral(device));
}

RendererElement::RendererElement() {
    vertexBuffer = nullptr;
    indexBuffer = nullptr;
    pipeline = nullptr;
    texture = nullptr;
}

RendererElement::RendererElement(MTL::Device* device, Mesh mesh, Colors colors, MTL::Texture *texture, std::vector<simd::float2> texCoords, MTL::RenderPipelineState* pipeline):
    Mesh(mesh),
    Colors(colors)
{
    this->texCoords = texCoords;
    vertexBuffer = nullptr;
    indexBuffer = nullptr;
    if (texture) {
        this->texture = texture->retain();
    } else {
        this->texture = nullptr;
    }
    update(device);
    setPipeline(pipeline);
}

RendererElement::RendererElement(RendererElement&& other) noexcept:
    Mesh(std::move(other)),
    Colors(std::move(other))
{
    texCoords = std::move(other.texCoords);
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
    if (texture) {
        texture->release();
    }
    if (other.texture) {
        texture = other.texture->retain();
        other.texture->release();
    }

    other.vertexBuffer = nullptr;
    other.indexBuffer = nullptr;
    other.pipeline = nullptr;
    other.texture = nullptr;
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
    if (texture) {
        texture->release();
    }
}

void RendererElement::update(MTL::Device* device) {
    std::vector<CompleteVertex> tosend;
    CompleteVertex tmp;
    size_t i;

    if (vertexBuffer) {
        vertexBuffer->release();
    }
    if (indexBuffer) {
        indexBuffer->release();
    }

    auto colors = getColors();
    auto indices = getIndices();
    auto vertices = getVertices();

    if (
        colors.size() == 0 ||
        indices.size() == 0 ||
        vertices.size() == 0
    ) {
        throw std::runtime_error("RendererElement::update: invalid data");
    }

    for (i = 0; i < vertices.size(); i++) {
        tmp.vertex = vertices[i];
        tmp.color = colors[i % colors.size()];
        if (texCoords.size() == 0) {
            tmp.texCoord = {-0.5f, -0.5f};
        } else {
            tmp.texCoord = texCoords[i % texCoords.size()];
        }
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

MTL::Texture* RendererElement::getTexture() const {
    return texture;
}
