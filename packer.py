import os

dir_path = os.path.dirname(os.path.realpath(__file__))


def load_obj(file):
    vertices_position = []
    texture_coordinates = []
    normals = []

    faces = []

    output = []
    
    for line in file:
        if "v " in line:
            d = line.split(" ")
            vertices_position.append([float(d[1]), float(d[2]), float(d[3])])

            
        
        if "vt" in line:
            d = line.split(" ")
            texture_coordinates.append([float(d[1]), float(d[2])])

        if "vn" in line:
            d = line.split(" ")
            normals.append([float(d[1]), float(d[2]), float(d[3])])


        if "f " in line:
            d0 = line.split(" ")

            g = [d0[i].split("/") for i in range(1,4)]


            for i in range(3):
                for j in range(3):
                    g[i][j] = int(g[i][j]) - 1

            for i in g:
                _vertex_position = vertices_position[i[0]]
                _texture_coordinate = texture_coordinates[i[1]]
                _normal =  normals[i[2]]


                output.append(_vertex_position[0])
                output.append(_vertex_position[1])
                output.append(_vertex_position[2])
                output.append(_texture_coordinate[0])
                output.append(_texture_coordinate[1])
                output.append(_normal[0])
                output.append(_normal[1])
                output.append(_normal[2])

    return output
            





print("Assets")
print("Shaders")
with open(dir_path + "\shaders.h", "w") as file:
    file.write("#pragma once\n")
    file.write("#include <map>\n")
    file.write("#include <string>\n")
    file.write("std::map<std::string, std::string> shaders = {\n")
    with os.scandir(dir_path + "\ASSETS\shaders") as it:
        for entry in it:
            if entry.is_file():
                file.write('{"'+entry.name+'",'+'R"(')
                
                with open(entry.path, "r") as f:
                    file.write(f.read())
                file.write(')"},')


    file.write("};")
print("Shaders OK")
print("Models")
with open(dir_path + "\models.h", "w") as file:
    file.write("#pragma once\n")
    file.write("#include <map>\n")
    file.write("#include <string>\n")
    file.write("std::map<std::string, std::vector<GLfloat>> models = {\n")

    with os.scandir(dir_path + "\ASSETS\models") as it:
      for entry in it:
            if entry.is_file():
                file.write('{"'+entry.name+'",'+" {")
                with open(entry.path, "r") as f:
                    vertices = load_obj(f)

                    for i in range(len(vertices)-1):
                        file.write(str(vertices[i]))
                        file.write(", ")
                    file.write(str(vertices[i-1]))
                file.write("}},")

    file.write("};")
print("Models OK")
print("Assets OK")
