#ifndef SCNE_ELEMENT_HPP
#define SCNE_ELEMENT_HPP

#include <Metal/Metal.hpp>
#include <simd/simd.h>
#include "view/renderer_element.hpp"
#include "model/mtlm.hpp"
#include "model/movement.hpp"


class SceneElement : public Movement {

    public:
        SceneElement(MTL::Device* device);
        SceneElement(SceneElement&& other) noexcept;
        ~SceneElement();

        void setRendererElement(RendererElement *rendererElement);
        RendererElement* getRendererElement();

        void setScale(simd::float3 dRatios);
        void scale(simd::float3 dRatios);

        MTL::Buffer* getBufferPositionTransform();
        MTL::Buffer* getBufferNormalTransform();

    private:
        RendererElement *rendererElement;
        simd::float4x4 scaleMatrix;
        MTL::Buffer *bufferPositionTransform, *bufferNormalTransform;

};

#endif /* SCNE_ELEMENT_HPP */
