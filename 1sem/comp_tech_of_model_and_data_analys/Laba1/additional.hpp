#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

struct point {
    double x = 0.0;
    double y = 0.0;
};


struct local_field {
    size_t field_num = -1;
    int p1;
    int p2;
    int p3;
    int p4;
};

size_t areas_amount = 0, nodes_amount = 0, border_lines_amount = 0;
int kx = 0, ky = 0;
std::vector<point> nodes = {};
std::vector<std::pair<int, int>> border_lines = {};
std::vector<std::vector<int>> areas = {};


std::string file_name = "drawer.py";
std::string command = "python ";

std::vector<double> coord_lines_x = {};
std::vector<double> coord_lines_y = {};

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void read_file(std::string file_path) {
    std::ifstream fin;
    fin.open(file_path);
    std::string file_data;
    std::vector<std::string> info_from_file = {};
    std::string current_line;
    while (getline(fin, current_line)) {
        file_data += current_line + "\n";
    }
    size_t current_line_iter = 0;
    info_from_file = split(file_data, "\n");
    nodes_amount = std::stoi(info_from_file[current_line_iter]);
    current_line_iter++;
    while (nodes.size() < nodes_amount) {
        std::vector<std::string> subarray = split(info_from_file[current_line_iter], " ");
        subarray.erase(std::remove(subarray.begin(), subarray.end(), ""), subarray.end());
        for (size_t i(0); i < subarray.size(); i+=2) {
            point p; p.x = std::stod(subarray[i]); p.y = std::stod(subarray[i + 1]);
            nodes.push_back(p);
        }
        current_line_iter++;
    }
    border_lines_amount = std::stoi(info_from_file[current_line_iter]);
    current_line_iter++;
    while (border_lines.size() < border_lines_amount) {
        std::vector<std::string> subarray = split(info_from_file[current_line_iter], " ");
        subarray.erase(std::remove(subarray.begin(), subarray.end(), ""), subarray.end());
        for (size_t i(0); i < subarray.size(); i+=2) {
            std::pair<int, int> kek_line = {std::stoi(subarray[i]), std::stoi(subarray[i + 1])};
            border_lines.push_back(kek_line);
        }
        current_line_iter++;
    }
    areas_amount = std::stoi(info_from_file[current_line_iter]);
    current_line_iter++;
    while (areas.size() < areas_amount) {
        std::vector<std::string> subarray = split(info_from_file[current_line_iter], " ");
        subarray.erase(std::remove(subarray.begin(), subarray.end(), ""), subarray.end());
        std::vector<int> local_refs = {};
        for (size_t i(0); i < subarray.size(); i++)
            local_refs.push_back(std::stoi(subarray[i]));
        areas.push_back(local_refs);
        current_line_iter++;
    }
    fin.close();
}

void build_mesh() {
    std::cout << "Currently, there is no any actions with building mesh" << std::endl;
}

void write_data(std::string output_path) {
    int total_lines_amount = 0;
    total_lines_amount += border_lines_amount;
    
    std::ofstream fout;
    fout.open(output_path);
    fout << total_lines_amount << std::endl;
    fout.precision(15);
    for (size_t i(0); i < border_lines_amount; i++) {
        fout << std::scientific << nodes[border_lines[i].first].x << " " << nodes[border_lines[i].first].y << " " <<
        nodes[border_lines[i].second].x << " " << nodes[border_lines[i].second].y << std::endl;
    }
    fout.close();
}

void draw_mesh() {
    command += file_name;
    system(command.c_str());
}