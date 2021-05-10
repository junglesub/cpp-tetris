#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
using namespace std;
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "matrix.hpp"
#include "Console.h"

class Matrix
{
private:
    int **matrix
public:
    Matrix(int height, int width);
    ~Matrix(int height, int width);

    void render(int t, Block& block);

    bool check(int x, int y, int shape[4][4]);
    void removeLine(Matrix matrix, Block& block);
    void debugMatrix(Matrix matrix);
};

// Matrix ** newMatrix(int height, int width);
// void delMatrix(int height, int width);

#endif