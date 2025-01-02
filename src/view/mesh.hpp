#ifndef MESH_HPP
#define MESH_HPP

#include <simd/simd.h>
#include <vector>


class Mesh {

    protected:
        struct Vertex {
            simd::float3 position; /* (x,y,z) */
            simd::float3 normal;   /* (x,y,z) */
        };

    public:
        Mesh();
        Mesh(std::vector<Mesh::Vertex> vertices, std::vector<ushort> indices);
        Mesh(Mesh&& other) noexcept;
        Mesh(const Mesh& other);
        ~Mesh();

        Mesh& operator=(const Mesh& other);

        std::vector<Mesh::Vertex> getVertices() const;
        void setVertices(const std::vector<Mesh::Vertex>& vertices);

        std::vector<ushort> getIndices() const;
        void setIndices(const std::vector<ushort>& indices);

    private:
        std::vector<Vertex> vertices;
        std::vector<ushort> indices;

};

#endif /* MESH_HPP */
