#include <cstring>
#include <iostream>
#include <string>

#include "Console.h"
#include "block.hpp"

using namespace std;

void drawMainFrame(void);
void drawScoreBoard(void);
void showBlock(Block block, string s = "#");
void removeBlock(Block block, string s = " ");

int const screenWidth = getWindowWidth();
int const screenHeight = getWindowHeight() - 3;
string const BORDERCH = "▓";

int main(void) {
  // Console Setting

  EnableCursor(0);
  clrscr();

  drawMainFrame();
  drawScoreBoard();

  int t = 0;
  char ch = '\0';

  // 2차원 동적 Matrix [x][y] 으로 이용.
  int **matrix = new int *[screenWidth / 3 * 2];
  for (int col = 0; col < screenWidth / 3 * 2; col++) {
    matrix[col] = new int[screenHeight];
  }

  Block &block = newBlock(3, 5);

  while (1) {
    // 키보드 입력
    if (kbhit()) {
      ch = getch();

      if (ch == 27 || ch == 'q') {
        break;
      } else if (ch == 'a') {
        block.left();
      } else if (ch == 'd') {
        block.right();
      }

      ch = '\0';
    }

    if (t % 100 == 0) {
      block.down();
    }

    // Finally Display the Block
    // Remove Last saved Block
    if (t > 0) {
      removeBlock(block);
    }

    // Display block
    showBlock(block);  // showBlock(block, "#");

    t++;
    gotoxy(1, screenHeight + 1);
    MySleep(10);
  }
  gotoxy(1, 1);
  printf("Good bye!\n");
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

void drawMainFrame(void) {
  // https://jrgraphix.net/r/Unicode/2500-257F
  // 여기 참고.

  clrscr();      // 화면 지우기
  gotoxy(0, 0);  // 좌측 상단에서 시작.

  // 맨 위 가로 # 그리기
  for (int x = 0; x < screenWidth; x++) {
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
  for (int x = 0; x < screenWidth; x++) {
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