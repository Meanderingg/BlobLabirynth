#pragma once
#include <vector>

class Labyrinth {
     private:
         std::vector<std::vector<int>> labyrinthMatrix;
         int rowCount;
         int columnCount;
         void populateLabyrinth();
     public:
         Labyrinth(int rowCount, int columnCount);
         ~Labyrinth() = default;
         Labyrinth() = default;
         const std::vector <std::vector<int>> &getLabyrinth(); 
};
