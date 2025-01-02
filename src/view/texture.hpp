#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <simd/simd.h>
#include <vector>
#include <stb_image.h>


class Texture {

    public:
        static MTL::Texture* Build(MTL::Device* device, const char* filename);
        static void Release();

        Texture(const Texture&);
        Texture(Texture&& other) noexcept;

        ~Texture();

    private:
        Texture();

        static std::vector<Texture> textures;

        std::string filename, vertexEntry, fragmentEntry;
        MTL::Texture *texture;

};


#endif /* TEXTURE_HPP */
