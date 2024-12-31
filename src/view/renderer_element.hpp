#ifndef RENDERER_Element_HPP
#define RENDERER_Element_HPP

#include <Metal/Metal.hpp>
#include "view/mesh.hpp"
#include "view/texture.hpp"
#include "view/colors.hpp"
#include "view/pipeline.hpp"


class RendererElement : public Mesh/*, public Texture*/, public Colors {

    public:
        static RendererElement BuildSquare(MTL::Device* device);
        static RendererElement BuildCube(MTL::Device* device);

        RendererElement();
        RendererElement(MTL::Device* device, Mesh mesh, Colors colors, MTL::RenderPipelineState* pipeline);
        RendererElement(RendererElement&&) noexcept;

        ~RendererElement();


        void update(MTL::Device* device);

        MTL::RenderPipelineState* getPipeline() const;
        void setPipeline(MTL::RenderPipelineState* pipeline);

        MTL::Buffer* getVertexBuffer() const;
        MTL::Buffer* getIndexBuffer() const;

    private:
        struct CompleteVertex {
            Mesh::Vertex vertex;
            simd::float3 color;            
        };

        MTL::Buffer *vertexBuffer, *indexBuffer;
        MTL::RenderPipelineState *pipeline;

};

#endif /* RENDERER_Element_HPP */

/*void ***::***(MTL::VertexDescriptor* descriptor) {
    if (this->vertexDescriptor) {
        this->vertexDescriptor->release();
    }
    this->vertexDescriptor = descriptor->retain();
}*/
