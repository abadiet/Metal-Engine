#include "view/renderer.hpp"

Renderer::Renderer(MTL::Device* device):
    MTK::ViewDelegate(),
    scene(new Scene(device)),
    device(device->retain())
{
    size_t id;

    commandQueue = device->newCommandQueue();
    buildRendererElements();
    buildDepthStencilState();

    /* main camera */
    id = scene->addCamera();
    scene->getCamera(id)->setPosition({0.0f, 3.0f, 0.0f});
    scene->getCamera(id)->setProjection(MTLM_PI / 8.0f, 4.0f / 3.0f, 0.1f, 40.0f);

    /* main light */
    id = scene->addLight();
    scene->getLight(id)->setPosition({0.0f, 10.0f, 0.0f});
    scene->getLight(id)->setColor({1.0f, 1.0f, 1.0f});
    scene->getLight(id)->setIntensity(30.0f);

    /* camera light */
    id = scene->addLight();
    scene->getLight(id)->setColor({1.0f, 1.0f, 1.0f});
    scene->getLight(id)->setIntensity(3.0f);

    /* moving lights */
    id = scene->addLight();
    scene->getLight(id)->setPosition({2.0f, 0.01f, 0.0f});
    scene->getLight(id)->setColor({1.0f, 0.0f, 0.0f});
    scene->getLight(id)->setIntensity(3.0f);

    id = scene->addLight();
    scene->getLight(id)->setPosition({-2.0f, 0.01f, 5.0f});
    scene->getLight(id)->setColor({0.0f, 0.0f, 1.0f});
    scene->getLight(id)->setIntensity(3.0f);

    id = scene->addLight();
    scene->getLight(id)->setPosition({3.0f, 0.01f, -4.0f});
    scene->getLight(id)->setColor({0.0f, 1.0f, 0.0f});
    scene->getLight(id)->setIntensity(3.0f);

    /* ground */
    id = scene->addElement();
    scene->getElement(id)->setRendererElement(&elements[0]);
    scene->getElement(id)->setPosition({0.0f, 0.0f, 0.0f});
    scene->getElement(id)->setOrientation({MTLM_PI / 2.0f, 0.0f, 0.0f});
    scene->getElement(id)->setScale({20.0f, 20.0f, 20.0f});

    /* cubes */
    id = scene->addElement();
    scene->getElement(id)->setRendererElement(&elements[1]);
    scene->getElement(id)->setPosition({1.0f, 2.0f, 3.0f});
    scene->getElement(id)->setScale({0.5f, 0.5f, 0.5f});

    id = scene->addElement();
    scene->getElement(id)->setRendererElement(&elements[1]);
    scene->getElement(id)->setPosition({1.0f, 2.0f, 4.0f});
    scene->getElement(id)->setOrientation({0.0f, 2.0f, 0.5f});
    scene->getElement(id)->setScale({0.05f, 0.05f, 0.05f});

    id = scene->addElement();
    scene->getElement(id)->setRendererElement(&elements[1]);
    scene->getElement(id)->setPosition({1.0f, 3.0f, 3.0f});
    scene->getElement(id)->setScale({0.05f, 0.05f, 0.05f});

    /* init */
    scene->getCamera(0)->lookAt(*scene->getElement(1));

    scene->updateLights();
}

Renderer::~Renderer() {
    depthStencilState->release();
    commandQueue->release();
    device->release();
    Pipeline::Release();
    Texture::Release();
    delete scene;
}

