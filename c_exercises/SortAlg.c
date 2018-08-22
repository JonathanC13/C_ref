#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef char *string;
#include <ctype.h>

#include "SearchAlg.h" // use strip

/* Inputs

// TO return an array, must be a pointer to a static array.
//https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm
int *bubbleSort()
  // Using char *fgets(char *str, int n, FILE *stream) reads a line from the specified stream and stores it into the string pointed to by str. It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.

// pass pointer to array
// Using fgetc to grab words
int insertionSort(int* p_Array, int size)

// Main will get the data through command line and pass a pointer to that array to this function.
void mergeSort(int *array, int size)


*/

void printArray(int arr[], int size){

  printf("\n");
  int i;
  for (i=0; i < size; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");

}

// Reads data from file, puts them in an array and strips.
// Input: null
// Output: null
int *bubbleSort(){
  int size = 9;

  int elem[size];  // must know the size of the array

  static int retArray[9]; // static cannot be sorted so sort then copy
  // static so it can be returned.
  // for static the size must be a constant.

  int index = 0;

  char *strip_;
  char symbols[3] = "\n, ";   // strip new line and , and space

  char line[20];

  char *word;
  int i_word;
  // Open file
  // 1. FILE pointer to keep track of the file being accesses.
  FILE *fp;

  // 2. Returns a file pointer to the specified file`
  fp = fopen("arr_linesDelim.txt", "r");

  if(fp == NULL) {
      perror("Error in opening file.");

  } else {

    while (fgets(line, sizeof(line), fp)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        //printf("%s\n", line);

        // get line and is split by a space
        word = strtok(line, " ");
        // print individual words
        // that are split by the space
        while (word != NULL){

          //i_word = (int)(*(word));
          //printf("%d\n", i_word);

          strip_ = strip_chars(word, symbols);  // Rid or undesired symbols
          //printf("%s\n", strip_);

          i_word = atoi(strip_);  // conver to int, to keep more than 1 digit
          elem[index] = i_word;
          index ++;

          word = strtok(NULL, " "); // move the pointer
        }
    }

    //for(int a = 0; a < size; a ++){
    //  printf("%d\n", elem[a]);
    //}

    // Do the bubble sort

    int swaps;
    int temp; // for swaps

    while(swaps != 0){
      swaps = 0;

      for (int m = 0; m < size-1; m++){ // < size - 1 due to stop before second last since we check pairs

        if(elem[m] > elem[m+1]){
          swaps ++;
          temp = elem[m];
          elem[m] = elem[m+1];
          elem[m+1] = temp;
        }

      }

    }


    //for(int a = 0; a < size; a ++){
    //  printf("%d\n", elem[a]);
    //}

    // copy the sorted array to the static array to be returned
    for (int in = 0; in < size; in ++){
      retArray[in] = elem[in];
    }

  }
  return retArray;

}

//shifting for insertion sort forward
// index to place and shiftTO place
void shiftArrFor(int *arr, int index, int shiftTo){
  int temp = arr[shiftTo];

  for (int k = shiftTo; k >= index; k--){
    *(arr+k) = *(arr+k-1);
    //arr[k] = arr[k-1];
  }
  arr[index] = temp;
}

// Insertion sort chooses the compare element starting from the base and compares it to each element on the left.
// If an element is lower then it is moved to the wall that divides the ordered and non-ordered parts of the array.
// When it reaches the comparing value, it is moved to the correct position, the wall.
// Inputs: pointer to array: int *, size of aaray: int
// Output: null
void insertionSort(int *arr, int size){

  printArray(arr, size);

  int insertions = 0;

  // current element to move
  for (int curr = 0; curr < size; curr ++){
    // iterate through the array
  //  printf("Current: %d\n", curr);
    for (int iter = 0; iter < curr; iter ++){
      //printf("iter: %d\n", iter);
      // if less than curr index check if elem[curr] is less than to place
      if (iter != curr){
        if(*(arr + curr) < *(arr + iter)){

          // if curr value is less than the value at iter, then place on left
          shiftArrFor(arr, iter, curr);
          //printf("\n Placing at index: %d and shifting to: %d \n", iter, curr);
          break;

        }
      }
    }
  }
}


void orderAndMerge(int *array, int left, int mid, int right);

// Merge sort, halve the array elements until the smallest groups of 1 element. Then compares and orders pairs of groups as it merges back into one complete set.
// Since the array is filled through the command line, just pass the pointer to the array here
// Input: array pointer: int *
// Output: null
void mergeSort(int *array, int size){

  // currnet divided group size
  int curr_groupSize;

  // First index of left group
  int left_index;

  // Loop for increasing the group size until one complete set. It doubles since merging pairs of groups each time
  for (curr_groupSize = 1; curr_groupSize < size; curr_groupSize = 2 * curr_groupSize){

    // inner loop to split the smaller groups so they can be ordered.
    for (left_index = 0; left_index < size-1; left_index = left_index + (2*curr_groupSize)){

      // Find the midpoint of the pair to distiguish the left and right groups
      int mid = left_index + curr_groupSize -1;

      // Determine the end index for the right group
      int right = int_min(mid + (2*curr_groupSize) -1, size - 1);

      // order and merge the 2 groups
      orderAndMerge(array, left_index, mid, right);

    }
  }
}

void orderAndMerge(int *array, int left, int mid, int right){

  int i;  //
  int j;  //
  int k;  // used for indexing the arrays

  int n1 = mid - left + 1;  // number of elements in left array
  int n2 = right - mid;     // number of elements in right array

  // temporary arrays for the groups;
  int L_arr[n1];
  int R_arr[n2];

  // copy the data into the temporary arrays so we can compare
  for (i = 0; i < n1; i++){
    L_arr[i] = array[left + i];
  }
  for (j = 0; j < n2; j ++){
    R_arr[j] = array[mid + 1 + j];
  }

  // copy the temp arrays back to the array indexes it was taken from, but in order.
  // array[l to r]

  i = 0; j = 0; k = left;  // k = l to keep track in original array

  while(i < n1 && j < n2){

    if (L_arr[i] <= R_arr[j]){


        array[k] = L_arr[i];
        i ++; // keep track of which element has been add (replace) back to the original array

    } else {

      array[k] = R_arr[j];
      j ++;
    }

    k ++;
  }

  // After comparing and replacing values in the ariginal array, there may be elements in the temporary arrays that are left over due to one group using all its elements.
  while (i < n1){
    // copying remaining left side first, if there is any
    array[k] = L_arr[i];
    i ++;
    k ++;
  }

  // Right elements if any remaining
  while (j< n2){

    array[k] = R_arr[j];
    j ++;
    k ++;

  }

}
