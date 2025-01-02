#ifndef RENDERER_Element_HPP
#define RENDERER_Element_HPP

#include <Metal/Metal.hpp>
#include "view/mesh.hpp"
#include "view/texture.hpp"
#include "view/colors.hpp"
#include "view/pipeline.hpp"


class RendererElement : public Mesh, public Colors {

    public:
        static RendererElement BuildSquare(MTL::Device* device);
        static RendererElement BuildCube(MTL::Device* device);

        RendererElement();
        RendererElement(MTL::Device* device, Mesh mesh, Colors colors, MTL::Texture *texture, std::vector<simd::float2> texCoords, MTL::RenderPipelineState* pipeline);
        RendererElement(RendererElement&&) noexcept;

        ~RendererElement();


        void update(MTL::Device* device);

        MTL::RenderPipelineState* getPipeline() const;
        void setPipeline(MTL::RenderPipelineState* pipeline);

        MTL::Buffer* getVertexBuffer() const;
        MTL::Buffer* getIndexBuffer() const;
        MTL::Texture* getTexture() const;

    private:
        struct CompleteVertex {
            Mesh::Vertex vertex;
            simd::float3 color;
            simd::float2 texCoord;
        };

        MTL::Buffer *vertexBuffer, *indexBuffer;
        MTL::RenderPipelineState *pipeline;
        MTL::Texture *texture;
        std::vector<simd::float2> texCoords;

};

#endif /* RENDERER_Element_HPP */
