#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

void getMatrixValues(int **matrixA, int ** matrixB, int maxRows, int maxCols, int matrixNum) { 
   for (int row = 0; row < maxRows; row++) {
      for (int col = 0; col < maxCols; col++) {
         matrixA[row][col] = rand() % 10;
         matrixB[row][col] = rand() % 10;
      }
   }
}

void multiplyMatrices(int **matrixA, int ** matrixB, int maxRows, int maxCols) {
   for (int row = 0; row < maxRows; row++) {
      for (int col = 0; col < maxCols; col++) {
         cout << matrixA[row][col] << " ";
      }
      cout << endl;
   }
}

int main() {
   srand((unsigned) time(NULL));

   const int NUM_OF_MATRICES = 1000;
   const int RUNS_PER_SET = 20;

   int cols, rows;

   cout << "Enter # of cols: ";
   cin >> cols;
   
   cout << "Enter # of rows: ";
   cin >> rows;

   int **matrixA = new int*[rows];
   int **matrixB = new int*[rows];

   for (int row = 0; row < cols; row++) {
      matrixA[row] = new int[cols];
      matrixB[row] = new int[cols];
   }

   for (int matrixNumber = 0; matrixNumber < NUM_OF_MATRICES; matrixNumber++) {
      getMatrixValues(matrixA, matrixB, rows, cols, matrixNumber);

      for (int runNumber = 0; runNumber < RUNS_PER_SET; runNumber++) {

         auto start = chrono::high_resolution_clock::now();

         multiplyMatrices(matrixA, matrixB, rows, cols);

         auto stop = chrono::high_resolution_clock::now();

         duration<double, chrono::milliseconds> ms_double = stop - start;
         cout << ms_double.count() << endl;
      }
   }

   return 0;
}