void Renderer::buildRendererElements() {
    RendererElement elem;

    /* ground (actually just a colored cube) */
    elem = RendererElement::BuildSquare(device);
    elem.setColors({simd::float3{0.5f, 0.5f, 0.5f}});
    elem.setTexture(Texture::Build(device, "../textures/20x20grid.png"));
    elem.setTextureCoords({
        simd::float2{0.0f, 0.0f},
        simd::float2{1.0f, 0.0f},
        simd::float2{1.0f, 1.0f},
        simd::float2{0.0f, 1.0f}
    });
    elem.update(device);
    elements.push_back(elem);

    /* custom cubes */
    elem = RendererElement::BuildCube(device);
    elem.setTexture(Texture::Build(device, "../textures/abadiet.jpg"));
    elem.setTextureCoords({
        simd::float2{0.0f, 0.0f},
        simd::float2{1.0f, 0.0f},
        simd::float2{1.0f, 1.0f},
        simd::float2{0.0f, 1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f},
        simd::float2{-1.0f, -1.0f}
    });
    elem.setColors({
        simd::float3{ 1.0f,  0.0f,  1.0f },
        simd::float3{ 0.0f,  1.0f,  1.0f },
        simd::float3{ 1.0f,  0.0f,  0.0f },
        simd::float3{ 0.0f,  1.0f,  0.0f },
        simd::float3{ 0.0f,  1.0f,  0.0f },
        simd::float3{ 0.0f,  1.0f,  0.0f },
        simd::float3{ 0.0f,  1.0f,  0.0f },
        simd::float3{ 0.0f,  1.0f,  0.0f },
        simd::float3{ 0.0f,  1.0f,  1.0f },
        simd::float3{ 0.0f,  1.0f,  1.0f },
        simd::float3{ 0.0f,  1.0f,  1.0f },
        simd::float3{ 0.0f,  1.0f,  1.0f },
        simd::float3{ 1.0f,  0.0f,  1.0f },
        simd::float3{ 1.0f,  0.0f,  1.0f },
        simd::float3{ 1.0f,  0.0f,  1.0f },
        simd::float3{ 1.0f,  0.0f,  1.0f },
        simd::float3{ 1.0f,  0.0f,  0.0f },
        simd::float3{ 1.0f,  0.0f,  0.0f },
        simd::float3{ 1.0f,  0.0f,  0.0f },
        simd::float3{ 1.0f,  0.0f,  0.0f },
        simd::float3{ 1.0f,  1.0f,  0.0f },
        simd::float3{ 1.0f,  1.0f,  0.0f },
        simd::float3{ 1.0f,  1.0f,  0.0f },
        simd::float3{ 1.0f,  1.0f,  0.0f }
    });
    elem.update(device);
    elements.push_back(elem);
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

    /* CAMERA */
    scene->getCamera(0)->mvmtCircle({1.0f, 3.0f, 3.0f}, {0.0f, 1.0f, 0.0f}, 0.02f, true);
    // scene->getCamera(0)->lookAt(*scene->getElement(1));

    /* LIGHTS */
    scene->getLight(1)->setPosition(scene->getCamera(0)->getPosition());
    scene->getLight(2)->mvmtCircle({3.0f, 0.01f, 0.0f}, {0.0f, 1.0f, 0.0f}, 0.05f);
    scene->getLight(3)->mvmtCircle({1.0f, 0.01f, 6.0f}, {0.0f, 1.0f, 0.0f}, 0.05f);
    scene->getLight(4)->mvmtCircle({4.0f, 0.01f, 0.0f}, {0.0f, 1.0f, 0.0f}, 0.05f);
    scene->updateLight(1);
    scene->updateLight(2);
    scene->updateLight(3);
    scene->updateLight(4);

    /* ELEMENTS */
    // scene->getElement(1)->lookAt(*scene->getElement(2), simd::float3{0.0f, 0.0f, 1.0f}, simd::float3{0.0f, 1.0f, 0.0f}, simd::float3{0.0f, 1.0f, 0.0f});
    scene->getElement(2)->mvmtCircle({1.0f, 2.0f, 3.0f}, {1.0f, 1.0f, 0.0f}, 0.02f, true);
    scene->getElement(3)->mvmtCircle({1.0f, 2.0f, 3.0f}, {0.0f, 0.4f, 0.3f}, 0.03f);

    /* DRAWING */
    /* mode */
    encoder->setDepthStencilState(depthStencilState);
    encoder->setCullMode(MTL::CullModeFront);
    encoder->setFrontFacingWinding(MTL::Winding::WindingCounterClockwise);
    /* camera */
    encoder->setVertexBuffer(scene->getCamera(0)->getBuffer(), 0, 3);
    /* lights */
    lightCount = (int) scene->getLightCount();
    encoder->setFragmentBytes((void*) &lightCount, sizeof(lightCount), 1);
    encoder->setFragmentBuffer(scene->getBufferLights(), 0, 0);
    /* elements */
    for (i = 0; i < scene->getElementCount(); i++) {
        element = scene->getElement(i);
        rendererElement = element->getRendererElement();
        encoder->setRenderPipelineState(rendererElement->getPipeline());
        encoder->setVertexBuffer(rendererElement->getVertexBuffer(), 0, 0);
        encoder->setVertexBuffer(element->getBufferPositionTransform(), 0, 1);
        encoder->setVertexBuffer(element->getBufferNormalTransform(), 0, 2);
        encoder->setFragmentTexture(rendererElement->getTexture(), 0);
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
