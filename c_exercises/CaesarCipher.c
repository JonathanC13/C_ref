#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

/*
// binary Search
// Input: (1D array passed by pointer: int, search value:int, array size:int)
// return: index of found:int
int binarySearch(int* p_Array, int target, int size){
*/
#include "SearchAlg.h"  // for binary search

void createEncryptionPattern(char *normal, char *arr, int key){

  int lowerCaseOffset = 96;

  int letterSize = 26; // 0 to 25

  //fill  normal alphabet array
  for (int a = 0; a < letterSize; a ++){
    normal[a] = a + lowerCaseOffset + 1;
  }

  // Ascii range for lower case letters
  int letterMin = 97;
  int letterMax = 122;

  int letter;
  int index = -1;

  // fill the encryption pattern
  for(int i = 0; i < letterSize; i ++){

    index ++;
    letter = key + index + lowerCaseOffset;  // offset for ascii char

    //printf("%c and %d.\n", letter, letter);
    if (letter > letterMax ){
      index = 1;
      key = 0;
      letter = letterMin;
    }
    arr[i] = letter;  // letter to the encryption array
  }


  //printf("\nEncryption pattern: %s \n", arr);
  /*
  printf("char by char:\n");
  for(int k = 0; k <= letterSize; k ++){
    printf("%c ", arr[k]);
  }
  */
}

// Determine the encrytion pattern, fill the encrypted message array, and return the key so it can be deciphered.
// Input: input:arr[], The original user input.
// Output: randPos:int, xreturn the key so the message can be deciphered
int encrypt(char *input, char *encrypted){

  time_t t;
  // initialize random number generator
  srand((unsigned) time(&t));

  int alphabetSize = 26; // 0 to 25
  int shift = (rand() % alphabetSize);  // Get random shift number for the encryption patter

  char encryptPattern[alphabetSize];  // array to be filled with the encryption pattern
  char normalAlpha[alphabetSize];

  //size_t sizeCheck = sizeof(encryptPattern) / sizeof(char);

  //printf("\n The SIZE is: %d\n", sizeCheck);

  // call creation function
  createEncryptionPattern(normalAlpha, encryptPattern, shift);
  encryptPattern[26] = '\0';
  normalAlpha[26] = '\0';

  int patternIndex;

  printf("Reg: %s\n",normalAlpha);
  printf("Enc: %s\n", encryptPattern);

  int end;

  // Encrypt the message
  for (int m = 0; input[m] != '\0'; m ++){
    end = m;
    if(input[m] == ' '){
      printf("input char %c.\n", input[m]);
      encrypted[m] = ' ';
      continue;
    }

    // find location of alphabet letter in normal alphabet
    printf("input char %c.\n", input[m]);
    patternIndex = char_binarySearch(normalAlpha, input[m], alphabetSize);
    // now look at the same index in the encryption pattern and add the letter
    encrypted[m] = encryptPattern[patternIndex];
    printf("changed to: %c\n", encrypted[m]);
  }

  encrypted[end] = '\0'; // end the string

  return shift; // return cipher key


}

// get user input text, encrypt is with the cipher, then decode it and display.
// Input: null
// Output: 0 on success
int main(){

  char userText[100]; //initilize memory for char array for user input
  char encryptedMsg[100]; // initialize array for the encrypted message.

  printf("Type the message you would like to be put through the cipher and then deciphered: ");
  fgets(userText, sizeof userText, stdin); // use fgets to be buffer overflow safe. Get user input from command line
  printf("\n");

  // convert all letters to lower case for cipher
  for (char *p = userText; *p == '\0'; p++ ){
    *p = tolower(*p);
  }

  // encrypt the message, get the key for the cipher
  int key = encrypt(userText, encryptedMsg);

  printf("\nThe key is: %d.\n", key);
  printf("Encrypted message: %s \n", encryptedMsg);

  return 0;
}
