#ifndef MESH_FACTORY_HPP
#define MESH_FACTORY_HPP

#include <Metal/Metal.hpp>
#include <simd/simd.h>


class Mesh {
    public:
        static Mesh buildQuad(MTL::Device* device);
        static Mesh buildCube(MTL::Device* device);
        static MTL::VertexDescriptor* buildVertexDescriptor();
        static void releaseVertexDescriptor();

        ~Mesh();
        MTL::Buffer* getVertexBuffer();
        MTL::Buffer* getIndexBuffer();

    private:
        static MTL::VertexDescriptor *vertexDescriptor;

        MTL::Buffer *vertexBuffer, *indexBuffer;
};

#endif /* MESH_FACTORY_HPP */
