#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

void createMatrices(int rows, int cols, int **matrix, int numberOfMatrices, string folderName) {

   for(int matrixNum = 0; matrixNum < numberOfMatrices; matrixNum++) {
      string fileName = to_string(matrixNum);
      string path = folderName + "/" + fileName;
      ofstream file(path);

      for (int row = 0; row < rows; row++) {
         for (int col = 0; col < cols; col++) {
            matrix[row][col] = rand() % 10;
            file << matrix[row][col] << " ";
         }
         file << endl;
      }

      file.close();
   }
}

int main() {
   srand((unsigned) time(NULL));
   
   int cols, rows, numOfMatrices;
   string folderName;

   cout << "Enter # of cols: ";
   cin >> cols;
   
   cout << "Enter # of rows: ";
   cin >> rows;

   cout << "Enter # of matrices to generate: ";
   cin >> numOfMatrices;

   cout << "Enter name of folder: ";
   cin >> folderName;

   int **matrix = new int*[rows];

   for (int row = 0; row < cols; row++) {
      matrix[row] = new int[cols];
   }
   createMatrices(rows, cols, matrix, numOfMatrices, folderName);

   cout << endl;
   return 0;
}