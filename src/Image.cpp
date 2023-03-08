#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

Image::Image(const std::string& path) {
    load(path);
}

void Image::load(const std::string& path) {
    if (!ok(path))
        throw std::runtime_error("Invalid file format");
    data = stbi_load(path.c_str(), &width, &height, &channels, 0);
}

void Image::save(const std::string& path) {
    switch (imageType(path)) {
        case ImageType::PNG:
            stbi_write_png(path.c_str(), width, height, channels, data, 0);
            break;
        case ImageType::JPG:
            stbi_write_jpg(path.c_str(), width, height, channels, data, 100);
            break;
        case ImageType::TGA:
            stbi_write_tga(path.c_str(), width, height, channels, data);
            break;
        case ImageType::BMP:
            stbi_write_bmp(path.c_str(), width, height, channels, data);
            break;
    }
}

int Image::ok(const std::string& path) {
    return stbi_info(path.c_str(), nullptr, nullptr, nullptr);
}

ImageType Image::imageType(const std::string& path) {
    size_t pos = path.find_last_of('.');
    std::string ext = path.substr(pos, path.length() - pos);

    if (ext == ".png") return ImageType::PNG;
    else if (ext == ".tga") return ImageType::TGA;
    else if (ext == ".bmp") return ImageType::BMP;
    else return ImageType::JPG;
}