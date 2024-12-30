#include "view/color.hpp"


Colors::Colors() {}

Colors::~Colors() {}

void Colors::setColors(const std::vector<simd::float3>& colors) {
    this->colors = colors;
}

std::vector<simd::float3> Colors::getColors() const {
    return colors;
}
