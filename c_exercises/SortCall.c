#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// include header file to use SeachAlg.c
#include "SearchAlg.h"
#include "SortAlg.h"

int main( int argc, const char* argv[] ) { // or const char **argv
  // argc is the number of arguments, including the program name
  // argv 1 to - are the command line arguments

  int size = argc - 1;
  int comm_array[size];
  int i_arg;

  for (int i = 0; i < size; i ++){
    i_arg = atoi(argv[i+1]);   // convert string to int
    comm_array[i] = i_arg;      // store into array
  }

  printf("Array contains: ");
  printArray(comm_array, size);

  // Call Merge SOrt
  printf("\nUsing Merge Sort:\n");
  mergeSort(comm_array, size);

  printf("The sorted array contains: ");
  printArray(comm_array, size);

  return 0;
}
