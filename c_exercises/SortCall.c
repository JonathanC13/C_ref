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

  int dupArray[size];

  for (int j = 0; j < size; j ++){
    dupArray[j] = comm_array[j];
  }

  printf("Array contains: ");
  printArray(comm_array, size);

  // Call Merge SOrt
  printf("\nUsing Merge Sort:\n");
  mergeSort(comm_array, size);

  printf("The sorted array contains: ");
  printArray(comm_array, size);
  printf("\n--\n");

  int *p;
  printf("\nMerge Sort with malloc\n");
  p = heapArray();
  printf("Sorted array contains: ");
  printArray(p, 4);
  printf("\n--\n");

  free(p);

  printf("\nQuick Sort\n");
  printf("Array contains: %d", size);
  printArray(dupArray, size);

  quickSort(dupArray, 0, size-1);
  printf("Sorted array contains: ");
  printArray(dupArray, size);
  //printf("%p what am i passing: ", (void *)&dupArr);
  printf("\n--\n");

  printf("Testing pointer values:");
  int *k;
  int m = 1;
  k = &m;
  printf("\nValue of k: %d\n", *k);
  printf("Address of k: %p\n", k);
  printf("What is this: %p", &k); // no idea
  printf("\nAddress of m: %p", &m);

  return 0;

}
