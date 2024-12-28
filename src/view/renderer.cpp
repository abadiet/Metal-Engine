#include "view/renderer.hpp"

Renderer::Renderer(MTL::Device* device):
    scene(new Scene()),
    device(device->retain())
{
    commandQueue = device->newCommandQueue();
    buildMeshes();
    buildShaders();
    buildDepthStencilState();

    const size_t camId = scene->addCamera();
    scene->getCamera(camId)->setPosition({0.0f, 0.0f, 0.0f});
    scene->getCamera(camId)->setOrientation({0.0f, 0.0f, 0.0f});
    scene->getCamera(camId)->setProjection(45.0f, 4.0f / 3.0f, 0.1f, 10.0f);

    const size_t objId = scene->addObject();
    scene->getObject(objId)->setMesh(&meshes[1]);
    scene->getObject(objId)->setScale({0.1f, 0.1f, 0.1f});
    scene->getObject(objId)->setOrientation({0.0f, 0.0f, 0.5f});
    scene->getObject(objId)->setPosition({0.5f, 0.5f, 2.0f});

    const size_t objId2 = scene->addObject();
    scene->getObject(objId2)->setMesh(&meshes[1]);
    scene->getObject(objId2)->setPosition({0.0f, 0.0f, 3.0f});

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

    builder.setVertexDescriptor(Mesh::buildVertexDescriptor());
    builder.setFilename("../shaders/general.metal");
    builder.setVertexEntryPoint("vertexMainGeneral");
    builder.setFragmentEntryPoint("fragmentMainGeneral");
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

    scene->getCamera(0)->mvmtCircle({0.0f, 0.0f, 3.0f}, {0.0f, 1.0f, 0.0f}, 0.05f);
    simd::float4x4 viewCam = scene->getCamera(0)->viewMatrix();
    encoder->setVertexBytes(&viewCam, sizeof(viewCam), 2);

    encoder->setRenderPipelineState(generalPipeline);
    encoder->setDepthStencilState(depthStencilState);
    encoder->setCullMode(MTL::CullModeFront);
    encoder->setFrontFacingWinding(MTL::Winding::WindingCounterClockwise);

    for (size_t i = 0; i < scene->getObjectCount(); i++) {
        const auto object = scene->getObject(i);
        simd::float4x4 transform = object->getTransform();
        encoder->setVertexBytes(&transform, sizeof(transform), 1);
        encoder->setVertexBuffer(object->getMesh()->getVertexBuffer(), 0, 0);
        encoder->drawIndexedPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, object->getMesh()->getIndexCount(), MTL::IndexType::IndexTypeUInt16, object->getMesh()->getIndexBuffer(), 0);
    }

    encoder->endEncoding();
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();

    pool->release();
}
