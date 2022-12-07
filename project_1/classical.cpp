// classical.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

void getMatrixValues(int **matrixA, int ** matrixB, int n) { 
   for (int n = 0; n < n; n++) {
      for (int n = 0; n < n; n++) {
         matrixA[n][n] = rand() % 10;
         matrixB[n][n] = rand() % 10;
      }
   }
}

void multiplyMatrices(int **matrixA, int ** matrixB, int **resultMatrix, int n) {
   for (int row = 0; row < n; row++) {
      for (int col = 0; col < n; col++) {
         for (int k = 0; k < n; k++) {
            resultMatrix[row][col] += matrixA[row][k] * matrixB[k][col];
         }
      }
   }
}

int main() {
   srand((unsigned) time(NULL));

   const int SETS = 1000;
   const int RUNS_PER_SET = 20;

   int n;

   cout << "Enter value for n:: ";
   cin >> n;

   int **matrixA = new int*[n];
   int **matrixB = new int*[n];
   int **resultMatrix = new int*[n];

   for (int row = 0; row < n; row++) {
      matrixA[row] = new int[n];
      matrixB[row] = new int[n];
      resultMatrix[row] = new int[n];
   }

   double sumOfAverages = 0.0;
   // run 1000 sets
   for (int setCount = 0; setCount < SETS; setCount++) {
      getMatrixValues(matrixA, matrixB, n);

      // run each set 20 times
      auto start = chrono::high_resolution_clock::now();
      for (int runCount = 0; runCount < RUNS_PER_SET; runCount++) {
         multiplyMatrices(matrixA, matrixB, resultMatrix, n);
      }
      auto stop = chrono::high_resolution_clock::now();

      chrono::duration<double, std::milli> totalSetTime = stop - start;

      double setAverage = totalSetTime.count() / 20.0;
      sumOfAverages += setAverage;
   }

   double resultAverage = sumOfAverages / 1000.0;

   cout << "Execution Time: "<< resultAverage << " " << "ms" << endl;

   return 0;
}