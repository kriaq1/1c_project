#pragma once

#include <vector>
#include <string>
#include <fstream>

using matrix = std::vector <std::vector <int>>;


matrix read_image(const std::string& filename);

