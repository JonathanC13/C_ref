#ifndef SEARCHALG_H_  /* Include guard */
#define SEARCHALG_H_

int int_min(int a, int b);

void linearSearch(int passArray[], int target, int *retIndex);

int binarySearch(int* p_Array, int target, int size);

int char_binarySearch(char* p_Array, char target, int size);

void jumpSearch(int* target, int size);



char *strip_chars(char *string,char *chars);

#endif

//https://stackoverflow.com/questions/17416719/do-i-need-to-compile-the-header-files-in-a-c-program
// Dont need to comple .h files
// Header files are intended to be included into implementation files, not fed to the compiler as independent translation units.
