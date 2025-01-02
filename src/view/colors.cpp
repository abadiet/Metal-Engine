#include "view/colors.hpp"


Colors::Colors() {}

Colors::Colors(const Colors& colors) {
    this->colors = colors.getColors();
}

Colors::Colors(Colors&& other) noexcept {
    colors = other.getColors();

    other.setColors({});
}

Colors::Colors(std::vector<simd::float3> colors) {
    this->colors = colors;
}

Colors::~Colors() {}

Colors& Colors::operator=(const Colors& other) {
    if (this == &other) {
        return *this;
    }

    colors = other.getColors();

    return *this;
}

void Colors::setColors(const std::vector<simd::float3>& colors) {
    this->colors = colors;
}

std::vector<simd::float3> Colors::getColors() const {
    return colors;
}
