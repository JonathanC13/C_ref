#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef char *string;
#include <ctype.h>

#include "SearchAlg.h" // use strip

/* Inputs

// TO return an array, must be a pointer to a static array.
int *bubbleSort()
  // Using char *fgets(char *str, int n, FILE *stream) reads a line from the specified stream and stores it into the string pointed to by str. It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.


*/


int *bubbleSort(){
  int size = 9;

  int elem[size];  // must know the size of the array
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

    for(int a = 0; a < size; a ++){
      printf("%d\n", elem[a]);
    }

  }
}
