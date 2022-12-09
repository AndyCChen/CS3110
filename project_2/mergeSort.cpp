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

void merge(int *array, int startIndex, int middleIndex, int endIndex) {

   // initialize subarray lengths
   int leftSubArrayLength = (middleIndex - startIndex) + 1;
   int rightSubArrayLength = endIndex - middleIndex;

   // create subarrays
   int *leftSubArray = new int[leftSubArrayLength];
   int *rightSubArray = new int[rightSubArrayLength];

   // copy values from left and right split into subarrays for sorting and merging
   for (int index = 0; index < leftSubArrayLength; index++) {
      leftSubArray[index] = array[startIndex + index];
   }

   for (int index = 0; index < rightSubArrayLength; index++) {
      rightSubArray[index] = array[middleIndex + index + 1];
   }

   // initialize subarray indexes
   int leftSubArrayIndex = 0, 
       rightSubArrayIndex = 0, 
       mergedArrayIndex = startIndex;
   
   // merge and sort subarrays
   while (leftSubArrayIndex < leftSubArrayLength && rightSubArrayIndex < rightSubArrayLength) {

      if (leftSubArray[leftSubArrayIndex] <= rightSubArray[rightSubArrayIndex]) {
         array[mergedArrayIndex] = leftSubArray[leftSubArrayIndex];

         leftSubArrayIndex++;
      } else {
         array[mergedArrayIndex] = rightSubArray[rightSubArrayIndex];

         rightSubArrayIndex++;
      }

      mergedArrayIndex++;
   }

   // copy left over items
   while (leftSubArrayIndex < leftSubArrayLength) {
      array[mergedArrayIndex] = leftSubArray[leftSubArrayIndex];

      leftSubArrayIndex++;
      mergedArrayIndex++;
   }

   while (rightSubArrayIndex < rightSubArrayLength) {
      array[mergedArrayIndex] = rightSubArray[rightSubArrayIndex];

      rightSubArrayIndex++;
      mergedArrayIndex++;
   }

   delete[] leftSubArray;
   delete[] rightSubArray;
}

void mergeSort (int *array, int startIndex, int endIndex) {

   // stop array spliting once array is divided into lengths of one
   if (startIndex >= endIndex) {
      return;
   }

   int middleIndex = startIndex + (endIndex - startIndex) / 2;

   mergeSort(array, startIndex, middleIndex);
   mergeSort(array, middleIndex + 1, endIndex);
   merge(array, startIndex, middleIndex, endIndex);
}

int main () {
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

   cout << "k-value: " << kValue << endl << endl;

   int *array = new int[arraySize];

   generateArrayValues(array, arraySize);

   auto start = chrono::high_resolution_clock::now();
   for (int i = 0; i < TOTAL_TEST_CASES; i++) {
      mergeSort(array, 0, arraySize - 1);
   }
   auto stop = chrono::high_resolution_clock::now();

   chrono::duration<double, std::milli> totalTime = stop - start;
   double executionTime = totalTime.count() / TOTAL_TEST_CASES;

   cout << "k-th smallest value: " << array[kValue - 1] << endl;
   cout << "Execution time: " << executionTime << " ms" << endl;

   delete[] array;

   return 0;
}