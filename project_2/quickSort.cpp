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

void selectWithQuickSort(int *array, int startIndex, int endIndex, int kValue) {
   // return when base case is reached
   if (startIndex > endIndex) {
      return;
   }

   int pivotIndex = partition(array, startIndex, endIndex);

   if (kValue < pivotIndex + 1) {
      selectWithQuickSort(array, startIndex, pivotIndex - 1, kValue);
   } else if (kValue > pivotIndex + 1) {
      selectWithQuickSort(array, pivotIndex + 1, endIndex, kValue);
   } else {
      cout << "k-th smallest value: " << array[pivotIndex] << endl;
   }

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

   printArray(array, arraySize);

   cout << "k-value: " << kValue << endl;

   selectWithQuickSort(array, 0, arraySize - 1, kValue);

   delete[] array;

   return 0;
}