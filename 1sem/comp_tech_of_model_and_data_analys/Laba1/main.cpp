#include "header.hpp"
#include "prism.hpp"
#include "additional.hpp"

const std::string relative_input_file_path = "Data\\input.txt";
const std::string relative_output_points_path = "Data\\points.txt";
const std::string relative_output_areas_path = "Data\\areas.txt";

int main()
{
    read_file(relative_input_file_path);
    build_mesh();
    write_data(relative_output_points_path, relative_output_areas_path);
    draw_mesh();
    return 0;
}