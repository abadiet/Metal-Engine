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
        simd::float3 getPosition() const;
        void setOrientation(simd::float3 orientation);

        void translate(simd::float3 dPos, bool relative = false);
        void rotate(simd::float3 dAngles, bool relative = false);

        void mvmtCircle(simd::float3 center, simd::float3 axis, float speed, bool lookAtCenter = false);
        void lookAt(const Movement& target, simd::float3 front);
        void lookAt(const Movement& target, simd::float3 front, simd::float3 selfVec, simd::float3 worldVec);

        simd::float3 World2Relative(simd::float3 worldVec);
        simd::float3 Relative2World(simd::float3 relativeVec);

        simd::float4x4 getMovementMatrix();
        simd::float4x4 getTranslationMatrix();
        simd::float4x4 getRotationMatrix();

    private:
        simd::float4x4 translationMatrix;
        simd::float4x4 rotationMatrix;

};

#endif /* MOVEMENT_HPP */
