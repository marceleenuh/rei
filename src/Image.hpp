#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

/*       REI FILE LAYOUT        */
/*  --------------------------  */
//  Null byte paddings are only to
//  make it seem less boring :)
//
//  Rei as in Rei Ayanami (my life)
//
//  4 bytes (UInt32)
//    magic number (826973)
//
//  2 bytes (UInt8)
//    padding (255)
//
//  4 bytes (UInt32) 
//    width
//
//  4 bytes (UInt32)
//    height
//
//  2 bytes (UInt8)
//    padding (255)
//
//  16 bytes (UInt8)
//    signature
//
//  6 bytes (UInt8)
//    padding (255)
//
/*             DATA             */
/*  --------------------------  */
//  width * height * 3 bytes (uint8_t)
//    Image data (RGB)

enum ImageType {
    PNG = 0,
    JPG,
    TGA,
    BMP,
    REI
};

class Image {
private:
    size_t size;
    uint8_t* data;
    int channels = 3;
    int width, height;
    char signature[16];

public:
    Image() {}
    Image(const std::string& path);
    ~Image() { delete[] data; }

    void load(const std::string& path);
    void write(const std::string& path);

    int loadRei(const std::string& path);
    void writeRei(const std::string& path);

    static int ok(const std::string& path);
    static ImageType imageType(const std::string& path);
}; 