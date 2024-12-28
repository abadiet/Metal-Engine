#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <simd/simd.h>
#include "mtlm.hpp"


class Camera {

    public:
        Camera();
        ~Camera();

        void set_position(simd::float3 position);
        void set_rotation(simd::float3 rotation);
        void set_projection(float fovy, float aspect, float near, float far);
        simd::float4x4 view_matrix();

    private:
        simd::float4x4 translation_matrix;
        simd::float4x4 rotation_matrix;
        simd::float4x4 projection_matrix;

};

#endif /* CAMERA_HPP */
