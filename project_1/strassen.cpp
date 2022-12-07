// strassen.cpp

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

void subtractMatrix(int **matrixA, int **matrixB, int **matrixC, int n) {
   for (int row = 0; row < n;row++) {
      for (int col = 0; col < n; col++) {
		   matrixC[row][col] = matrixA[row][col] - matrixB[row][col];
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

   // matrices for constants
   int **p = new int*[(n/2)];
   int **q = new int*[(n/2)];
   int **r = new int*[(n/2)];
   int **s = new int*[(n/2)];
   int **t = new int*[(n/2)];
   int **u = new int*[(n/2)];
   int **v = new int*[(n/2)];

   int **p1 = new int*[(n/2)];
   int **p2 = new int*[(n/2)];
   int **q1 = new int*[(n/2)];
   int **r1 = new int*[(n/2)];
   int **s1 = new int*[(n/2)];
   int **t1 = new int*[(n/2)];
   int **u1 = new int*[(n/2)];
   int **u2 = new int*[(n/2)];
   int **v1 = new int*[(n/2)];
   int **v2 = new int*[(n/2)];

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

      p[i] = new int[(n/2)];
      q[i] = new int[(n/2)];
      r[i] = new int[(n/2)];
      s[i] = new int[(n/2)];
      t[i] = new int[(n/2)];
      u[i] = new int[(n/2)];
      v[i] = new int[(n/2)];

      p1[i] = new int[(n/2)];
      p2[i] = new int[(n/2)];
      q1[i] = new int[(n/2)];
      r1[i] = new int[(n/2)];
      s1[i] = new int[(n/2)];
      t1[i] = new int[(n/2)];
      u1[i] = new int[(n/2)];
      u2[i] = new int[(n/2)];
      v1[i] = new int[(n/2)];
      v2[i] = new int[(n/2)];
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

   // compute constants
   
   // p1 = a11 + a22
   addMatrix(a11, a22, p1, n / 2);

   // p2 = b11 + b22
   addMatrix(b11, b22, p2, n / 2);

   // q1 = a21 + a22
   addMatrix(a21, a22, q1, n / 2);

   // r1 = b12 - b22
   subtractMatrix(b12, b22, r1, n / 2);

   // s1 = b21 - b11
   subtractMatrix(b21, b11, s1, n / 2);

   // t1  = a11 + a12
   addMatrix(a11, a12, t1, n / 2);

   // u1 = a21 - a22
   subtractMatrix(a21, a22, u1, n / 2);

   // u2 = b11 + b12
   addMatrix(b11, b12, u2, n / 2);

   // v1 = a12 - a22
   subtractMatrix(a12, a22, v1, n / 2);

   // v2 = b21 + b22
   addMatrix(b21, b22, v2, n / 2);

   // p = p1 * p2
   multiplyMatrices(p1, p2, p, n / 2);

   // q = q1 * b11
   multiplyMatrices(q1, b11, q, n / 2);

   // r = a11 * r1
   multiplyMatrices(a11, r1, r, n / 2);

   // s = a22 * s1
   multiplyMatrices(a22, s1, s, n / 2);

   // t = t1 * b22
   multiplyMatrices(t1, b22, t , n / 2);

   // u = u1 * u2
   multiplyMatrices(u1, u2, u, n / 2);

   // v = v1 * v2
   multiplyMatrices(v1, v2, v, n / 2);

   // c11 = p + s - t + v
   addMatrix(p, s, tempA, n / 2);
   addMatrix(t, v, tempB, n / 2);
   subtractMatrix(tempA, tempB, c11, n / 2);

   // c12 = r + t
   addMatrix(r, t, c12, n / 2);

   // c21 = q + s
   addMatrix(q, s, c21, n / 2);
   
   // c22 = p + r - q + u
   addMatrix(p, r, tempA, n / 2);
   addMatrix(q, u, tempB, n / 2);
   subtractMatrix(tempA, tempB, c22, n / 2);

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

      delete[] p[row];
      delete[] q[row];
      delete[] r[row];
      delete[] s[row];
      delete[] t[row];
      delete[] u[row];
      delete[] v[row];
   
      delete[] p1[row];
      delete[] p2[row];
      delete[] q1[row];
      delete[] r1[row];
      delete[] s1[row];
      delete[] t1[row];
      delete[] u1[row];
      delete[] u2[row];
      delete[] v1[row];
      delete[] v2[row];
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