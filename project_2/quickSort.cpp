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
   cout << endl;
}

int partition(int *array, int startIndex, int endIndex) {
   int pivot = array[endIndex];


}

void selectWithQuickSort(int *array, int startIndex, int endIndex) {
   if (startIndex < endIndex) {
      int pivotIndex = partition(array, startIndex, endIndex);

      selectWithQuickSort(array, startIndex, pivotIndex);
      selectWithQuickSort(array, pivotIndex + 1, endIndex);
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



   return 0;
}