#ifndef SCNE_OBJECT_HPP
#define SCNE_OBJECT_HPP

#include <simd/simd.h>
#include "view/mesh.hpp"
#include "model/mtlm.hpp"


class SceneObject {

    public:
        SceneObject();
        ~SceneObject();

        void set_mesh(Mesh *mesh);
        Mesh* get_mesh();

        simd::float4x4 get_transform();
        void set_transform(simd::float4x4 transform);

        void translate(simd::float3 dPos);
        void rotate(simd::float3 dAngles);
        void scale(simd::float3 dRatios);

    private:
        Mesh *mesh;
        simd::float4x4 transform;

};

#endif /* SCNE_OBJECT_HPP */
