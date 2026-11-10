#include "Labyrinth.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Labyrinth::~Labyrinth() {
   delete[] labyrinthMatrix; 
}

Labyrinth::Labyrinth(){
    rowCount = 0;
    columnCount = 0;
    labyrinthMatrix = nullptr;
    std::cout << "Consturctor vid";

}
Labyrinth::Labyrinth(int rowCount, int columnCount) {
    std::cout<<"Constructor";
    this->rowCount = rowCount;
    this->columnCount = columnCount;
    labyrinthMatrix = new int* [rowCount + 1];
    for (int i = 0; i < rowCount; i ++)
        labyrinthMatrix[i] = new int[columnCount + 1];

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

int Labyrinth::getCell(int row, int column){
    return labyrinthMatrix[row][column];
}
