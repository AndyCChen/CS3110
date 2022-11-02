#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
   srand((unsigned) time(NULL));

   int cols, rows;

   cout << "Enter # of cols: ";
   cin >> cols;
   
   cout << "Enter # of rows: ";
   cin >> rows;

   cout << "Cols: " << cols << endl;
   cout << "Rows: " << rows << endl;

   return 0;
}