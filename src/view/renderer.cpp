#include "view/renderer.hpp"

Renderer::Renderer(MTL::Device* device):
    MTK::ViewDelegate(),
    scene(new Scene(device)),
    device(device->retain())
{
    size_t id;

    commandQueue = device->newCommandQueue();
    buildMeshes();
    buildDepthStencilState();

    id = scene->addCamera();
    scene->getCamera(id)->setPosition({0.0f, 1.5f, 0.0f});
    scene->getCamera(id)->setOrientation({-0.5f, 0.0f, 0.0f});
    scene->getCamera(id)->setProjection(3.14f / 8.0f, 4.0f / 3.0f, 0.1f, 10.0f);

    id = scene->addLight();
    scene->getLight(id)->setPosition({0.0f, 1.5f, 0.0f});
    scene->getLight(id)->setColor({1.0f, 1.0f, 1.0f});
    scene->getLight(id)->setIntensity(10.0f);

    id = scene->addLight();
    scene->getLight(id)->setPosition({0.0f, 1.5f, 0.0f});
    scene->getLight(id)->setColor({1.0f, 0.1f, 0.1f});
    scene->getLight(id)->setIntensity(10.0f);

    id = scene->addElement();
    scene->getElement(id)->setRendererElement(&elements[1]);
    scene->getElement(id)->setScale({0.05f, 0.05f, 0.05f});
    scene->getElement(id)->setOrientation({0.0f, 2.0f, 0.5f});
    scene->getElement(id)->setPosition({0.5f, 0.5f, 2.0f});

    id = scene->addElement();
    scene->getElement(id)->setRendererElement(&elements[1]);
    scene->getElement(id)->setScale({0.05f, 0.05f, 0.05f});
    scene->getElement(id)->setPosition({0.0f, 0.5f, 4.0f});

    id = scene->addElement();
    scene->getElement(id)->setRendererElement(&elements[1]);
    scene->getElement(id)->setScale({0.5f, 0.5f, 0.5f});
    scene->getElement(id)->setPosition({0.0f, 0.0f, 3.0f});
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
    NS::AutoreleasePool* pool;
    MTL::CommandBuffer* commandBuffer;
    MTL::RenderPassDescriptor* renderPass;
    MTL::RenderCommandEncoder* encoder;
    size_t i;
    int lightCount;
    SceneElement *element;
    RendererElement *rendererElement;

    pool = NS::AutoreleasePool::alloc()->init();

    commandBuffer = commandQueue->commandBuffer();
    renderPass = view->currentRenderPassDescriptor();
    encoder = commandBuffer->renderCommandEncoder(renderPass);

    encoder->setVertexBuffer(scene->getCamera(0)->getBuffer(), 0, 3);

    scene->getLight(0)->mvmtCircle({0.0f, 1.5f, 3.0f}, {0.0f, 1.0f, 0.0f}, 0.05f);
    scene->updateLights();
    encoder->setFragmentBuffer(scene->getBufferLights(), 0, 0);
    lightCount = (int) scene->getLightCount();
    encoder->setFragmentBytes((void*) &lightCount, sizeof(lightCount), 1);

    encoder->setDepthStencilState(depthStencilState);
    encoder->setCullMode(MTL::CullModeFront);
    encoder->setFrontFacingWinding(MTL::Winding::WindingCounterClockwise);

    scene->getElement(0)->rotate({0.02f, 0.01f, 0.03f});
    scene->getElement(0)->mvmtCircle({0.0f, 0.0f, 3.0f}, {1.0f, 0.0f, 1.0f}, 0.03f);

    scene->getElement(1)->rotate({0.02f, 0.01f, 0.03f});
    scene->getElement(1)->mvmtCircle({0.0f, 0.0f, 3.0f}, {1.0f, 1.0f, 1.0f}, 0.03f);

    for (i = 0; i < scene->getElementCount(); i++) {
        element = scene->getElement(i);
        rendererElement = element->getRendererElement();
        encoder->setRenderPipelineState(rendererElement->getPipeline());
        encoder->setVertexBuffer(rendererElement->getVertexBuffer(), 0, 0);
        encoder->setVertexBuffer(element->getBufferPositionTransform(), 0, 1);
        encoder->setVertexBuffer(element->getBufferNormalTransform(), 0, 2);
        encoder->drawIndexedPrimitives(
            MTL::PrimitiveType::PrimitiveTypeTriangle,
            rendererElement->getIndices().size(),
            MTL::IndexType::IndexTypeUInt16,
            rendererElement->getIndexBuffer(),
            0
        );
    }

    encoder->endEncoding();
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();

    pool->release();
}
