#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <Metal/Metal.hpp>
#include <simd/simd.h>
#include "model/movement.hpp"


class Light : public Movement {

    public:
        Light(MTL::Device* device);
        Light(Light&& other) noexcept;
        ~Light();

        void setOrientation(simd::float3 orientation) = delete;
        simd::float3 getOrientation() = delete;

        void setIntensity(float intensity);
        float getIntensity();

        void setColor(simd::float3 color);
        simd::float3 getColor();

        void update();

        MTL::Buffer* getBuffer();

    private:
        struct Light_st {
            simd::float3 position;
            simd::float3 color;
            float intensity;
        };
    
        float intensity;
        simd::float3 color;
        MTL::Buffer* buffer;

};

#endif /* LIGHT_HPP */
