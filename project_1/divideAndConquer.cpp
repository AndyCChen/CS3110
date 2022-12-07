// divideAndConquer.cpp

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

void addMatrix(int **matrixA, int **matrixB, int **matrixC, int n) {
   for (int row = 0; row < n;row++) {
      for (int col = 0; col < n; col++) {
		   matrixC[row][col] = matrixA[row][col] + matrixB[row][col];
	   }
   }
}

void multiplyMatrices(int **matrixA, int **matrixB, int **matrixC, int n) {
   if (n == 1) {
      matrixC[0][0] = matrixA[0][0] * matrixB[0][0];
      return;
   }

   // sub-matrices for first matrix
   int **a11 = new int*[(n/2)];
   int **a12 = new int*[(n/2)];
   int **a21 = new int*[(n/2)];
   int **a22 = new int*[(n/2)];

   // sub-matrices for second matrix
   int **b11 = new int*[(n/2)];
   int **b12 = new int*[(n/2)];
   int **b21 = new int*[(n/2)];
   int **b22 = new int*[(n/2)];

   // sub-matrices for product matrix
   int **c11 = new int*[(n/2)];
   int **c12 = new int*[(n/2)];
   int **c21 = new int*[(n/2)];
   int **c22 = new int*[(n/2)];

   // temp storage for product of sub-matrices
   int **tempA = new int*[(n/2)];
   int **tempB = new int*[(n/2)];

   // allocate array for each row
   for (int i = 0; i < (n/2); i++) {
      a11[i] = new int[(n/2)];
      a12[i] = new int[(n/2)];
      a21[i] = new int[(n/2)];
      a22[i] = new int[(n/2)];

      b11[i] = new int[(n/2)];
      b12[i] = new int[(n/2)];
      b21[i] = new int[(n/2)];
      b22[i] = new int[(n/2)];

      c11[i] = new int[(n/2)];
      c12[i] = new int[(n/2)];
      c21[i] = new int[(n/2)];
      c22[i] = new int[(n/2)];

      tempA[i] = new int[(n/2)];
      tempB[i] = new int[(n/2)];
   }

   // divide matrices, assign values to each sub-matrix
   for (int row = 0; row < n / 2; row++) {
      for (int col = 0; col < n / 2; col++) {
         a11[row][col] = matrixA[row][col];
         a12[row][col] = matrixA[row][col + (n / 2)];
         a21[row][col] = matrixA[row + (n / 2)][col];
         a22[row][col] = matrixA[row + (n /2)][col + (n /2)];

         b11[row][col] = matrixB[row][col];
         b12[row][col] = matrixB[row][col + (n / 2)];
         b21[row][col] = matrixB[row + (n / 2)][col];
         b22[row][col] = matrixB[row + (n /2)][col + (n /2)];
      }
   }

   // recursive calls on sub-matrices
   multiplyMatrices(a11, b11, tempA, n / 2);
   multiplyMatrices(a12, b21, tempB, n / 2);
   addMatrix(tempA, tempB, c11, n / 2);

   multiplyMatrices(a11, b12, tempA, n / 2);
   multiplyMatrices(a12, b22, tempB, n / 2);
   addMatrix(tempA, tempB, c12, n / 2);

   multiplyMatrices(a21, b11, tempA, n / 2);
   multiplyMatrices(a22, b21, tempB, n / 2);
   addMatrix(tempA, tempB, c21, n / 2);

   multiplyMatrices(a21, b12, tempA, n / 2);
   multiplyMatrices(a22, b22, tempA, n / 2);
   addMatrix(tempA, tempB, c22, n / 2);

   // assign product sub-matrices back to product matrix
   for (int row = 0; row < n / 2; row++) {
      for (int col = 0; col < n / 2; col++) {
         matrixC[row][col] = c11[row][col];
         matrixC[row][col + (n / 2)] = c12[row][col];
         matrixC[row + (n / 2)][col] = c21[row][col];
         matrixC[row + (n / 2)][col + (n / 2)] = c22[row][col];
      }
   }

   // free memory
   for (int row = 0; row < (n/2); row++) {
      delete[] a11[row];
      delete[] a12[row];
      delete[] a21[row];
      delete[] a22[row];

      delete[] b11[row];
      delete[] b12[row];
      delete[] b21[row];
      delete[] b22[row];

      delete[] c11[row];
      delete[] c12[row];
      delete[] c21[row];
      delete[] c22[row];
      
      delete[] tempA[row];
      delete[] tempB[row];
	}
}

int main() {
   srand((unsigned) time(NULL));

   const int SETS = 1000;
   const int RUNS_PER_SET = 20;

   int n;

   cout << "Enter value for n: ";
   cin >> n;

   int **matrixA = new int*[n];
   int **matrixB = new int*[n];
   int **matrixC = new int*[n];

   for (int row = 0; row < n; row++) {
      matrixA[row] = new int[n];
      matrixB[row] = new int[n];
      matrixC[row] = new int[n];
   }

   double sumOfAverages = 0.0;

   // run 1000 sets
   for (int setCount = 0; setCount < SETS; setCount++) {
      // generate random values for matrices A & B
      getMatrixValues(matrixA, matrixB, n);

      auto start = chrono::high_resolution_clock::now();
      // run each set 20 times
      for (int runCount = 0; runCount < RUNS_PER_SET; runCount++) {
         multiplyMatrices(matrixA, matrixB, matrixC, n);
      }
      auto stop = chrono::high_resolution_clock::now();

      chrono::duration<double, std::milli> totalSetTime = stop - start;

      double setAverage = totalSetTime.count() / 20.0;
      sumOfAverages += setAverage;
   }

   double resultAverage = sumOfAverages / (double)SETS;

   cout << "Execution Time: "<< resultAverage << " " << "ms" << endl;

   return 0;
}