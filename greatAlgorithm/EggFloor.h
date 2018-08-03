#pragma once
class EggFloor
{
public:
    EggFloor();
    ~EggFloor();

    static unsigned int getMinSteps(const unsigned int eggs, const unsigned int floors);

    static void printMatrix(unsigned int **matrix, const unsigned int rows, const unsigned int cols);

    static unsigned int droppingMax(const unsigned int eggs, const unsigned times);

    static unsigned int droppingEggsPuzzle(unsigned int eggs, unsigned int floors);

};

