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

void createEncryptionPattern(char *normal, char *arr_encryption, int key){

  // Ascii range for lower case letters
  int letterMin = 97;
  int letterMax = 122;


  int letterSize = 26; // 0 to 25

  //fill  normal alphabet array, abcdefghijklmnoqrstuvwxyz
  for (int a = 0; a < letterSize; a ++){
    normal[a] = a + letterMin;
  }

  normal[letterSize] = '\0';

  int letter;
  int index = -1;

  // fill the encryption pattern
  for(int i = 0; i < letterSize; i ++){

    index ++;
    letter = key + index + letterMin;  // offset for ascii char

    //printf("%c and %d.\n", letter, letter);
    if (letter > letterMax ){
      index = 0;
      key = 0;
      letter = letterMin;
    }
    arr_encryption[i] = letter;  // letter to the encryption array
  }

  arr_encryption[letterSize] = '\0';

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

  int alphabetSize = 26; // 0 to 25, if shift 26 then normal alphabet
  int shift = (rand() % alphabetSize);  // Get random shift number for the encryption patter

  char encryptPattern[alphabetSize];  // array to be filled with the encryption pattern
  char normalAlpha[alphabetSize];

  //size_t sizeCheck = sizeof(encryptPattern) / sizeof(char);

  //printf("\n The SIZE is: %d\n", sizeCheck);

  // call creation function
  createEncryptionPattern(normalAlpha, encryptPattern, shift);
  //encryptPattern[26] = '\0';
  //normalAlpha[26] = '\0';

  int patternIndex;

  printf("Reg: %s\n",normalAlpha);
  printf("Enc: %s\n", encryptPattern);

  int end;

  // Encrypt the message
  for (int m = 0; input[m] != '\0'; m ++){
    end = m;
    if(input[m] == ' '){
      //printf("input char %c.\n", input[m]);
      encrypted[m] = ' ';
      continue;
    }

    // find location of alphabet letter in normal alphabet
    //printf("input char %c.\n", input[m]);
    patternIndex = char_binarySearch(normalAlpha, input[m], alphabetSize);
    // now look at the same index in the encryption pattern and add the letter
    encrypted[m] = encryptPattern[patternIndex];
    //printf("changed to: %c\n", encrypted[m]);
  }

  encrypted[end] = '\0'; // end the string

  return shift; // return cipher key


}

// Get the encypted message and the key then decrypt it for the user
// Input: encryptedMsg: char array; deciphered: char array; key: int
// Output: retunrn 0 on success
int decrypt(char encryptedMsg[], char* deciphered, int key){
  int alphabetSize = 26; // 0 to 25
  char norm_alpha[alphabetSize];  // array for normal alphabet
  char encrypPattern[alphabetSize]; // array for encryption pattern

  // fill normal alphabet array, encryption pattern array
  createEncryptionPattern(norm_alpha, encrypPattern, key);

  printf("Reg: %s\n",norm_alpha);
  printf("Enc: %s\n", encrypPattern);

  int end;
  int patternIndex;

  for(int i = 0; encryptedMsg[i] != '\0'; i++){
    end = i;
    // check if space
    if (encryptedMsg[i] == ' '){
      //printf("input char %c.\n", encryptedMsg[i]);
      deciphered[i] = ' ';
      continue;
    }
    // find the location of the encrypted character in the cipher, must use linear search due to shift!!!
    patternIndex = char_linearSearch(encrypPattern, encryptedMsg[i], alphabetSize);
    if (patternIndex == -1){
      printf("not found: %c\n", encryptedMsg[i]);
    }
    // place deciphered character into array
    deciphered[i] = norm_alpha[patternIndex];
    //printf("input char %c.\n", encryptedMsg[i]);
  }

  deciphered[end+1] = '\0';

  //printf("1. Dec: %s\n", deciphered);
  return 0;

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

  // decipher message
  char decipheredMsg[100];
  //decipheredMsg[0] = 'b';
  //decipheredMsg[1] = 'k';

  int res = decrypt(encryptedMsg, decipheredMsg, key);

  printf("Decrypted message: %s \n", decipheredMsg);

  return 0;
}
