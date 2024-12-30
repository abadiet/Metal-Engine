#include "view/renderer.hpp"

Renderer::Renderer(MTL::Device* device):
    MTK::ViewDelegate(),
    scene(new Scene()),
    device(device->retain())
{
    commandQueue = device->newCommandQueue();
    buildMeshes();
    buildDepthStencilState();

    const size_t camId = scene->addCamera();
    scene->getCamera(camId)->setPosition({0.0f, 1.5f, 0.0f});
    scene->getCamera(camId)->setOrientation({-0.5f, 0.0f, 0.0f});
    scene->getCamera(camId)->setProjection(45.0f, 4.0f / 3.0f, 0.1f, 10.0f);

    size_t objId = scene->addElement();
    scene->getElement(objId)->setRendererElement(&elements[1]);
    scene->getElement(objId)->setScale({0.05f, 0.05f, 0.05f});
    scene->getElement(objId)->setOrientation({0.0f, 2.0f, 0.5f});
    scene->getElement(objId)->setPosition({0.5f, 0.5f, 2.0f});

    objId = scene->addElement();
    scene->getElement(objId)->setRendererElement(&elements[1]);
    scene->getElement(objId)->setScale({0.05f, 0.05f, 0.05f});
    scene->getElement(objId)->setPosition({0.0f, 0.5f, 4.0f});

    objId = scene->addElement();
    scene->getElement(objId)->setRendererElement(&elements[1]);
    scene->getElement(objId)->setScale({0.5f, 0.5f, 0.5f});
    scene->getElement(objId)->setPosition({0.0f, 0.0f, 3.0f});

}

Renderer::~Renderer() {
    depthStencilState->release();
    commandQueue->release();
    device->release();
    delete scene;
}

void Renderer::buildMeshes() {
    elements.push_back(RendererElement::BuildSquare(device));
    elements.push_back(RendererElement::BuildCube(device));
}

void Renderer::buildDepthStencilState() {
    MTL::DepthStencilDescriptor* pDsDesc = MTL::DepthStencilDescriptor::alloc()->init();
    pDsDesc->setDepthCompareFunction(MTL::CompareFunction::CompareFunctionLess);
    pDsDesc->setDepthWriteEnabled(true);

    depthStencilState = device->newDepthStencilState(pDsDesc);

    pDsDesc->release();
}

void Renderer::drawInMTKView(MTK::View* view) {

    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* commandBuffer = commandQueue->commandBuffer();
    MTL::RenderPassDescriptor* renderPass = view->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* encoder = commandBuffer->renderCommandEncoder(renderPass);

    scene->getCamera(0)->mvmtCircle({0.0f, 1.5f, 3.0f}, {0.0f, 1.0f, 0.0f}, 0.05f);
    simd::float4x4 viewCam = scene->getCamera(0)->viewMatrix();
    encoder->setVertexBytes(&viewCam, sizeof(viewCam), 2);

    encoder->setDepthStencilState(depthStencilState);
    encoder->setCullMode(MTL::CullModeFront);
    encoder->setFrontFacingWinding(MTL::Winding::WindingCounterClockwise);

    scene->getElement(0)->rotate({0.02f, 0.01f, 0.03f});
    scene->getElement(0)->mvmtCircle({0.0f, 0.0f, 3.0f}, {1.0f, 0.0f, 1.0f}, 0.03f);

    scene->getElement(1)->rotate({0.02f, 0.01f, 0.03f});
    scene->getElement(1)->mvmtCircle({0.0f, 0.0f, 3.0f}, {1.0f, 1.0f, 1.0f}, 0.03f);

    for (size_t i = 0; i < scene->getElementCount(); i++) {
        const auto element = scene->getElement(i);
        const auto rendererElement = element->getRendererElement();
        encoder->setRenderPipelineState(rendererElement->getPipeline());
        simd::float4x4 transform = element->getTransform();
        encoder->setVertexBytes(&transform, sizeof(transform), 1);
        encoder->setVertexBuffer(rendererElement->getVertexBuffer(), 0, 0);
        encoder->drawIndexedPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, rendererElement->getIndices().size(), MTL::IndexType::IndexTypeUInt16, rendererElement->getIndexBuffer(), 0);
    }

    encoder->endEncoding();
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();

    pool->release();
}
