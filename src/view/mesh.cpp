#include "view/mesh.hpp"

Mesh::Mesh() {}

Mesh::Mesh(Mesh& mesh) {
    vertices = mesh.getVertices();
    indices = mesh.getIndices();
}

Mesh::Mesh(std::vector<Mesh::Vertex> vertices, std::vector<ushort> indices) {
    this->vertices = vertices;
    this->indices = indices;
}

Mesh::Mesh(Mesh&& other) noexcept {
    vertices = other.getVertices();
    indices = other.getIndices();
}

Mesh::~Mesh() {}

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
