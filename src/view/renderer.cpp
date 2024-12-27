#include "view/renderer.hpp"

Renderer::Renderer(MTL::Device* device):
    device(device->retain())
{
    commandQueue = device->newCommandQueue();
    buildMeshes();
    buildShaders();
}

Renderer::~Renderer() {
    triangleMesh->release();
    quadMesh.vertexBuffer->release();
    quadMesh.indexBuffer->release();
    trianglePipeline->release();
    generalPipeline->release();
    commandQueue->release();
    device->release();
}

void Renderer::buildMeshes() {
    triangleMesh = MeshFactory::buildTriangle(device);
    quadMesh = MeshFactory::buildQuad(device);
}

void Renderer::buildShaders() {
    PipelineBuilder builder(device);

    builder.set_vertex_descriptor(quadMesh.vertexDescriptor);

    builder.set_filename("../shaders/triangle.metal");
    builder.set_vertex_entry_point("vertexMain");
    builder.set_fragment_entry_point("fragmentMain");
    trianglePipeline = builder.build();

    builder.set_filename("../shaders/general.metal");
    builder.set_vertex_entry_point("vertexMainGeneral");
    builder.set_fragment_entry_point("fragmentMainGeneral");
    generalPipeline = builder.build();
}

void Renderer::draw(MTK::View* view) {

    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* commandBuffer = commandQueue->commandBuffer();
    MTL::RenderPassDescriptor* renderPass = view->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* encoder = commandBuffer->renderCommandEncoder(renderPass);
    
    encoder->setRenderPipelineState(generalPipeline);
    simd::float4x4 projection = mtlm::perspective_projection(45.0f, 4.0f / 3.0f, 0.1f, 10.0f);
    encoder->setVertexBytes(&projection, sizeof(projection), 2);

    simd::float4x4 transform = mtlm::translation({0.0f, 0.0f, 3.0f});
    encoder->setVertexBytes(&transform, sizeof(transform), 1);
    encoder->setVertexBuffer(quadMesh.vertexBuffer, 0, 0);
    encoder->drawIndexedPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, 6, MTL::IndexType::IndexTypeUInt16, quadMesh.indexBuffer, 0, 6);

    transform = mtlm::translation({0.5f, 0.5f, 2.0f}) * mtlm::z_rotation(0.5f) * mtlm::scale(0.1f);
    encoder->setVertexBytes(&transform, sizeof(transform), 1);
    encoder->setVertexBuffer(triangleMesh, 0, 0);
    encoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), 3);

    encoder->endEncoding();
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();

    pool->release();
}
