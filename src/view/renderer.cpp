#include "view/renderer.hpp"

Renderer::Renderer(MTL::Device* device):
    scene(new Scene()),
    device(device->retain())
{
    commandQueue = device->newCommandQueue();
    buildMeshes();
    buildShaders();
    buildDepthStencilState();

    const size_t camId = scene->add_camera();
    scene->get_camera(camId)->set_position({0.0f, 0.0f, 0.0f});
    scene->get_camera(camId)->set_orientation({0.0f, 0.0f, 0.0f});
    scene->get_camera(camId)->set_projection(45.0f, 4.0f / 3.0f, 0.1f, 10.0f);

    const size_t objId = scene->add_object();
    scene->get_object(objId)->set_mesh(&meshes[1]);
    scene->get_object(objId)->set_scale({0.1f, 0.1f, 0.1f});
    scene->get_object(objId)->set_orientation({0.0f, 0.0f, 0.5f});
    scene->get_object(objId)->set_position({0.5f, 0.5f, 2.0f});

    const size_t objId2 = scene->add_object();
    scene->get_object(objId2)->set_mesh(&meshes[1]);
    scene->get_object(objId2)->set_position({0.0f, 0.0f, 3.0f});

}

Renderer::~Renderer() {
    Mesh::releaseVertexDescriptor();
    depthStencilState->release();
    generalPipeline->release();
    commandQueue->release();
    device->release();
    delete scene;
}

void Renderer::buildMeshes() {
    meshes.push_back(Mesh::buildQuad(device));
    meshes.push_back(Mesh::buildCube(device));
}

void Renderer::buildShaders() {
    PipelineBuilder builder(device);

    builder.set_vertex_descriptor(Mesh::buildVertexDescriptor());
    builder.set_filename("../shaders/general.metal");
    builder.set_vertex_entry_point("vertexMainGeneral");
    builder.set_fragment_entry_point("fragmentMainGeneral");
    generalPipeline = builder.build();
}

void Renderer::buildDepthStencilState() {
    MTL::DepthStencilDescriptor* pDsDesc = MTL::DepthStencilDescriptor::alloc()->init();
    pDsDesc->setDepthCompareFunction(MTL::CompareFunction::CompareFunctionLess);
    pDsDesc->setDepthWriteEnabled(true);

    depthStencilState = device->newDepthStencilState(pDsDesc);

    pDsDesc->release();
}

void Renderer::draw(MTK::View* view) {

    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* commandBuffer = commandQueue->commandBuffer();
    MTL::RenderPassDescriptor* renderPass = view->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* encoder = commandBuffer->renderCommandEncoder(renderPass);

    scene->get_camera(0)->mvmt_circle({0.0f, 0.0f, 3.0f}, {0.0f, 1.0f, 0.0f}, 0.05f);
    simd::float4x4 view_cam = scene->get_camera(0)->view_matrix();
    encoder->setVertexBytes(&view_cam, sizeof(view_cam), 2);

    encoder->setRenderPipelineState(generalPipeline);
    encoder->setDepthStencilState(depthStencilState);
    // encoder->setCullMode(MTL::CullModeBack);
    // encoder->setFrontFacingWinding(MTL::Winding::WindingCounterClockwise);

    for (size_t i = 0; i < scene->get_object_count(); i++) {
        const auto object = scene->get_object(i);
        simd::float4x4 transform = object->get_transform();
        encoder->setVertexBytes(&transform, sizeof(transform), 1);
        encoder->setVertexBuffer(object->getMesh()->getVertexBuffer(), 0, 0);
        encoder->drawIndexedPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, object->getMesh()->getIndexCount(), MTL::IndexType::IndexTypeUInt16, object->getMesh()->getIndexBuffer(), 0);
    }

    encoder->endEncoding();
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();

    pool->release();
}
