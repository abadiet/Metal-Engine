#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "view/mesh.hpp"
#include "view/pipeline_builder.hpp"
#include "model/mtlm.hpp"
#include "model/scene.hpp"


class Renderer {

    public:
        Renderer(MTL::Device* device);
        ~Renderer();
        void buildDepthStencilState();
        void draw(MTK::View* view);

    private:
        void buildMeshes();
        void buildShaders();

        Scene *scene;

        MTL::Device* device;
        MTL::CommandQueue* commandQueue;
        MTL::DepthStencilState* depthStencilState;

        MTL::RenderPipelineState *generalPipeline;
        std::vector<Mesh> meshes;

};

#endif /* RENDERER_HPP */
