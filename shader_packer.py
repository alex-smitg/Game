import os

dir_path = os.path.dirname(os.path.realpath(__file__))

print("Shaders pack")
with open(dir_path + "\packed_shaders.h", "w") as file:
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
print("Shaders pack OK")
