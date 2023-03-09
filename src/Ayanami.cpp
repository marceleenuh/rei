#include <cstdio>

#include "Image.hpp"

int main(int argc, char** argv) {
    Image img("img/test.rei");
    
    img.write("img/test.png");
}