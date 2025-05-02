#ifndef GAME_LEVEL_MANAGER
#define GAME_LEVEL_MANAGER

#include <fstream>
#include <string>
#include <vector>
#include "cell_enum.h"

class LevelManager {
public:

    std::vector<std::vector<CellType>> map;
    
    CellType getCellType(int x, int y) {
        return map[x][y];
    }

    int loadLevel(std::string path) {
        std::ifstream file(path);

        if (!file) {
            return 1;
        }

       
        
        std::string line;
        while (std::getline(file, line)) { 

            std::vector<CellType> r;
            for (char i : line) {
                switch (i)
                {
                case '=':
                    r.push_back(CellType::STAND);
                    break;
                case '.':
                    r.push_back(CellType::WALK);
                    break;
                case 'f':
                    r.push_back(CellType::PATH);
                    break;
                case 'o':
                    r.push_back(CellType::START);
                    break;
                case 'x':
                    r.push_back(CellType::END);

                default:
                    break;
                }
            }

            map.push_back(r);
        }

        file.close();


        

        return 0;



    }




    
};

#endif
