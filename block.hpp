struct Block 
{
    int rotation, x, y;
    int shape[1][4][4];         // shape[rotation][x][y]

    void del();                 // 블럭 데이터 삭제

    void down();                // 블럭 수정
    void left();                // 왼쪽, 오른쪽
    void right();               // 오른쪽
    void rotate();              // 회전
};

Block * newBlock(int &x, int &y);         // 블럭 데이터 생성, shape 4 * 4, rotate, 초깃값 내가