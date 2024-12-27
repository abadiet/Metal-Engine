#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#include "view/mesh_factory.hpp"
#include "view/pipeline_builder.hpp"
#include "model/mtlm.hpp"


class Renderer {

    public:
        Renderer(MTL::Device* device);
        ~Renderer();
        void buildDepthStencilState();
        void draw(MTK::View* view);

    private:
        void buildMeshes();
        void buildShaders();

        MTL::Device* device;
        MTL::CommandQueue* commandQueue;
        MTL::DepthStencilState* depthStencilState;

        MTL::RenderPipelineState *trianglePipeline, *generalPipeline;
        MTL::Buffer *triangleMesh;
        Mesh quadMesh;

};

#endif /* RENDERER_HPP */
