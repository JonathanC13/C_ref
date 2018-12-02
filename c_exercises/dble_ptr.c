/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// Tip for modifying variables
/*
void change(int* p){
    *p = 6;
}

int main()
{
    int *p;
    int c = 99;
    p = &c;

    change(p); // need to pass address

    printf("\n%i", *p);
    return 0;
}

also with just address
    int p = 55;
    change(&p); works
*/

// For modifying just the values and no resizing or changing pointer value, can just do:
/*
void change(int *arr){
  arr[0] = 1; // or *(arr + 0) = 1;
}
// main call
int arr[2] = {2,1};
change(arr)
*/

// Also can have a double pointer like:
/*
  void what(int *arr, int length){
  }
  // main call
  int *ptr = calloc
  what(&ptr); // pass address

  creates double pointer:
    [arr]        [ptr]        [var]
    val   --+    val  --+     val (elem[0])
    addr    \--> addr   \-->  addr
*/

void what(int **arr, int length){

    int new_len = length - 1;

    printf("\n what \n");
    printf("**arr: value = %p and addr = %p.\n", arr, &arr);


        int* tmp = calloc(new_len, sizeof(int));

        printf("\n tmp \n");
        printf("*tmp: value = %i and addr = %p.\n", tmp[0], &tmp[0]);

      int i;
      for (i = 0; i < new_len; i++)
      {
        *(tmp+i) = 5;
      }
      printf("free: %p.", *arr);
      free(*arr);
      *arr = tmp;
      printf("\n new \n");
        printf("*arr: value = %p and addr = %p.\n", *arr, &(*arr));
}


int main()
{
    int length = 3;
      int* test = calloc(length, sizeof(int));
      test[0] = 1;
      test[1] = 2;
      test[2] = 3;


      printf("\nVar: value = %i and addr = %p.\n", test[0], &test[0]);
      printf("test ptr: value = VarAddr = %p and addr = %p.\n", test, &test);


      what(&test, length);

      int new_len = sizeof(test)/sizeof(int);
      printf("\n main: \n");
      for(int i = 0; i < new_len; i++){
          printf("%i, ", test[i]);
      }

    return 0;
}
