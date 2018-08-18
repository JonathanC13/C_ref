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
int insertionSort(int* p_Array, int size){


*/


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

        // split by space
        word = strtok(line, " ");
        // print individual words
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

void insertionSort(int *arr, int size){

  for(int a = 0; a < 6; a ++){
    printf("%d ", *(arr + a));
  }
  printf("\n");

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
