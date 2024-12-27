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
        void set_filename(const char* filename);
        void set_vertex_entry_point(const char* entryPoint);
        void set_fragment_entry_point(const char* entryPoint);
        void set_vertex_descriptor(MTL::VertexDescriptor* descriptor);
        MTL::RenderPipelineState* build();

    private:
        const char* filename, *vertexEntryPoint, *fragmentEntryPoint;
        MTL::VertexDescriptor* vertexDescriptor = nullptr;
        MTL::Device* device;

};

#endif /* PIPELINE_FACTORY_HPP */
