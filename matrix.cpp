#include "matrix.hpp"

Matrix::Matrix(int height, int width)
{
    matrix = (int **)malloc(sizeof(int *) * leftScreenWidth + 1);
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

        return matrix;
    }

void Matrix::removeLine(Block block)
{
  int count;
  for(int row = 0; row < 4; row++) {
    count = 0;
    for(int col = 2; col < leftScreenWidth; col++) {
      if(matrix[col][block.y + row] == 2) {
        count++;
      }
    }
    // if(count == leftScreenWidth) {
    gotoxy(2 + row, screenHeight + 1);
    cout << count;
    if(count >= leftScreenWidth - 4) {
      for(int col = 2; col < leftScreenWidth; col++) {
        matrix[col][block.y + row] = 0;
        
      }
    }
  }
}

void Matrix::debugMatrix(int **matrix)
{
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

bool Matrix::check(int &x, int &y, int shape[4][4])
{
    int flag = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] != 0) {
                if (matrix[x + i][y + j] != 0) {
                    flag = false;
                }
            }
        }
    }
  return flag;
}