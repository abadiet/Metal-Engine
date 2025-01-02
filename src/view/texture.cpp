#include "view/texture.hpp"


std::vector<Texture> Texture::textures;

MTL::Texture* Texture::Build(MTL::Device* device, const char* filename) {
    MTL::TextureDescriptor* descriptor;
    int tw, th, tc;
    unsigned char* image;

    for (const Texture& texture : textures) {
        if (texture.filename == filename) {
            return texture.texture;
        }
    }

    image = stbi_load(filename, &tw, &th, &tc, 4);
    if (!image) {
        throw std::runtime_error("Failed to load image " + std::string(filename));
    }

    textures.push_back(Texture());
    textures.back().filename = filename;

    descriptor = MTL::TextureDescriptor::alloc()->init();
    descriptor->setWidth(NS::UInteger(tw));
    descriptor->setHeight(NS::UInteger(th));
    descriptor->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
    descriptor->setTextureType(MTL::TextureType2D);
    descriptor->setStorageMode(MTL::StorageModeManaged);
    descriptor->setUsage(MTL::ResourceUsageSample | MTL::ResourceUsageRead);

    textures.back().texture = device->newTexture(descriptor);
    textures.back().texture->replaceRegion(MTL::Region(0, 0, NS::UInteger(tw), NS::UInteger(th)), 0, image, NS::UInteger(tw * 4));

    stbi_image_free(image);

    return textures.back().texture;
}

void Texture::Release() {
    textures.clear();
}

Texture::Texture() {
    texture = nullptr;
}

Texture::Texture(const Texture& other) {
    this->filename = other.filename;
    if (this->texture) {
        this->texture->release();
    }
    if (other.texture) {
        this->texture = other.texture->retain();
    }
}

Texture::Texture(Texture&& other) noexcept {
    this->filename = other.filename;
    if (this->texture) {
        this->texture->release();
    }
    if (other.texture) {
        this->texture = other.texture->retain();
        other.texture->release();
    }

    other.texture = nullptr;
}

Texture::~Texture() {
    if (texture) {
        texture->release();
    }
}
