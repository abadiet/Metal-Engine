#include "view/mesh.hpp"

Mesh::Mesh() {}

Mesh::Mesh(std::vector<Mesh::Vertex> vertices, std::vector<ushort> indices) {
    this->vertices = vertices;
    this->indices = indices;
}

Mesh::Mesh(Mesh&& other) noexcept {
    vertices = other.getVertices();
    indices = other.getIndices();

    other.setVertices({});
    other.setIndices({});
}

Mesh::Mesh(const Mesh& other) {
    vertices = other.getVertices();
    indices = other.getIndices();
}

Mesh::~Mesh() {}

Mesh& Mesh::operator=(const Mesh& other) {
    if (this == &other) {
        return *this;
    }

    vertices = other.getVertices();
    indices = other.getIndices();

    return *this;
}

std::vector<Mesh::Vertex> Mesh::getVertices() const {
    return vertices;
}

void Mesh::setVertices(const std::vector<Mesh::Vertex>& vertices) {
    this->vertices = vertices;
}

void Mesh::setIndices(const std::vector<ushort>& indices) {
    this->indices = indices;
}

std::vector<ushort> Mesh::getIndices() const {
    return indices;
}
