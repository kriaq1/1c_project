#include "solution.h"


using matrix = std::vector<std::vector<int>>;

using rectangle = std::array <int ,5>;


std::array<int, 3> get_colors(int pixel) {
    std::array<int, 3> result{};
    for (int i = 0; i < 3; ++i) {
        result[i] = ((uint32_t)pixel >> (i * 8)) % 256;
    }
    return result;
}

int get_compares(int a, int b) {
    int result = 0;
    auto a_colors = get_colors(a);
    auto b_colors = get_colors(b);
    for (int i = 0; i < 3; ++i) {
        result ^= (a_colors[i] <= b_colors[i]) << (i * 2 + 1);
        result ^= (a_colors[i] >= b_colors[i]) << (i * 2);
    }
    return result;
}

bool check_compares(int a) {
    return (a & (3 << 4)) && (a & (3 << 2)) && (a & 3);
}


matrix get_transposed(const matrix &image) {
    matrix result(image[0].size(), std::vector<int>(image.size()));
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[0].size(); ++j) {
            result[i][j] = image[j][i];
        }
    }
    return result;
}

std::vector <int> get_single_color_lengths(const  std::vector <int>& image) {
    std::vector <int> result(image.size());
    int same_first = image.size() - 1;
    result[same_first] = 1;
    for (int j = same_first - 1; j >= 0; --j) {
        if (image[same_first] == image[j]) {
            result[j] = result[j + 1] + 1;
        } else {
            same_first = j;
            result[same_first] = 1;
        }
    }
    return result;
}

matrix get_single_color_lengths(const matrix &image) {
    matrix result(image.size(), std::vector<int>(image[0].size()));
    for (int i = 0; i < image.size(); ++i) {
        result[i] = get_single_color_lengths(image[i]);
    }
    return result;
}

matrix get_gradient_transitions(const matrix &image) {
    matrix result(image.size(), std::vector<int>(image[0].size()));
    for (int i = 0; i < result.size();++i) {
        result[i] = get_gradient_transitions(image[i]);
    }
    return result;
}

std::vector<int> get_gradient_transitions(const std::vector<int> &image) {
    std::vector<int> result(image.size());
    int begin_monotone = 0;
    int compares;
    for (int i = 0; i < image.size() - 1; ++i) {
        if (i == begin_monotone) {

            compares = get_compares(image[begin_monotone], image[begin_monotone + 1]);
            continue;
        }


        int curr_compares = get_compares(image[i], image[i + 1]);
        if (check_compares(curr_compares & compares)) {
            compares &= curr_compares;
            continue;
        } else {
            result[begin_monotone] = i;
            begin_monotone = i + 1;
        }
    }
    result[begin_monotone] = result.size() - 1;
    return result;
}



std::array <int, 4> get_max_squad(const std::vector <int>& h) {
    std::vector<int> left_min, right_min;
    int n = h.size();
    std::vector<int> left(n), right(n);
    left_min.push_back(0);
    for (int i = 0; i < n; ++i) {
        if (h[i] > h[left_min.back()]) {
            left[i] = left_min.back() + 1;
            left_min.push_back(i);
        } else {
            while (left_min.size() > 0 && h[i] <= h[left_min.back()]) {
                left_min.pop_back();
            }
            if (left_min.size() == 0) left[i] = 0;
            else left[i] = left_min.back() + 1;
            left_min.push_back(i);
        }
    }
    right_min.push_back(n - 1);
    for (int i = n - 1; i > -1; --i) {
        if (h[i] > h[right_min.back()]) {
            right[i] = right_min.back() - 1;
            right_min.push_back(i);
        } else {
            while (right_min.size() > 0 && h[i] <= h[right_min.back()]) {
                right_min.pop_back();
            }
            if (right_min.size() == 0) right[i] = n -1;
            else right[i] = right_min.back() - 1;
            right_min.push_back(i);
        }
    }


    std::array <int, 4> result{};
    int max_squad = INT32_MIN;
    for (int i = 0; i < n; ++i) {
        if (max_squad < h[i] * (right[i] - left[i] + 1)) {
            result[0] = left[i];
            result[1] = right[i];
            result[2]= h[i];
            max_squad = h[i] * (right[i] - left[i] + 1);
        }
    }
    result[3] = max_squad;
    return result;
}



std::vector<rectangle> search_gradient_fill(const matrix& image, int flag) {
    if(flag == 2) {
        auto result = search_gradient_fill(image, 1);
        for(int i = 0;i < result.size();++i) {
            std::swap(result[i][0],result[i][1]);
            std::swap(result[i][2],result[i][3]);
        }
        auto result1 = search_gradient_fill(image,0);
        for(int i = 0;i < result1.size();++i) {
            result.push_back(result1[i]);
        }
        return result;
    }

    if(flag == 1) {
        return search_gradient_fill(get_transposed(image), 0);
    }
    std::vector <rectangle> result;

    matrix single_color_lengths = get_transposed(get_single_color_lengths(get_transposed(image)));
    matrix gradient_transitions = get_gradient_transitions(image);
    for(int i = 0;i < image.size();++i) {
        int begin_transition = 0;
        while(true) {
            int end_transition = gradient_transitions[i][begin_transition];
            auto res= get_max_squad(std::vector <int> (single_color_lengths[i].begin() + begin_transition,
                                                       single_color_lengths[i].begin() + end_transition + 1));
            res[0] += begin_transition;
            res[1] += begin_transition;
            result.push_back({i, res[0], i + res[2] - 1, res[1],res[3]});
            if(end_transition == image[i].size() - 1) break;
            begin_transition = end_transition + 1;
        }
    }
    return result;
}
