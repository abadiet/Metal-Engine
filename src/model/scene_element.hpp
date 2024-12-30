#ifndef SCNE_ELEMENT_HPP
#define SCNE_ELEMENT_HPP

#include <simd/simd.h>
#include "view/renderer_element.hpp"
#include "model/mtlm.hpp"
#include "model/movement.hpp"


class SceneElement : public Movement {

    public:
        SceneElement();
        ~SceneElement();

        void setRendererElement(RendererElement *rendererElement);
        RendererElement* getRendererElement();

        void setScale(simd::float3 dRatios);
        void scale(simd::float3 dRatios);

        simd::float4x4 getTransform();

    private:
        RendererElement *rendererElement;
        simd::float4x4 scaleMatrix;

};

#endif /* SCNE_ELEMENT_HPP */
