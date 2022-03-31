#include "read_image.h"

using matrix = std::vector <std::vector <int>>;


matrix read_image(const std::string& filename) {
    int size;
    int width;
    int height;
    short int bits_per_pixel;
    int pixels_address;
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    file.seekg( 2, std::ios::beg);
    file.read ((char*)&size, sizeof(int));
    file.seekg( 10, std::ios::beg);
    file.read ((char*)&pixels_address, sizeof(int));
    file.seekg( 18, std::ios::beg);
    file.read ((char*)&width, sizeof(int));
    file.read ((char*)&height, sizeof(int));
    file.seekg( 28, std::ios::beg);
    file.read ((char*)&bits_per_pixel, sizeof(short int));

    file.seekg( pixels_address, std::ios::beg);
    matrix result(width, std::vector <int> (height));
    int curr_pixel = 0;
    for(int y = width - 1;y >= 0;--y) {
        for(int x = 0;x < height;++x) {
            file.read((char*)&curr_pixel, bits_per_pixel / 8);
            result[y][x] = curr_pixel;
            curr_pixel = 0;
        }
    }

    return result;
}

