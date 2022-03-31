#include "main.h"

int main(int argc, char** argv) {
    if(argc >= 2) {
        for(int i = 1;i < argc;++i) {
            output_rectangle(get_max_gradient_fill(argv[i]));
        }
    } else{
        output_rectangle(get_max_gradient_fill(input_filename()));
    }
}

