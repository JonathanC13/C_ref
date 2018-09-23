#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/shm.h>
#include <semaphore.h>  // for POSIX semaphore
#include <fcntl.h>      // this also needed

#include <errno.h>

#include "shLL_struct.h"
#include "DB_LinkedList_lib.h"

// name the semaphore
#define SEM_LL "/sem_ll"
#define SEM_W "/sem_w"

// writer for shared linked list
// Reader starts first creating the linked list and writer will execute and write a value to the linked list
// Then ends.
int main(){

  // The shared memory will be the size of a pointer to a node.
  void *shared_memory_pt = (void *)0;    // pointer to the shared Memory
  int shmid;                // Returns !(-1) if successful in creating or acknowledging existing shared memory

  struct sh_node *shared_head; // Contains the pointer to the first byte of the shared memory.
  struct sh_node *head;

  // create a shared memory location to fit the linked list pointer
  shmid = shmget((key_t)4444, sizeof(struct sh_node), 0666);
  // error handling of shared memory
  errno = 0;
  if(shmid == -1){
    fprintf(stderr, "shmget failed: %d\n", errno);
    exit(EXIT_FAILURE);
  }

  // attach to the shared memory
  // Returns pointer to the first byte of the shared memory
  shared_memory_pt = shmat(shmid, (void*)0, 0);
  // error handling
  if (shared_memory_pt == (void*)-1){
    fprintf(stderr, "shmat failed\n");
      exit(EXIT_FAILURE);
  }

  printf("Writer: Memory attached at %X\n", shared_memory_pt);

  // Reader will have the shared structure point to the head of the linked list.
  shared_head = (struct sh_node *)shared_memory_pt;

  // open the semaphore
  sem_t *sem = sem_open(SEM_LL, 0); /* Open a preexisting semaphore. name doesn't matter */

  // open the semaphore
  sem_t *sem_writer = sem_open(SEM_W, 0); /* Open a preexisting semaphore. name doesn't matter */

  // wait for reader to create the linked list.
  //sem_wait(sem_writer);

  // enter critical section
  //sem_wait(sem);
  printf("W: Where is the shared mem: %p.\n", shared_head);

  // So just print the current value of the head to test if can read
  printf("Writer: The head value of the shared linked list is: %d.\n", shared_head[0].value); // shared_head.value
  sleep(2);
  /// ////////////////// WRITER having probelsms writing to shared memory!!!!!!!!
  // Now write the value of 1 to it, to indicate to the reader it can end.
  (*shared_head).value = 5;

  printf("Writer: The head value of the shared linked list is NOW: %d.\n", shared_head[0].value);

  //sem_post(sem);
  //sem_post(sem_writer);

  sem_close(sem);
  sem_close(sem_writer);

  printf("Writer close.\n");

  // closing procedure
  // after finished, detach from shared memory
  if (shmdt(shared_memory_pt) == -1){
    fprintf(stderr, "shmdt failed\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}
