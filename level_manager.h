#ifndef GAME_LEVEL_MANAGER
#define GAME_LEVEL_MANAGER

#include <fstream>
#include <string>
#include <vector>


class LevelManager {
public:



    int loadLevel(std::string path) {
        std::ifstream file(path);

        if (!file) {
            return 1;
        }

       
        
        std::string line;
        while (std::getline(file, line)) { 

        }

        file.close();
        return 0;
    }
};

#endif
