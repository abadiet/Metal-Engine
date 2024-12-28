#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <simd/simd.h>
#include "model/mtlm.hpp"


class Movement {

    public:
        Movement();
        ~Movement();

        void set_position(simd::float3 position);
        void set_orientation(simd::float3 orientation);

        void translate(simd::float3 dPos);
        void rotate(simd::float3 dAngles);

        simd::float4x4 get_movement_matrix();

    private:
        simd::float4x4 translation_matrix;
        simd::float4x4 rotation_matrix;

};

#endif /* MOVEMENT_HPP */
