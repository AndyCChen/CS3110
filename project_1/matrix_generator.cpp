#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

void createMatrix(int rows, int cols, int **matrix) {
   for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
         matrix[row][col] = rand() % 10;
         cout << matrix[row][col] << " ";
      }
      cout << endl;
   }
}

int main() {
   srand((unsigned) time(NULL));
   
   int cols, rows, numOfMatrices;

   cout << "Enter # of cols: ";
   cin >> cols;
   
   cout << "Enter # of rows: ";
   cin >> rows;

   cout << "Enter # of matrices to generate: ";
   cin >> numOfMatrices;

   int **matrix = new int*[rows];

   for (int row = 0; row < cols; row++) {
      matrix[row] = new int[cols];
   }

   for(int i = 0; i < numOfMatrices; i++) {
      createMatrix(rows, cols, matrix);
      cout << endl;
   }

   string path = "/2x2/file.txt";
   ofstream file(path);
   file << "stuff";

   return 0;
}