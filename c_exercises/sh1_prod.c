#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/shm.h>
#include <semaphore.h>  // for POSIX semaphore
#include <fcntl.h>      // this also needed

#include <errno.h>

#include "sh_arrayStruct.h"  // The shared structure

// Name for our semaphore
#define SEM_NAME "/mysem"

#define SEM_DELAY "/semDelay"

// http://liuhangbin.github.io/linux-semaphore-and-shared-memory/

int main(){

  int arr_size = 1;
  int curr_count = 0; // current location to write in the array.
  char buffer[BUFSIZ];  // BUFSIZ is 512 bytes

  int running = 1;
  void *shared_memory = (void *)0;
  struct shared_Array_st *shared_stuff; // contains the struct elements
  int shmid;

  // create a shared memory to fit the struct array.
  //int shmget(key_t key, size_t size, int shmflg);
  shmid = shmget((key_t)1234, sizeof(struct shared_Array_st), 0666 | IPC_CREAT);	//
  //errno = 0;
  if(shmid == -1){
    fprintf(stderr, "shmget failed: %d\n", errno);
    exit(EXIT_FAILURE);
  }

  // attach
  //void *shmat(int shm_id, const void *shm_addr, int shmflg);
  shared_memory = shmat(shmid, (void*)0, 0);	//attach the shared memory to shmid. Returns pointer to the first byte of the shared memory
  if (shared_memory == (void*)-1){
    fprintf(stderr, "shmat failed\n");
    exit(EXIT_FAILURE);
  }

  printf("Memory attached at %X\n", (int)shared_memory);

  // assign shared_memory to shared stuff.
  shared_stuff = (struct shared_Array_st *)shared_memory;	//point to first byte


  // open the semaphore
  sem_t *sem = sem_open(SEM_NAME, 0); /* Open a preexisting semaphore. name doesn't matter */

  // open the semaphore
  sem_t *sem_delay = sem_open(SEM_DELAY, 0); /* Open a preexisting semaphore. name doesn't matter */

  int sem_val;


  // write to shared memory
  while (running){
    //sem_getvalue(sem_delay, &sem_val);
    //printf("sem value is: %d", sem_val);
    // enter critical section for shared memory
    sem_wait(sem_delay);

    fflush(stdout);
    printf("Enter a string: ");
    // get the string from user
    fgets(buffer, sizeof(buffer), stdin);

    if(strncmp(buffer, "end", 3) == 0){		// if end was written, finished
				running = 0;
		}

    // The producer sleeps if the semaphore value is 5 since which indicates the array is full
    /*
    while(1){
      sem_getvalue(sem, &sem_val);

      if(sem_val == arr_size){
        printf("sem value is: %d", sem_val);
        //sleep(3);
      } else {
        break;
      }

    }
    */
    // if the current element has been read then produce and replace
    //if (shared_stuff[curr_count].old != 1){
      strncpy(shared_stuff[curr_count].string1, buffer, text_size);
      shared_stuff[curr_count].old = 1; // 1 means not read yet.

    //}
    // move count regardless
    curr_count ++;

    if (curr_count >= arr_size){
      curr_count = 0;
      // post that it has produced
      sem_post(sem);
    }


    // post access to shared memory
    sem_post(sem_delay);

    printf("Waiting for consumer.\n");
    sleep(2); // give consumer a chance
  }

  // The sem_unlink() function removes the semaphore identified by name and marks the semaphore to be destroyed once all processes cease using it (this may mean immediately, if all processes that had the semaphore open have already closed it).
  sem_close(sem);
  sem_close(sem_delay);
  sem_unlink(SEM_NAME);
  sem_unlink(SEM_DELAY);

  // after finished, detach from shared memory
  if (shmdt(shared_memory) == -1){
  fprintf(stderr, "shmdt failed\n");
  exit(EXIT_FAILURE);
  }

  // Delete the shared memory since this is the creator
  if(shmctl(shmid, IPC_RMID, 0) == -1){
  fprintf(stderr,"shmctl(IPC_RMID) failed\n");
  exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);

}
