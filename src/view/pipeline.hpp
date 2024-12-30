#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <Metal/Metal.hpp>
#include <fstream>
#include <sstream>
#include <vector>


/* TODO: Pipelines are never freed as well as VertexDescriptor */

class Pipeline {

    public:
        static MTL::RenderPipelineState* Build(MTL::Device* device, const char* filename, const char* vertexEntry, const char* fragmentEntry, MTL::VertexDescriptor* descriptor);
        static MTL::RenderPipelineState* BuildGeneral(MTL::Device* device);

        ~Pipeline();

    private:
        Pipeline();

        static std::vector<Pipeline> pipelines;

        std::string filename, vertexEntry, fragmentEntry;
        MTL::RenderPipelineState *pipeline;

};

#endif /* PIPELINE_HPP */
