#include "header.hpp"
#include "prism.hpp"
#include "additional.hpp"

const std::string relative_input_file_path = "Data\\input.txt";
const std::string relative_output_file_path = "Data\\lines.txt";

int main()
{
    read_file(relative_input_file_path);
    build_mesh();
    write_data(relative_output_file_path);
    draw_mesh();
    return 0;
}