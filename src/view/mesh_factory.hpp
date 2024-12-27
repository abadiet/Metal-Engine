#ifndef MESH_FACTORY_HPP
#define MESH_FACTORY_HPP

#include <MetalKit/MetalKit.hpp>
#include <simd/simd.h>


struct Vertex {
    simd::float3 pos;   //(x,y,z)
    simd::float3 color; //(r,g,b)
};

struct Mesh {
    MTL::Buffer* vertexBuffer, *indexBuffer;
    MTL::VertexDescriptor* vertexDescriptor;
};

namespace MeshFactory {
    MTL::Buffer* buildTriangle(MTL::Device* device);
    Mesh buildQuad(MTL::Device* device);
}

#endif /* MESH_FACTORY_HPP */
