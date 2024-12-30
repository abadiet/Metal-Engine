#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
#include <fstream>
#include <sstream>
#include <vector>

#include "view/renderer_element.hpp"
#include "view/pipeline.hpp"
#include "model/mtlm.hpp"
#include "model/scene.hpp"


/* TODO: mv depth stencil to RendererElement */

class Renderer : public MTK::ViewDelegate {

    public:
        Renderer(MTL::Device* device);
        ~Renderer();
        virtual void drawInMTKView(MTK::View* view) override;

    private:
        void buildMeshes();
        void buildDepthStencilState();

        Scene *scene;

        MTL::Device* device;
        MTL::CommandQueue* commandQueue;
        MTL::DepthStencilState* depthStencilState;

        std::vector<RendererElement> elements;

};

#endif /* RENDERER_HPP */
