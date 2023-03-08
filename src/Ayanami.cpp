#include <cstdio>

#include "Image.hpp"

int main(int argc, char** argv) {
    Image img("img/test.jpg");

    img.save("img/saved.png");
}