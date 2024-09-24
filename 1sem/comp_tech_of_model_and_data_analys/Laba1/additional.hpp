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


struct area {
    size_t field_num = -1;
    std::vector<int> p_refs_array;
    int x_delim;
    double kx;
    int y_delim;
    double ky;
};

size_t areas_amount = 0, nodes_amount = 0, border_lines_amount = 0, areas_lines_amount = 0;
int kx = 0, ky = 0;
std::vector<point> nodes = {};
std::vector<std::pair<int, int>> border_lines = {};
std::vector<area> areas = {};


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
    for (auto node : nodes) {
        if (std::count(coord_lines_x.begin(), coord_lines_x.end(), node.x) == 0) {
            coord_lines_x.push_back(node.x);            
        }
    }
    std::sort(coord_lines_x.begin(), coord_lines_x.end());
    for (auto node : nodes) {
        if (std::count(coord_lines_y.begin(), coord_lines_y.end(), node.y) == 0) {
            coord_lines_y.push_back(node.y);            
        }
    }
    std::sort(coord_lines_y.begin(), coord_lines_y.end());
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
    int current_area_iter = 0;
    while (areas.size() < areas_amount) {
        std::vector<std::string> subarray = split(info_from_file[current_line_iter], " ");
        subarray.erase(std::remove(subarray.begin(), subarray.end(), ""), subarray.end());
        area local_area = {};
        local_area.field_num = current_area_iter;
        current_area_iter++;

        local_area.p_refs_array = std::vector<int> {std::stoi(subarray[0]),
                                                    std::stoi(subarray[1]),
                                                    std::stoi(subarray[2]),
                                                    std::stoi(subarray[3])};

        local_area.x_delim = std::stoi(subarray[4]);
        local_area.kx = std::stod(subarray[5]);
        local_area.y_delim = std::stoi(subarray[6]);
        local_area.ky = std::stod(subarray[7]);
         
        areas.push_back(local_area);
        current_line_iter++;
    }
    fin.close();
}

void build_mesh() {
    for (auto area : areas) {
        for (size_t i (0); i < area.p_refs_array.size() - 1; i++) {
            for (size_t j (i + 1); j < area.p_refs_array.size(); j++) {
                std::pair<int, int> kek_line = {area.p_refs_array[i], 
                                                area.p_refs_array[j]};
                switch (area.p_refs_array.size())
                {
                case 3:
                    border_lines.push_back(kek_line);
                    border_lines_amount++;
                    break;
                case 4:
                    if ((i != 1 || j != 2) && (i != 0 || j != 3)) {
                        border_lines.push_back(kek_line);
                        border_lines_amount++;
                    }
                    break;              
                default:
                    throw std::length_error("no such area type with nodes amount");
                    break;
                }
            }
        }
        
    }
}

void write_data(std::string output_path) {
    int total_lines_amount = 0;
    total_lines_amount += border_lines_amount;
    total_lines_amount += areas_lines_amount;

    std::ofstream fout;
    fout.open(output_path);
    fout << total_lines_amount << std::endl;
    fout.precision(15);
    //file out of inner areas lines.
    for (size_t i(border_lines.size() - 1); i >= border_lines_amount; i--) {
        fout << std::scientific << nodes[border_lines[i].first].x << " " << nodes[border_lines[i].first].y << " " <<
        nodes[border_lines[i].second].x << " " << nodes[border_lines[i].second].y << " " << 2.0 << std::endl;    
    }
    // file out of border lines.
    for (int i(border_lines_amount - 1); i >= 0; i--) {
        fout << std::scientific << nodes[border_lines[i].first].x << " " << nodes[border_lines[i].first].y << " " <<
        nodes[border_lines[i].second].x << " " << nodes[border_lines[i].second].y << " " << 3.0 << std::endl;
    }
    fout.close();
}

void draw_mesh() {
    command += file_name;
    system(command.c_str());
}