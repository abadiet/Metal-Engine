#include "view/mesh.hpp"

Mesh::Mesh() {}

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
