#include "view/pipeline.hpp"

std::vector<Pipeline> Pipeline::pipelines;

MTL::RenderPipelineState* Pipeline::Build(MTL::Device* device, const char* filename, const char* vertexEntry, const char* fragmentEntry, MTL::VertexDescriptor* descriptor) {
    std::ifstream file;
    std::stringstream reader;
    std::string raw_string;
    NS::String *sourceCode, *vertexName, *fragmentName;
    NS::Error* error;
    MTL::CompileOptions* options;
    MTL::Library* library;
    MTL::Function *vertexMain, *fragmentMain;
    MTL::RenderPipelineDescriptor* pipelineDescriptor;

    for (const Pipeline& pipeline : pipelines) {
        if (
            pipeline.filename == filename &&
            pipeline.vertexEntry == vertexEntry &&
            pipeline.fragmentEntry == fragmentEntry
        ) {
            return pipeline.pipeline;
        }
    }

    pipelines.push_back(Pipeline());

    pipelines.back().filename = filename;
    pipelines.back().vertexEntry = vertexEntry;
    pipelines.back().fragmentEntry = fragmentEntry;

    file.open(pipelines.back().filename);
    reader << file.rdbuf();
    raw_string = reader.str();
    sourceCode = NS::String::string(raw_string.c_str(), NS::StringEncoding::UTF8StringEncoding);

    error = nullptr;
    options = nullptr;
    library = device->newLibrary(sourceCode, options, &error);
    if (!library) {
        throw std::runtime_error(error->localizedDescription()->utf8String());
    }

    vertexName = NS::String::string(pipelines.back().vertexEntry.c_str(), NS::StringEncoding::UTF8StringEncoding);
    vertexMain = library->newFunction(vertexName);

    fragmentName = NS::String::string(pipelines.back().fragmentEntry.c_str(), NS::StringEncoding::UTF8StringEncoding);
    fragmentMain = library->newFunction(fragmentName);

    pipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    pipelineDescriptor->setVertexFunction(vertexMain);
    pipelineDescriptor->setFragmentFunction(fragmentMain);
    pipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);

    pipelineDescriptor->setVertexDescriptor(descriptor);

    pipelines.back().pipeline = device->newRenderPipelineState(pipelineDescriptor, &error);
    if (!pipelines.back().pipeline) {
        throw std::runtime_error(error->localizedDescription()->utf8String());
    }

    vertexMain->release();
    fragmentMain->release();
    pipelineDescriptor->release();
    library->release();
    file.close();

    return pipelines.back().pipeline;
}

MTL::RenderPipelineState* Pipeline::BuildGeneral(MTL::Device* device) {
    MTL::VertexDescriptor *vertexDescriptor = MTL::VertexDescriptor::alloc()->init();

    auto attributes = vertexDescriptor->attributes();

    auto positionDescriptor = attributes->object(0);
    positionDescriptor->setFormat(MTL::VertexFormat::VertexFormatFloat3);
    positionDescriptor->setBufferIndex(0);
    positionDescriptor->setOffset(0);

    auto normalDescriptor = attributes->object(1);
    normalDescriptor->setFormat(MTL::VertexFormat::VertexFormatFloat3);
    normalDescriptor->setBufferIndex(0);
    normalDescriptor->setOffset(4 * sizeof(float));

    auto colorDescriptor = attributes->object(2);
    colorDescriptor->setFormat(MTL::VertexFormat::VertexFormatFloat3);
    colorDescriptor->setBufferIndex(0);
    colorDescriptor->setOffset(8 * sizeof(float));

    auto layoutDescriptor = vertexDescriptor->layouts()->object(0);
    layoutDescriptor->setStride(12 * sizeof(float));

    return Build(device, "../shaders/general.metal", "vertexMainGeneral", "fragmentMainGeneral", vertexDescriptor);
}

Pipeline::~Pipeline() {}

Pipeline::Pipeline() {}