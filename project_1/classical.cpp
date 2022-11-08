#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void getMatrixValues(int **matrixA, int ** matrixB, int maxRows, int maxCols, int matrixNum, string folderName) { 
   string fileName = to_string(matrixNum);
   string path = folderName + "/" + fileName;

   ifstream file(path);

   for (int row = 0; row < maxRows; row++) {
      for (int col = 0; col < maxCols; col++) {
         int value;
         file >> value;

         matrixA[row][col] = value;
         matrixB[row][col] = value;
      }
   }
}

void multiplyMatrices() {

}

int main() {
   int cols, rows, numOfMatrices;
   string folderName;

   cout << "Enter # of cols: ";
   cin >> cols;
   
   cout << "Enter # of rows: ";
   cin >> rows;

   cout << "Enter # of matrices to read: ";
   cin >> numOfMatrices;

   cout << "Enter name of folder: ";
   cin >> folderName;

   int **matrixA = new int*[rows];
   int **matrixB = new int*[rows];

   for (int row = 0; row < cols; row++) {
      matrixA[row] = new int[cols];
      matrixB[row] = new int[cols];
   }

   for (int matrixNumber = 0; matrixNumber < numOfMatrices; matrixNumber++) {
      getMatrixValues(matrixA, matrixB, rows, cols, matrixNumber, folderName);

      for (int row = 0; row < rows; row++) {
         for (int col = 0; col < cols; col++) {
            cout << matrixA[row][col];
         }
         cout << endl;
      }
      cout << endl;
   }

   return 0;
}