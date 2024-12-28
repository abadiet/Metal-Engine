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

        void set_mesh(Mesh *mesh);
        Mesh* get_mesh();

        void set_scale(simd::float3 dRatios);
        void scale(simd::float3 dRatios);

        simd::float4x4 get_transform();

    private:
        Mesh *mesh;
        simd::float4x4 scale_matrix;

};

#endif /* SCNE_OBJECT_HPP */
