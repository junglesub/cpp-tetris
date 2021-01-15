struct Block 
{
    int x, y; 
    int rotation, block_type;
    int ** shape;            // shape[x][y]

    void down();                // 블럭 수정
    void left();                // 왼쪽, 오른쪽
    void right();               // 오른쪽
    void rotate();              // 회전
};

Block * newBlock(int &x, int &y);         // 블럭 데이터 생성, shape 4 * 4, rotate, 초깃값 내가
void delBlock(Block &delBlock);                 // 블럭 데이터 삭제
void setShape(int b_type, int ** shape, int rotation);  // 블럭타입 set