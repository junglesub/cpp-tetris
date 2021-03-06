#include <cstring>
#include <iostream>
#include <string>
  #include <fstream>

#include "Console.h"
#include "block.hpp"

using namespace std;

void debugMatrix(int **matrix);
void drawMainFrame(void);
void drawScoreBoard(void);
void showBlock(Block block, string s = "█");
void removeBlock(Block block, string s = " ");
void render(int t, Block block);
bool inBoundOfMatrix(int x, int y);
void bottomCollide(int **matrix, Block *block, Block **nextBlock);
void removeLine(int **matrix, Block block);

int const screenWidth = 30;
int const screenHeight = 24;
int const leftScreenWidth = screenWidth / 3 * 2;
// int const screenWidth = getWindowWidth();
// int const screenHeight = getWindowHeight() - 3;
string const BORDERCH = "▓";

int main(void) {
  // Console Setting

  EnableCursor(0);
  clrscr();

  drawMainFrame();
  drawScoreBoard();

  int t = 0;
  char ch = '\0';
  int flag;

  // 2차원 동적 Matrix [x][y] 으로 이용.
  int **matrix = (int **)malloc(sizeof(int *) * leftScreenWidth + 1);
  for (int col = 0; col < leftScreenWidth + 1; col++) {
    matrix[col] = (int *)calloc(screenHeight, sizeof(int *));
    // 초기화
    matrix[col][0] = 1;                 // 천장
    matrix[col][screenHeight - 1] = 1;  // 바닥
  }
  for (int row = 1; row < screenHeight - 1; row++) {
    // matrix[0][row] = 1;
    // matrix[1][row] = 1;
    matrix[2][row] = 1;
    matrix[leftScreenWidth - 1][row] = 1;
  }

  Block &block = newBlock(screenWidth / 3 - 2, 1);
  Block *nextBlock = &newBlock(leftScreenWidth + screenWidth / 6 - 1, 10);
  showBlock(*nextBlock, "█");

  while (1) {
    flag = true;
    block.matrix = matrix;
    // 키보드 입력
    if (kbhit()) {
      ch = getch();

      if (ch == 27 || ch == 'q') {
        break;
      } else if (ch == 'a') {
        block.left();
        render(t, block);
      } else if (ch == 'm') {
        bottomCollide(matrix, &block, &nextBlock);
        continue;
      } else if (ch == 'd') {
        block.right();
        render(t, block);
      } else if (ch == 's') {
        if (!block.down()) {
          if (block.count < 2) {
            break;
          }
          bottomCollide(matrix, &block, &nextBlock);
          continue;
        }
        render(t, block);
      } else if (ch == 'r') {
        // removeBlock(block, "-");
        showBlock(block, " ");
        block.rotate(1);
        memcpy(block.pre_shape, block.shape, sizeof(int) * 4 * 4);
        showBlock(block);  // showBlock(block, "█");
      } else if (ch == 'e') {
        // removeBlock(block, "-");
        showBlock(block, " ");
        block.rotate(-1);
        memcpy(block.pre_shape, block.shape, sizeof(int) * 4 * 4);
        showBlock(block);  // showBlock(block, "█");
      }

      ch = '\0';
    }

    if (t % 100 == 0) {
      debugMatrix(matrix);
      if (!block.down()) {
        if (block.count < 2) {
          break;
        }
        bottomCollide(matrix, &block, &nextBlock);
        continue;
      }
      render(t, block);
    }

    t++;
    gotoxy(1, screenHeight + 1);
    MySleep(10);
  }
  gotoxy(1, 1);
  clrscr();
  cout << "Good Bye!\n";
}

void render(int t, Block block) {
  // Finally Display the Block
  // Remove Last saved Block
  if (t > 0) {
    removeBlock(block, " ");
  }

  // Display block
  showBlock(block);  // showBlock(block, "█");
}

void showBlock(Block block, string s) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (block.shape[x][y] == 2) {
        gotoxy(block.x + x, block.y + y);
        cout << s;
      }
    }
  }
}
void removeBlock(Block block, string s) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (block.pre_shape[x][y] == 2) {
        gotoxy(block.pre_x + x, block.pre_y + y);
        cout << s;
      }
    }
  }
}

bool inBoundOfMatrix(int x, int y) {
  if (x > 0 && x < leftScreenWidth) {
    if (y > 0 && y < screenHeight) {
      return true;
    }
  }
  gotoxy(1, screenHeight + 1);
  cout << "WARN-OOB (" << x << "," << y;
  return false;
}

