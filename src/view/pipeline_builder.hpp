#ifndef PIPELINE_FACTORY_HPP
#define PIPELINE_FACTORY_HPP

#include <Metal/Metal.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

class PipelineBuilder {
    public:
        PipelineBuilder(MTL::Device* device);
        ~PipelineBuilder();
        void setFilename(const char* filename);
        void setVertexEntryPoint(const char* entryPoint);
        void setFragmentEntryPoint(const char* entryPoint);
        void setVertexDescriptor(MTL::VertexDescriptor* descriptor);
        MTL::RenderPipelineState* build();

    private:
        const char* filename, *vertexEntryPoint, *fragmentEntryPoint;
        MTL::VertexDescriptor* vertexDescriptor = nullptr;
        MTL::Device* device;

};

#endif /* PIPELINE_FACTORY_HPP */
