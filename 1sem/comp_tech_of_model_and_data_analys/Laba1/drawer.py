import matplotlib.pyplot as plt
import os

relative_triangle_path = "Data\\lines.txt"

class Point:
    def __init__(self, x : float, y : float):
        self.x = x 
        self.y = y 

class Line:
    def __init__(self, x0 : float, y0 : float, x1 : float, y1 : float):
        self.p1 = Point(x0, y0)
        self.p2 = Point(x1, y1)

def draw(big_big_list):
    if len(big_big_list) == 0:
        raise Exception("Error: empty lines array.")
    for line in big_big_list:
        plt.plot([line.p1.x, line.p2.x],
                 [line.p1.y, line.p2.y], color="black")
    plt.show() 

def read_file(relative_path_input) -> list:
    if not os.path.isfile(relative_path_input):
        raise Exception("Error: no such directory.")
    file = open(relative_path_input , "r")
    file_info = file.read().split('\n')
    lines_amount = int(file_info[0])
    list_of_lines = []
    for i in range(lines_amount):
        info_line = file_info[i + 1].split(" ")
        list_of_lines.append(Line(float(info_line[0]), float(info_line[1]), 
                                  float(info_line[2]), float(info_line[3])))
    return list_of_lines
    
def main():
    list_of_lines = read_file(relative_triangle_path)
    draw(list_of_lines)

if __name__ == "__main__":
    main()