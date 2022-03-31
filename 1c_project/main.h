#include "solution/solution.h"
#include "read_image/read_image.h"
#include <iostream>

std::string input_filename() {
    std::string filename;
    std::cin >> filename;
    return filename;
}

void output_rectangle(const rectangle& rect) {
    std::cout << "points: ";
    std::cout << "(" << rect[0]<< "," << rect[1] << ")";
    std::cout << ",  ";
    std::cout << "(" << rect[2]<< "," << rect[3] << ")\n";
    std::cout << "squad: " << rect[4] << '\n';
}

rectangle get_max_gradient_fill(const std::string &filename) {
    matrix image = read_image(filename);
    auto gradient_fills = search_gradient_fill(image);
    rectangle max_grad_fill {};
    for(int i = 0;i < gradient_fills.size();++i) {
        if(max_grad_fill[4] < gradient_fills[i][4]) {
            max_grad_fill = gradient_fills[i];
        }
    }
    return max_grad_fill;
}


