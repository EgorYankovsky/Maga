#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct local_area {
    int area_num = 0;
    int x0 = 0;
    int x1 = 0;
    int y0 = 0;
    int y1 = 0;
};

struct point {
    double x = 0.0;
    double y = 0.0;
};

int kx = 0, ky = 0, areas_amount = 0, nodes_amount = 0, lines_amount = 0;
std::vector<point> nodes = {};
std::vector<std::pair<int, int>> lines = {};

std::string file_name = "test.py";
std::string command = "python ";

std::vector<double> coord_lines_x = {};
std::vector<double> coord_lines_y = {};
std::vector<local_area> areas = {};
std::vector<point> points = {};

void read_file(std::string file_path) {
    std::ifstream fin;
    fin.open(file_path);
    fin >> nodes_amount;
    nodes.resize(nodes_amount);
    for (int i(0); i < nodes_amount; i++) {
        double local_x = 0.0, local_y = 0.0;
        fin >> local_x >> local_y;
        nodes[i].x = local_x;
        nodes[i].y = local_y;
    }
    fin >> lines_amount;
    lines.resize(lines_amount);
    for (int i(0); i < lines_amount; i++) {
        int l1 = 0, l2 = 0;
        fin >> l1 >> l2;
        lines[i].first = l1;
        lines[i].second = l2;
    }

    // code here 

}

void build_mesh() {
    std::cout << "Currently, there is no any actions with building mesh" << std::endl;
}

void write_data(std::string points_path, std::string areas_path) {
    std::ofstream fout(points_path);
    fout << areas_amount << std::endl;
    fout.precision(15);
    for (int i(0); i < areas_amount; i++)
        fout << std::scientific << coord_lines_x[areas[i].x0] << " " << coord_lines_x[areas[i].x1] << " " <<  
        coord_lines_y[areas[i].y0] << " " << coord_lines_y[areas[i].y1] << std::endl;
}

void draw_mesh() {
    command += file_name;
    system(command.c_str());
}