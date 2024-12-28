#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <simd/simd.h>
#include "model/mtlm.hpp"
#include "model/movement.hpp"


class Camera : public Movement {

    public:
        Camera();
        ~Camera();

        void setProjection(float fovy, float aspect, float near, float far);

        simd::float4x4 viewMatrix();

    private:
        simd::float4x4 projectionMatrix;

};

#endif /* CAMERA_HPP */
