#ifndef COLOR_HPP
#define COLOR_HPP

#include <simd/simd.h>
#include <vector>


class Colors {

    public:
        Colors();
        Colors(const Colors& colors);
        Colors(std::vector<simd::float3> colors);
        Colors(Colors&& other) noexcept;
        ~Colors();

        Colors& operator=(const Colors& other);

        void setColors(const std::vector<simd::float3>& colors);
        std::vector<simd::float3> getColors() const;

    private:
        std::vector<simd::float3> colors;

};

#endif  /* COLOR_HPP */