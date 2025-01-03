#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <Metal/Metal.hpp>
#include <fstream>
#include <sstream>
#include <vector>


class Pipeline {

    public:
        static MTL::RenderPipelineState* Build(MTL::Device* device, const char* filename, const char* vertexEntry, const char* fragmentEntry, MTL::VertexDescriptor* descriptor);
        static MTL::RenderPipelineState* BuildGeneral(MTL::Device* device);
        static void Release();

        Pipeline(const Pipeline&);
        Pipeline(Pipeline&& other) noexcept;

        ~Pipeline();

    private:
        Pipeline();

        static std::vector<Pipeline> pipelines;

        std::string filename, vertexEntry, fragmentEntry;
        MTL::RenderPipelineState *pipeline;

};

#endif /* PIPELINE_HPP */
