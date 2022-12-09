#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;

void generateArrayValues (int *array, int arrayLength) {
   for (int index = 0; index < arrayLength; index++) {
      array[index] = rand() % 1000;
   }
}

void printArray (int *array, int arrayLength) {
   for (int index = 0; index < arrayLength; index++) {
      cout << array[index] << " ";
   }
   cout << endl << endl;
}

int partition(int *array, int startIndex, int endIndex) {
   int indexOfPivotValue = endIndex;
   int pivotPosition = startIndex;

   // find first value that is greater than the pivot
   for (int n = startIndex; n <= endIndex; n++) {
      if (array[n] >= array[indexOfPivotValue]) {
         pivotPosition = n;
         break;
      }
   }

   for (int n = pivotPosition + 1; n < endIndex; n++) {
      if (array[n] <= array[indexOfPivotValue]) {
         int valueToSwap = array[pivotPosition];
         array[pivotPosition] = array[n];
         array[n] = valueToSwap;

         pivotPosition++;
      }
   }

   int valueToSwap = array[pivotPosition];
   array[pivotPosition] = array[indexOfPivotValue];
   array[indexOfPivotValue] = valueToSwap;

   return pivotPosition;
}

int selectKthSmallestWithQuickSort(int *array, int startIndex, int endIndex, int kValue) {
   int pivotIndex = partition(array, startIndex, endIndex);

   // keep partitioning array until the pivot position is equal to the kValue
   while (kValue < pivotIndex + 1 || kValue > pivotIndex + 1) {

      // partition values left of pivot
      if ( kValue < pivotIndex + 1) {
         pivotIndex = partition(array, startIndex, pivotIndex - 1);
      }
      // partition values right of the pivot
      else if (kValue > pivotIndex + 1) {
         pivotIndex = partition(array, pivotIndex + 1, endIndex);
      }
   }

   return array[pivotIndex];
}

int main() {
   const int TOTAL_TEST_CASES = 10000;

   unsigned seed = 202038;
   srand(seed);

   int arraySize, choice, kValue;

   cout << "Enter value for n: ";
   cin >> arraySize;

   cout << endl;

   cout << "Select a k value to use." << endl;
   cout << "1. k = 1" << endl;
   cout << "2. k = n/4" << endl;
   cout << "3. k = n/2" << endl;
   cout << "4. k = 3n/4" << endl;
   cout << "5. k = n" << endl;
   cin >> choice;

   switch (choice) {
      case 1:
         kValue = 1;
         break;
      case 2: 
         kValue = arraySize / 4;
         break;
      case 3:
         kValue = arraySize / 2;
         break;
      case 4:
         kValue = (arraySize * 3) / 4;
         break;
      case 5:
         kValue = arraySize;
         break;
      default:
         kValue = 1;
   }

   int *array = new int[arraySize];

   generateArrayValues(array, arraySize);

   int kthSmallestValue;

   cout << "k-value: " << kValue << endl;

   auto start = chrono::high_resolution_clock::now();
   for (int i = 0; i < TOTAL_TEST_CASES; i++) {
      kthSmallestValue = selectKthSmallestWithQuickSort(array, 0, arraySize - 1, kValue);
   }
   auto stop = chrono::high_resolution_clock::now();

   chrono::duration<double, std::milli> totalTime = stop - start;

   double executionTime = totalTime.count() / TOTAL_TEST_CASES;

   cout << "k-th smallest value: " << kthSmallestValue << endl;
   cout << "Execution time: " << executionTime << " ms" << endl;

   delete[] array;

   return 0;
}