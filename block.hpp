#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include <iostream>
using namespace std;
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "block.hpp"
#include "Console.h"

class Block 
{
    int x, y;
    int pre_x, pre_y;
    int count;
    
    int rotation, block_type;
    int shape[4][4];                   // shape[x][y]
    int pre_shape[4][4];               // shape[x][y]

    Block & newBlock(int x_in, int y_in);                      // 블럭 데이터 생성
    void delBlock();                                           // 블럭 데이터 삭제
    void setShape(int b_type, int shape[4][4], int rotation);  // 블럭타입 set

    void left();                    // 왼쪽
    void right();                   // 오른쪽
    bool down();                    // 아래
    bool go_bottom();               // 바닥으로
    void rotate(int direction);     // 회전

    bool check(int x, int y, int shape[4][4]);
    void showBlock(Matrix& matrix, string s = "█");
    void removeBlock(Matrix& matrix, string s = " ");
};

#endif