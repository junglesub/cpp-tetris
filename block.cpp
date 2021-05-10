enum BlockType
{
    b1, b2, b3, b4, b5
};

enum Turn
{
    left_turn = -1, right_turn = 1
};

/*1번 블럭*/
const int block1[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {2, 2, 2, 2},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {2, 2, 2, 2},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0}
        },
};
/*2번 블럭*/
const int block2[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        },
};
/*3번 블럭*/
const int block3[4][4][4] = {
        {
                        {0, 2, 0, 0},
                        {0, 2, 0, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 2},
                        {0, 2, 0, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 2, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 0, 2, 0},
                        {2, 2, 2, 0},
                        {0, 0, 0, 0}
        },
};
/*4번 블럭*/
const int block4[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 2, 0, 0},
                        {0, 2, 2, 0},
                        {0, 0, 2, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {2, 2, 0, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 0, 0},
                        {0, 2, 2, 0},
                        {0, 0, 2, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {2, 2, 0, 0},
                        {0, 0, 0, 0}
        },
};
/*5번 블럭*/
const int block5[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 2},
                        {0, 0, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 2, 0},
                        {0, 2, 2, 2},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0}
        },
        {
                        {0, 0, 2, 0},
                        {0, 0, 2, 2},
                        {0, 0, 2, 0},
                        {0, 0, 0, 0}
        },
};

Block::Block(int x_in, int y_in)         
{
    Block * newblock = new Block;
    srand(time(0));

    newblock->rotation = rand() % 4 + 0;
    newblock->block_type = rand() % 5 + 0;
    
    Block::setShape(newblock->block_type, newblock->shape, newblock->rotation);
    memcpy(newblock->pre_shape, newblock->shape, sizeof(int) * 4 * 4);

    newblock->pre_x = x_in;
    newblock->pre_y = y_in;

    newblock->x = x_in;
    newblock->y = y_in;

    newblock->count = 0;

    return *newblock;
}

void Block::setShape(int b_type, int shape[4][4], int rotation)
{

    switch (b_type)
    {
    case b1:
        memcpy(shape, block1[rotation], sizeof(int) * 4 * 4);
        break;

    case b2:
        memcpy(shape, block2[rotation], sizeof(int) * 4 * 4);
        break;

    case b3:
        memcpy(shape, block3[rotation], sizeof(int) * 4 * 4);
        break;

    case b4:
        memcpy(shape, block4[rotation], sizeof(int) * 4 * 4);
        break;

    case b5:
        memcpy(shape, block5[rotation], sizeof(int) * 4 * 4);
        break;
    
    default:
        cout << "rotation is not true. rotation is: " << rotation << '\n';
        break;
    }
}

void Block::delBlock(Block * delBlock)
{
    delete delBlock;
}

bool Block::Block::down()
{   
    int temp = pre_y;
    pre_x = x;
    pre_y = y++;

    count++;

    if(check() == false){
        pre_y = temp;
        y--;
        return false;
    }
    return true;
}

void Block::Block::left()
{
    int temp = pre_x;
    pre_x = x--;
    pre_y = y;
    
    if(check() == false){
        pre_x = temp;
        x++;
    }
}

void Block::Block::right()
{
    int temp = pre_x;
    pre_x = x++;
    pre_y = y;

    if(check() == false){
        pre_x = temp;
        x--;
    }
}

void Block::Block::rotate(int direction)
{
    int temp = rotation;
    memcpy(pre_shape, shape, sizeof(int) * 4 * 4);

    switch (direction)
    {
    case right_turn:
        rotation++;
        if (rotation > 3) {
            rotation -= 4;
        }
        break;

    case left_turn:
        rotation--;
        if (rotation < 0) {
            rotation += 4;
        }
        break;
    
    default:
        cout << "directon is not true. direction: " << direction << '\n';
        break;
    }

    setShape(block_type, shape, rotation);
    if(check() == false){
        pre_x = temp;
        x--;
    }
}

void Block::showBlock(Matrix& matrix, string s) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (block.shape[x][y] == 2) {
        gotoxy(block.x + x, block.y + y);
        cout << s;
      }
    }
  }
}
void Block::removeBlock(Matrix& matrix, string s) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (block.pre_shape[x][y] == 2) {
        gotoxy(block.pre_x + x, block.pre_y + y);
        cout << s;
      }
    }
  }
}