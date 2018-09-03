#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// include header file to use SeachAlg.c
#include "SearchAlg.h"
#include "SortAlg.h"

void printName(char addon[]){

  char space[2] = " ";
  char name[5] = "Name";
  strcat(name,space);

  strcat(name,addon);

  printf("1. %s.\n", name);
}

void reverseString(char *rev){

  // Passing the array with a pointer causes sizeof to only get the size of the pointer variable
  //size_t n = sizeof(rev)/sizeof(char);
  //Must loop through.

  //char dupArr[5];
  int size = 0; // size
  for (char *t = rev; *t != '\0'; t ++){
    //dupArr[size] = *t;
    size ++;
  }

  //printf("duplicate %zu and %s", sizeof(dupArr), dupArr);

  char reverseArr[size];

  for (int i = 0; i < size; i ++){
    reverseArr[i] = rev[size - i - 1];
  }

  reverseArr[size] = 0;

  printf("2. Reversed is: %s \n", reverseArr);
}

void rectangle_Area_Perim(int length, int width){

  int perimeter = (2* length) + (2 * width);
  int area = length * width;

  printf("3. The perimeter is %i and the area is %i.\n", perimeter, area);

}

void distance(int x1, int y1, int x2, int y2){

  double x_plane = x1 - x2;
  double y_plane = y1 - y2;

  float dist = sqrt(pow(x_plane,2) + pow(y_plane,2));

  printf("4. The distance is %.2f.\n", dist);

}


void remove_element(int *array, int index, int array_length);

