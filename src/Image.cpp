#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

Image::Image(const std::string& path) {
    load(path);
}

void Image::load(const std::string& path) {
    if (loadRei(path))
        return;
    if (!ok(path))
        throw std::runtime_error("Invalid file format");
    data = stbi_load(path.c_str(), &width, &height, &channels, channels);
    size = width * height * channels;
}

void Image::write(const std::string& path) {
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
        case ImageType::REI:
            writeRei(path);
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
    else if (ext == ".rei") return ImageType::REI;
    else return ImageType::JPG;
}

int Image::loadRei(const std::string& path) {
    int magicNumber;
    char padding[6]; // Won't work if padding isn't written here. So, yeah! :)
    delete[] data; // Wipe any existing image data
    std::ifstream file(path, std::ios::binary);
    if(!file)
        throw std::runtime_error("Error opening file");

    file.read((char*)&magicNumber, 4);
    if (magicNumber != 826973)
        return 0;

    file.read(padding, 2);
    file.read((char*)&width, 4);
    file.read((char*)&height, 4);
    file.read(padding, 2);
    file.read(signature, 16);
    file.read(padding, 6);

    size = width * height * 3;
    data = (uint8_t*)malloc(size);
    file.read((char*)data, size);
    file.close();
    return 1;
}

void Image::writeRei(const std::string& path) {
    uint32_t magicNumber = 826973;
    const char _signature[16] = "EVA 00";
    uint8_t padding[6];
    memset(padding, 0xff, 6);

    std::ofstream file(path, std::ios::binary);
    if(!file)
        throw std::runtime_error("Error opening file");

    file.write((char*)&magicNumber, 4);
    file.write((char*)padding, 2);
    file.write((char*)&width, 4);
    file.write((char*)&height, 4);
    file.write((char*)padding, 2);
    file.write(_signature, 16);
    file.write((char*)padding, 6);
    file.write((char*)data, size);
    file.close();
}