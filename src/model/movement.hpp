#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <simd/simd.h>
#include "model/mtlm.hpp"


class Movement {

    public:
        Movement();
        Movement(Movement&& other) noexcept;
        ~Movement();

        void setPosition(simd::float3 position);
        simd::float3 getPosition();

        void setOrientation(simd::float3 orientation);

        void translate(simd::float3 dPos);
        void rotate(simd::float3 dAngles);

        void mvmtCircle(simd::float3 center, simd::float3 axis, float speed);

        simd::float4x4 getMovementMatrix();
        simd::float4x4 getTranslationMatrix();
        simd::float4x4 getRotationMatrix();

    private:
        simd::float4x4 translationMatrix;
        simd::float4x4 rotationMatrix;

};

#endif /* MOVEMENT_HPP */
