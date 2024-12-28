#ifndef SCNE_OBJECT_HPP
#define SCNE_OBJECT_HPP

#include <simd/simd.h>
#include "view/mesh.hpp"
#include "model/mtlm.hpp"
#include "model/movement.hpp"


class SceneObject : public Movement {

    public:
        SceneObject();
        ~SceneObject();

        void setMesh(Mesh *mesh);
        Mesh* getMesh();

        void setScale(simd::float3 dRatios);
        void scale(simd::float3 dRatios);

        simd::float4x4 getTransform();

    private:
        Mesh *mesh;
        simd::float4x4 scaleMatrix;

};

#endif /* SCNE_OBJECT_HPP */
