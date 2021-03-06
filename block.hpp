#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

struct Block 
{
    int x, y;
    int pre_x, pre_y;
    
    int rotation, block_type;
    int shape[4][4];                   // shape[x][y]
    int pre_shape[4][4];               // shape[x][y]

    int ** matrix;
    int count;

    void left();                    // 왼쪽
    void right();                   // 오른쪽
    bool down();                    // 아래
    bool go_bottom();               // 바닥으로
    void rotate(int direction);     // 회전

    bool check();
};

Block & newBlock(int x_in, int y_in);                      // 블럭 데이터 생성
void delBlock(Block * delBlock);                           // 블럭 데이터 삭제
void setShape(int b_type, int shape[4][4], int rotation);  // 블럭타입 set

#endif