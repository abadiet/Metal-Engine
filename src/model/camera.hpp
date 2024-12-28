#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <simd/simd.h>
#include "model/mtlm.hpp"
#include "model/movement.hpp"


class Camera : public Movement {

    public:
        Camera();
        ~Camera();

        void set_projection(float fovy, float aspect, float near, float far);

        simd::float4x4 view_matrix();

    private:
        simd::float4x4 projection_matrix;

};

#endif /* CAMERA_HPP */
