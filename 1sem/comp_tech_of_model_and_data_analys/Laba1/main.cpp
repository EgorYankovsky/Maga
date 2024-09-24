#include "additional.hpp"

const std::string relative_input_old_format_file_path = "Data\\old_input.txt";
const std::string relative_input_new_format_file_path = "Data\\new_input.txt";
const std::string relative_output_file_path = "Data\\lines.txt";

int main() {
    int type_format = -1;
    std::string relative_input_file_path = "";
    std::cout << "New [0] / old [1] format?" << std::endl;
    std::cin >> type_format;
    switch (type_format) {
    case 0:
        relative_input_file_path = relative_input_new_format_file_path;
        break;
    case 1:
        relative_input_file_path = relative_input_old_format_file_path;
        break;
    default:
        throw std::ios_base::failure("incorrect input");
    }
    read_file(relative_input_file_path);
    build_mesh();
    write_data(relative_output_file_path);
    draw_mesh();
    return 0;
}