void lessThan5(int *list){
  int index = 0;
  int removed = 0;
  //for (int *t = list; *t != '\0'; t ++){
  for (int y = 0; y < 10; y ++){
    if (list[index] >= 5){
      //printf("removing: %i", list[index]);
      remove_element(list, index, 10);
      removed ++;

    }
    else {
      index ++;
    }
  }
  list[10 - removed] = 0;
}
void remove_element(int *array, int index, int array_length)
{
   int i;
   for(i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}

void divisors(int in){
  int divideList[in-1];

  int pos = 0;
  for (int x = 2; x < in+1; x++){
    divideList[pos] = x;

    //printf("%i ", divideList[pos]);
    pos ++;
  }

  printf("6. ");
  for (int z = 0; z < in-1; z ++){
    if((in % divideList[z]) == 0){
      printf(":%i ", divideList[z]);
    }
  }
  printf("\n");

}

void listOverlap(){


  int a[11] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
  int b[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 89};
  int c[11];
  int dup = 0;

  int new = 0;
  printf("7. ");
  for (int x = 0; x < 11; x ++){
    for (int y = 0; y < 13; y ++){
      if (a[x] == b[y]){
        for (int z = 0; z < 11; z ++){
          if (a[x] == c[z]){
            dup = 1;
            break;
          }
        }

        if(dup == 0){
          c[new] = a[x];
          new ++;
          printf(":%i ", a[x]);
        }
        dup = 0;
      }
    }
  }

  printf("\n");

}

void stringToUl(){
  char buffer[123] = "155";
  unsigned long ul;
  //printf ("8. Input an unsigned number: ");
  //fgets (buffer,123,stdin);

  ul = strtoul (buffer,NULL,0);
  printf ("8. Output: %lu\n",ul);

  /*char input[] = "8.0 2.0";
		char * ptr_end;
		double x, y;

		x = strtod (input,&ptr_end);
		y = strtod (ptr_end,NULL);
  */

}

void sortArr(int *list){

  int temp = 0;
  int sorted = 0;

  while (sorted == 0){
    sorted = 1;
    for(int x = 0; x < 6; x++){
      if((x+1) < 6){
        if (list[x] > list[x+1]){
          sorted = 0;
          temp = list[x+1];
          list[x+1] = list[x];
          list[x] = temp;
        }
      }
    }
  }

}

void quotient_remainder(){
  long int n = 10;
  long int d = 3;
  ldiv_t result;

  result = ldiv (n,d);
  printf ("10. quotient =  %ld, remainder = %ld.\n\n",result.quot,result.rem);

}

void callocBlock()
{
  int i,n,num;
  int * my_array;

  printf("11. ");
  printf("\nInput the number of elements to be stored in the array :");
  //scanf("%d",&n);
  n = 3;

  printf("Input %d elements in the array :\n",n);

  my_array = (int*) calloc ( n,sizeof(int) );
  if (my_array==NULL)
  {
    printf (" Requested memory allocation is wrong.");
    exit (1);
  }
  for ( i=0; i<n; i++ )
  {
    printf (" element %d : ",i+1);
    //scanf ("%d",&my_array[i]);
    my_array[i] = 6;
  }
  printf (" Values entered in the array are : \n");
  for ( i=0; i<n; i++ )
    printf (" %d ",my_array[i]);
    printf ("\n\n");
  free (my_array);

}

void string_to_wordsWtoken(){
	int size = 100;
	char str1[size];
	char* word;

	char* word_arr[size];

	printf("Using token, get words from string: ");
	// get the string from user
	fgets(str1, sizeof(str1), stdin);

	// split the string by space
	word = strtok(str1, " ");

	int i = 0;
  int new_size = 0;
	// put words in an array
	while(word != NULL){
    new_size ++;
		word_arr[i] = word;
		i ++;
		// move pointer
		word = strtok(NULL, " ");
	}

  char* storedWords[new_size];

  // copy to smaller array
  for(int r = 0; r < new_size; r++){
    storedWords[r] = word_arr[r];
  }

	printf("Array of size %d of words contains: ", new_size);
	for (int k = 0; k < new_size; k ++){
		printf("%s\n", storedWords[k]);
	}
	printf("\n");

  printf("address of array %p", storedWords[0]);
	char *letter;
	int count = 0;
	printf("Find the number of occurrences of 'the'\n");


  for(int m = 0; m < new_size; m ++){
		letter = storedWords[m]; // point to the start address of word_arr[m], skip words`
    printf("%d. address of pointer to array: %p\n", m, letter);
		if(*letter == 't'){
      printf("%c \n", *letter);
			letter ++;             // increment the letters in the word

			if(*letter == 'h'){
        printf("%c \n", *letter);
				letter ++;
				if(*letter == 'e'){
          printf("%c \n", *letter);
					letter++;
					if(*letter == '\0' || *letter == '\n'){
            printf("%c \n", *letter);
						count ++;
					}

				}
			}
		}
	}

	printf("The number is: %d\n", count);
}

void string_to_wordReg(){
  char str1[100];
  char newString[10][10];
  int i,j,ctr;
     printf("\n\n Split string by space into words :\n");
     printf("---------------------------------------\n");

  printf(" Input  a string : ");
  fgets(str1, sizeof str1, stdin);

  j=0; ctr=0;
  for(i=0;i<=(strlen(str1));i++)
  {
      // if space or NULL found, assign NULL into newString[ctr]
      if(str1[i]==' '||str1[i]=='\0')
      {
          newString[ctr][j]='\0';
          ctr++;  //for next word
          j=0;    //for next word, init index to 0
      }
      else
      {
          newString[ctr][j]=str1[i];
          j++;
      }
  }
  printf("\n Strings or words after split by space are :\n");
  for(i=0;i < ctr;i++)
      printf(" %s\n",newString[i]);

	
	// reverse the order of the words
	char revWords[ctr];
	
	for(int n = 0; n < ctr; n ++){
		// try strcpy
		strcpy(revWords[n], newString[ctr-n-1];
		//revWords[n] = newString[ctr- n - 1];	
	}
	
	printf("\n Words in reverse are: \n");
  	for(i=0;i < ctr;i++)
      		printf(" %s\n",revWords[i]);
		       
	printf("\n");

	int count = 0;
	int letter = 0;
	printf("Find the number of occurrences of 'the'\n");
		       
	

  for(int m = 0; m < ctr; m ++){

    letter = 0;
    if(newString[m][letter] == 't'){
      printf("%c \n", newString[m][letter]);
      letter ++;
      if (newString[m][letter] == 'h'){
        printf("%c \n", newString[m][letter]);
        letter ++;
        if (newString[m][letter] == 'e'){
          printf("%c \n", newString[m][letter]);
          letter ++;
          if(newString[m][letter] == '\0' || newString[m][letter] == '\n'){
            count ++;
          }
        }
      }
    }
  }
	printf("The number is: %d\n", count);
}

// ranges in decimal
struct ascii_ranges{
	int min;
	int max;
	int count;
};

void count_ascii(){
	char arr[20] = "avsopo123";

	// just checking size
	int sizeofArr = (sizeof(arr)/sizeof(arr[0]));
	printf("Array of size %d: \n", sizeofArr);

	struct ascii_ranges lower_alpha_ranges = {97, 122, 0};
	struct ascii_ranges digit_ranges = {48, 57, 0};

	// struct array
	struct ascii_ranges all_ranges[2];
	all_ranges[0] = lower_alpha_ranges;
	all_ranges[1] = digit_ranges;

	for (char *p = arr; *p != '\0'; p ++){
		for(int j = 0; j < 2; j ++){
			if (all_ranges[j].min <= *p && all_ranges[j].max >= *p){
				all_ranges[j].count ++;
				break;
			}
		}
	}

	printf("Final count of alphabet: %d\n",all_ranges[0].count );
	printf("Final count of digits: %d\n",all_ranges[1].count );
	printf("\n");
}

void compare_strings(){
	char str1[20] = "Hello";
	char str2[20] = "Hello";

	printf("Comparing strings\n");
	int same_flag = 1;
	int i = 0;
	while(str1[i] != '\0'){
		if(str1[i] != str2[i]){
			same_flag = 0;
			break;
		}
    i ++;
	}

  if ((str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0')){
    same_flag = 0;
  }

	if(same_flag == 0){
		printf("The strings are not the same.\n");

	} else {
		printf("The strings are the same\n");
	}
	printf("\n");
}
		       
// sort alphabetically		      
void bubbleSortWords(char *arr, int size){
	
	int swaps;
	char temp[10];
	
	for (int i = 0; i < size-1; i ++){
		// just checking first letter
		if(arr[i][0] > arr[i+1][0]){
			strcpy(temp, arr[i+1]);
			strcpy(arr[i+1], arr[i]);
			strcpy(arr[i], temp);
		}
	}
	
	printf("Sorted alphabetically\n");
	for(int k = 0; k < size; k ++){
		printf("%s ", arr[k]);	
	}
	
}	

//int ndays, y, m, d;
//printf("Input no. of days: ");
//scanf("%d", &ndays);

//char inputString[3] = {'A','B','C'};
//for (char *t = inputString; *t != '\0'; t ++){
//  printf("%c ", *t);
//}

/*
    int number, input;
		/* initialize random seed:
		srand ( time(NULL) );
		/* Generate a random number:
		number = rand() % 10 + 1;
*/

//		atexit (newFunctionOne);  functions executed upon program termination
//		atexit (newFunctionTwo);

int main(){

	//string_to_wordsWtoken();
	//string_to_wordReg();
	//count_ascii();
	compare_strings();
	
	int w_arrSize = 4;
	char* wordArray[w_arrSize] = {"Banana", "Apple", "Zoo", "Tool"};
	// need to pass size because when passed as an argument it is the pointer not the whole array				   
	bubbleSortWords(wordArray, w_arrSize);
/*
  // Ex 1
  char addon[3] = "HI";
  printName(addon);

  // Ex 2
  // 3 char with /0 as terminating
  char inputString[4] = {'A','B','C','\0'};
  reverseString(inputString);

  // Ex 3
  rectangle_Area_Perim(2,3);

  // Ex 4
  distance(25,15,35,10);

  // Ex 5
  int list10[10] = {1,2,3,4,5,6,7,8,9,10};
  lessThan5(list10);
  printf("5. ");
  for (int i = 0; list10[i] != 0; i++){
    printf("%i ", list10[i]);
  }
  printf("\n");

  // Ex 6
  //int input; printf("INPUT: "); scanf("%i", &input);
  divisors(10);

  // Ex 7
  listOverlap();

  // Ex 8
  stringToUl();

  // Ex 9
  int sort[6] = {5,15,100, 55, 60, 45};
  sortArr(sort);
  printf("9. ");
  for(int a = 0; sort[a] != 0; a++){
    printf(":%i ", sort[a]);
  }
  printf("\n");

  // Ex 10
  quotient_remainder();

  // Ex 11
  callocBlock();

  // Ex 12
  // Linear Search
  printf("Searching ===\n");
  int bb = -1;
  int *retIndex;
  retIndex = &bb; // initialize pointer to this address

  int linArray[6] = {5,15,50, 55, 60, 100};
  int target = 100;
  // passing a pointer
  linearSearch(linArray, target, retIndex);
  printf("12. The target found at index: %d\n", *retIndex);

  // Ex 13
  // Binary Search. Array must be a sorted array
  int binRet;
  binRet = binarySearch(linArray, 50, sizeof(linArray)/sizeof(int));
  if (binRet != -1){
    printf("13. Binary Search return index: %d\n", binRet);
  } else {
    printf("13: Binary. Not found.");
  }

  // Ex 14
  // Jump Search, Array must be sorted array

  // target
  int cc = 9;    // allocate to some address
  int *cp = &cc;  // point to the address and pass it

  printf("Ex 14. ");
  jumpSearch(cp, 7);

  printf("\nSorting ===\n");

  printf("Ex 15: Bubble. \n");
  int *dd;  // pointer for return
  dd = bubbleSort();

  for(int a = 0; a < 9; a ++){
    printf("%d ", *(dd + a));
  }

  printf("\n\nEx 16: Insertion sort. \n");

  int Ins_arr[6] = {5, 4, 6, 7, 1, 0};
  insertionSort(Ins_arr, 6);
  for(int a = 0; a < 6; a ++){
    printf("%d ", *(Ins_arr + a));
  }

  // binary search number 12
  // https://www.w3resource.com/c-programming-exercises/variable-type/index.php

  return 0;
  */
}
