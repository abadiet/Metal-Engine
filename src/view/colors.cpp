#include "view/colors.hpp"


Colors::Colors() {}

Colors::Colors(Colors& colors) {
    this->colors = colors.getColors();
}

Colors::Colors(std::vector<simd::float3> colors) {
    this->colors = colors;
}

Colors::~Colors() {}

Colors::Colors(Colors&& other) noexcept {
    colors = other.getColors();
}

void Colors::setColors(const std::vector<simd::float3>& colors) {
    this->colors = colors;
}

std::vector<simd::float3> Colors::getColors() const {
    return colors;
}
