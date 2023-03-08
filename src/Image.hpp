#pragma once
#include <string>
#include <stdexcept>

enum ImageType {
    PNG = 0,
    JPG,
    TGA,
    BMP
};

class Image {
private:
    int channels;
    uint8_t* data;
    int width, height;

public:
    Image() {}
    Image(const std::string& path);
    ~Image() { free(data); }

    void load(const std::string& path);
    void save(const std::string& path);

    static int ok(const std::string& path);
    static ImageType imageType(const std::string& path);
}; 