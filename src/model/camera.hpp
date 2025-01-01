#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Metal/Metal.hpp>
#include <simd/simd.h>
#include "model/mtlm.hpp"
#include "model/movement.hpp"


class Camera : public Movement {

    public:
        Camera(MTL::Device* device);
        Camera(Camera&& other) noexcept;
        ~Camera();

        void setProjection(float fovy, float aspect, float near, float far);

        MTL::Buffer* getBuffer();

    private:
        simd::float4x4 projectionMatrix;
        MTL::Buffer *buffer;

};

#endif /* CAMERA_HPP */
