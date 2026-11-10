#pragma once

class Labyrinth {
     private:
         int** labyrinthMatrix;
         int rowCount;
         int columnCount;
         void populateLabyrinth();
     public:
         Labyrinth();
         Labyrinth(int rowCount, int columnCount);
         ~Labyrinth();
         int getCell(int row, int column); 
};
