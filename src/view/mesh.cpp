#include "view/mesh.hpp"

MTL::VertexDescriptor* Mesh::vertexDescriptor = nullptr;

struct Vertex {
    simd::float3 pos;   //(x,y,z)
    simd::float3 normal; //(x,y,z)
    simd::float3 color; //(r,g,b)
};

MTL::VertexDescriptor* Mesh::buildVertexDescriptor() {

    if (vertexDescriptor) return vertexDescriptor;

    vertexDescriptor = MTL::VertexDescriptor::alloc()->init();

    auto attributes = vertexDescriptor->attributes();

    auto positionDescriptor = attributes->object(0);
    positionDescriptor->setFormat(MTL::VertexFormat::VertexFormatFloat3);
    positionDescriptor->setBufferIndex(0);
    positionDescriptor->setOffset(0);

    auto normalDescriptor = attributes->object(1);
    normalDescriptor->setFormat(MTL::VertexFormat::VertexFormatFloat3);
    normalDescriptor->setBufferIndex(0);
    normalDescriptor->setOffset(4 * sizeof(float));

    auto colorDescriptor = attributes->object(2);
    colorDescriptor->setFormat(MTL::VertexFormat::VertexFormatFloat3);
    colorDescriptor->setBufferIndex(0);
    colorDescriptor->setOffset(8 * sizeof(float));

    auto layoutDescriptor = vertexDescriptor->layouts()->object(0);
    layoutDescriptor->setStride(12 * sizeof(float));

    return vertexDescriptor;
}

void Mesh::releaseVertexDescriptor() {
    if (vertexDescriptor) {
        vertexDescriptor->release();
        vertexDescriptor = nullptr;
    }
}

Mesh Mesh::buildQuad(MTL::Device* device) {
    Mesh mesh;

    Vertex vertices[4] = {
        {{-0.75f, -0.75f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.75f, -0.75f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.75f,  0.75f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.75f,  0.75f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}
    };

    ushort indices[6] = {0, 1, 2, 2, 3, 0};
    
    mesh.vertexBuffer = device->newBuffer(4 * sizeof(Vertex), MTL::ResourceStorageModeShared);
    memcpy(mesh.vertexBuffer->contents(), vertices, 4 * sizeof(Vertex));
    
    mesh.indexBuffer = device->newBuffer(6 * sizeof(indices), MTL::ResourceStorageModeShared);
    memcpy(mesh.indexBuffer->contents(), indices, 6 * sizeof(indices));
    
    return mesh;
}

Mesh Mesh::buildCube(MTL::Device* device) {
    Mesh mesh;

    const float s = 0.75f;
    Vertex vertices[24] = {
        { { -s, -s, +s }, { 0.f,  0.f,  1.f }, { 0.f,  0.f,  1.f } },
        { { +s, -s, +s }, { 0.f,  0.f,  1.f }, { 0.f,  0.f,  1.f } },
        { { +s, +s, +s }, { 0.f,  0.f,  1.f }, { 0.f,  0.f,  1.f } },
        { { -s, +s, +s }, { 0.f,  0.f,  1.f }, { 0.f,  0.f,  1.f } },

        { { +s, -s, +s }, { 1.f,  0.f,  0.f }, { 0.f,  1.f,  0.f } },
        { { +s, -s, -s }, { 1.f,  0.f,  0.f }, { 0.f,  1.f,  0.f } },
        { { +s, +s, -s }, { 1.f,  0.f,  0.f }, { 0.f,  1.f,  0.f } },
        { { +s, +s, +s }, { 1.f,  0.f,  0.f }, { 0.f,  1.f,  0.f } },

        { { +s, -s, -s }, { 0.f,  0.f, -1.f }, { 0.f,  1.f,  1.f } },
        { { -s, -s, -s }, { 0.f,  0.f, -1.f }, { 0.f,  1.f,  1.f } },
        { { -s, +s, -s }, { 0.f,  0.f, -1.f }, { 0.f,  1.f,  1.f } },
        { { +s, +s, -s }, { 0.f,  0.f, -1.f }, { 0.f,  1.f,  1.f } },

        { { -s, -s, -s }, { -1.f, 0.f,  0.f }, { 1.f,  0.f,  1.f } },
        { { -s, -s, +s }, { -1.f, 0.f,  0.f }, { 1.f,  0.f,  1.f } },
        { { -s, +s, +s }, { -1.f, 0.f,  0.f }, { 1.f,  0.f,  1.f } },
        { { -s, +s, -s }, { -1.f, 0.f,  0.f }, { 1.f,  0.f,  1.f } },

        { { -s, +s, +s }, { 0.f,  1.f,  0.f }, { 1.f,  0.f,  0.f } },
        { { +s, +s, +s }, { 0.f,  1.f,  0.f }, { 1.f,  0.f,  0.f } },
        { { +s, +s, -s }, { 0.f,  1.f,  0.f }, { 1.f,  0.f,  0.f } },
        { { -s, +s, -s }, { 0.f,  1.f,  0.f }, { 1.f,  0.f,  0.f } },

        { { -s, -s, -s }, { 0.f, -1.f,  0.f }, { 1.f,  1.f,  0.f } },
        { { +s, -s, -s }, { 0.f, -1.f,  0.f }, { 1.f,  1.f,  0.f } },
        { { +s, -s, +s }, { 0.f, -1.f,  0.f }, { 1.f,  1.f,  0.f } },
        { { -s, -s, +s }, { 0.f, -1.f,  0.f }, { 1.f,  1.f,  0.f } }
    };

    ushort indices[36] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    mesh.vertexBuffer = device->newBuffer(24 * sizeof(Vertex), MTL::ResourceStorageModeShared);
    memcpy(mesh.vertexBuffer->contents(), vertices, 24 * sizeof(Vertex));
    
    mesh.indexBuffer = device->newBuffer(36 * sizeof(indices), MTL::ResourceStorageModeShared);
    memcpy(mesh.indexBuffer->contents(), indices, 36 * sizeof(indices));

    return mesh;
}

Mesh::~Mesh() {
    /* TODO: Why is the destructor called in buildMeshes() */
    if (!vertexBuffer) vertexBuffer->release();
    if (!indexBuffer) indexBuffer->release();
}

MTL::Buffer* Mesh::getVertexBuffer() {
    return vertexBuffer;
}

MTL::Buffer* Mesh::getIndexBuffer() {
    return indexBuffer;
}
