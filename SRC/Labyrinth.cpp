#include "Labyrinth.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Labyrinth::Labyrinth(int rowCount, int columnCount) {
    this->rowCount = rowCount;
    this->columnCount = columnCount;
    labyrinthMatrix = std::vector<std::vector<int>>(rowCount, std::vector<int> (columnCount, 0));
    srand(time(0));
    populateLabyrinth();
}

void Labyrinth::populateLabyrinth(){
    for (int i = rowCount - 1; i >= 0; i--){
        for (int j = columnCount - 1; j >= 0; j--){
            int randomNumber = rand() % 3;
            labyrinthMatrix[i][j] = randomNumber;    
        }
    }

}


const std::vector< std::vector<int>>& Labyrinth::getLabyrinth(){
    return labyrinthMatrix;
}
