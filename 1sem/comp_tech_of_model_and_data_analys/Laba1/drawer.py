import matplotlib.pyplot as plt
import os

relative_triangle_path = "Data\\points.txt"

class point:
    def __init__(self, x, y):
        self.x = x 
        self.y = y 

class rectangle:
    def __init__(self, p0, p1, p2, p3):
        self.point0 = p0
        self.point1 = p1
        self.point2 = p2
        self.point3 = p3

    def __init__(self, x0, y0, x1, y1, 
                       x2, y2, x3, y3):
        self.point0 = point(x0, y0)
        self.point1 = point(x1, y1)
        self.point2 = point(x2, y2)
        self.point3 = point(x3, y3)

class triangle:
    def __init__(self, p0, p1, p2):
        self.point0 = p0  
        self.point1 = p1  
        self.point2 = p2

    def __init__(self, x0, y0, x1, y1, x2, y2):
        self.point0 = point(x0, y0)  
        self.point1 = point(x1, y1)  
        self.point2 = point(x2, y2)


def draw(big_big_list):
    if len(big_big_list) == 0:
        raise Exception("Error: empty triangles array.")
    for triangle in big_big_list:

        plt.plot()
    plt.show() 

def read_file(relative_path_input) -> list:
    if not os.path.isfile(relative_path_input):
        raise Exception("Error: no such directory.")
    file = open(relative_path_input , "r")
    file_info = file.read().split('\n')
    figures_amount = int(file_info[0])
    list_of_figures = []
    for i in range(figures_amount):
        info_line = file_info[i + 1].split(" ")
        if len(info_line) == 3:
            list_of_figures.append(triangle())
        
    print("fe")
    
    
    


list_of_triangles = read_file(relative_triangle_path)
draw(list_of_triangles)