void bottomCollide(int **matrix, Block *block, Block **nextBlock) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (block->pre_shape[x][y] == 2) {
        int setX = block->x + x;
        int setY = block->y + y;

        if (inBoundOfMatrix(setX, setY)) {
          matrix[setX][setY] = 2;
          gotoxy(setX, setY);
          cout << "█";
        }
      }
    }
  }

  removeLine(matrix, *block);

  memcpy(block, *nextBlock, sizeof(Block));
  showBlock(**nextBlock, " ");
  block->x = screenWidth / 3 - 2;
  block->y = 1;
  *nextBlock = &newBlock(leftScreenWidth + screenWidth / 6 - 1, 10);
  showBlock(**nextBlock, "▓");
  // // *nextBlock = &newBlock(3, 1);
}

void drawMainFrame(void) {
  // https://jrgraphix.net/r/Unicode/2500-257F
  // 여기 참고.

  clrscr();      // 화면 지우기
  gotoxy(0, 0);  // 좌측 상단에서 시작.

  // 맨 위 가로 # 그리기
  for (int x = 2; x < screenWidth; x++) {
    gotoxy(x, 0);
    cout << "═";
  }

  // 맨 위 모서리
  gotoxy(0, 0);  // 왼쪽
  cout << "🥕";
  // cout << "╔";
  gotoxy(screenWidth - 1, 0);  // 오른쪽
  cout << "🥕";
  // cout << "╗";

  // 테두리 만들기
  for (int y = 2; y < screenHeight; y++) {
    gotoxy(1, y);
    cout << "║";
    for (int x = 2; x < screenWidth - 1; x++) {
      gotoxy(x, y);
      cout << " ";
    }
    cout << "║";
  }

  // 맨 아래 # 그리기
  for (int x = 2; x < screenWidth; x++) {
    gotoxy(x, screenHeight);
    cout << "═";
  }

  // 맨 아래 모서리
  gotoxy(0, screenHeight);  // 왼쪽
  // cout << "╚";
  cout << "🥕";
  gotoxy(screenWidth - 1, screenHeight);  // 오른쪽
  // cout << "╝";
  cout << "🥕";
}

void drawScoreBoard(void) {
  int const scoreboardSize = screenWidth / 3;
  int const scoreboardStart = scoreboardSize * 2;
  // 왼쪽 오른쪽 나누기
  for (int y = 0; y < screenHeight; y++) {
    gotoxy(scoreboardStart, y);
    cout << "║";

    for (int x = 2; x < scoreboardSize - 2; x++) {
      if (y < 2 || y > screenHeight - 1) continue;
      // 빈공간으로 바꾸기
      gotoxy(scoreboardStart + x, y);
      cout << " ";
    }
  }
  // 모서리
  gotoxy(scoreboardStart, 0);  // 위
  cout << "╦";
  gotoxy(scoreboardStart, screenHeight);  // 아래
  cout << "╩";

  // 기본적인 텍스트 입력
  gotoxy(scoreboardStart + scoreboardSize / 2 - 9, 2);
  cout << "소은정섭의 테트리스";
  // for (int x = 1; x < scoreboardSize - 2; x += 2) {
  //   gotoxy(scoreboardStart + x, 3);
  //   cout << "🥕";
  // }
}

void debugMatrix(int **matrix){
	string filePath = "livematrix.txt";

	// write File
	ofstream writeFile(filePath.data());
  writeFile << "== Beginning ==" << endl;
	if( writeFile.is_open() ){
    for(int row = 0; row < screenHeight; row++) {
      for(int col = 0; col < leftScreenWidth; col++) {
        writeFile << matrix[col][row];
      }
      writeFile << endl;
    }
		writeFile.close();
  }
  writeFile << "== End ==" << endl;
}

void removeLine(int **matrix, Block block) {
  int count;
  for(int row = 0; row < 4; row++) {
    count = 0;
    for(int col = 0; col < leftScreenWidth; col++) {
      if(matrix[col][block.y + row] == 2) {
        count++;
      }
    }
    // if(count == leftScreenWidth) {
    gotoxy(2 + row, screenHeight + 1);
    cout << count;
    if(count > 12) {
      for(int col = 0; col < leftScreenWidth; col++) {
        matrix[col][block.y + row] = 0;
      }
    }
  }
}