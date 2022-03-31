#include <vector>
#include <array>

using matrix = std::vector <std::vector <int>>;

using rectangle = std::array <int ,5>;


std::array<int, 3> get_colors(int pixel);

std::vector <rectangle> search_gradient_fill(const matrix& image, int flag = 2);

matrix get_single_color_lengths(const matrix& image);

std::vector <int> get_single_color_lengths(const std::vector<int>& image);

std::vector <int> get_gradient_transitions(const std::vector <int> &image);

matrix get_gradient_transitions(const matrix &image);

matrix get_transposed(const matrix& image);


int get_compares(int a, int b);

bool check_compares(int a);


std::array <int, 4> get_max_squad(const std::vector <int>& h);