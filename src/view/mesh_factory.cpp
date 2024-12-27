#include "view/mesh_factory.hpp"

MTL::Buffer* MeshFactory::buildTriangle(MTL::Device* device) {

    Vertex vertices[3] = {
        {{-0.75f, -0.75f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.75f, -0.75f}, {0.0f, 1.0f, 0.0f}},
        {{  0.0f,  0.75f}, {0.0f, 0.0f, 1.0f}}
    };
    
    MTL::Buffer* buffer = device->newBuffer(3 * sizeof(Vertex), MTL::ResourceStorageModeShared);
    
    memcpy(buffer->contents(), vertices, 3 * sizeof(Vertex));
    
    return buffer;
}

Mesh MeshFactory::buildQuad(MTL::Device* device) {
    Mesh mesh;

    Vertex vertices[4] = {
        {{-0.75f, -0.75f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.75f, -0.75f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.75f,  0.75f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.75f,  0.75f, 0.0f}, {0.0f, 1.0f, 0.0f}}
    };

    ushort indices[6] = {0, 1, 2, 2, 3, 0};
    
    mesh.vertexBuffer = device->newBuffer(4 * sizeof(Vertex), MTL::ResourceStorageModeShared);
    memcpy(mesh.vertexBuffer->contents(), vertices, 4 * sizeof(Vertex));
    
    mesh.indexBuffer = device->newBuffer(6 * sizeof(indices), MTL::ResourceStorageModeShared);
    memcpy(mesh.indexBuffer->contents(), indices, 6 * sizeof(indices));

    MTL::VertexDescriptor* vertexDescriptor = MTL::VertexDescriptor::alloc()->init();
    auto attributes = vertexDescriptor->attributes();
    auto positionDescriptor = attributes->object(0);
    positionDescriptor->setFormat(MTL::VertexFormat::VertexFormatFloat3);
    positionDescriptor->setBufferIndex(0);
    positionDescriptor->setOffset(0);
    auto colorDescriptor = attributes->object(1);
    colorDescriptor->setFormat(MTL::VertexFormat::VertexFormatFloat3);
    colorDescriptor->setBufferIndex(0);
    colorDescriptor->setOffset(4 * sizeof(float));

    auto layoutDescriptor = vertexDescriptor->layouts()->object(0);
    layoutDescriptor->setStride(8 * sizeof(float));

    mesh.vertexDescriptor = vertexDescriptor;
    
    return mesh;
}