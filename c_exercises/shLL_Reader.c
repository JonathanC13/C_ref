
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/shm.h>
#include <semaphore.h>  // for POSIX semaphore
#include <fcntl.h>      // this also needed

#include <semaphore.h>  // for POSIX semaphore
#include <fcntl.h>      // this also needed

#include <errno.h>

#include "shLL_struct.h"
#include "DB_LinkedList_lib.h"

// name the semaphore
#define SEM_LL "/sem_ll"
#define SEM_W "/sem_w"

void create_node(struct sh_node** headRef, int value);

// The Reader will allocate memory for the linked list nodes
// Then will initialize the shared memory with pointers to the linked list, either pointer to the head node or to each node.
// Probably only give the pointer to the head node so it can be dynamic.
// When the reader reads the value of 1 in the linked list head, it will end.
int main(){

  // The shared memory will be the size of a pointer to a node.
  void *shared_memory_pt = (void *)0;    // pointer to the shared Memory
  int shmid;                // Returns !(-1) if successful in creating or acknowledging existing shared memory

  struct sh_node *shared_head; // Contains the pointer to the first byte of the shared memory.
  struct sh_node *head;

  int running = 1;

  // create a shared memory location to fit the linked list pointer
  shmid = shmget((key_t)4444, sizeof(struct sh_node), 0666 | IPC_CREAT);
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

  printf("Reader: Memory attached at %X\n", shared_memory_pt);

  // Reader will have the shared structure point to the head of the linked list.
  // maybe dont need this if shared_head = head. will test without if this works.
  shared_head = (struct sh_node *)shared_memory_pt;

  // Create semaphore to be shared, sem_open does this while sem_init will give a copy to child processes.
  //Use sem_open with O_CREAT in the process that creates them
  sem_t *sem = sem_open(SEM_LL, O_CREAT, 0644, 1); /* Initial value is 0. */
  // https://stackoverflow.com/questions/8359322/how-to-share-semaphores-between-processes-using-shared-memory/8359403#8359403
  errno=0;  /* <---- This is an important thing I learned when using errno. */
  if (sem == SEM_FAILED){
    fprintf(stderr, "sem_open() failed.  errno:%d\n", errno);
    return 1;
  }

  sem_t *sem_writer = sem_open(SEM_W, O_CREAT, 0644, 0); /* Initial value is 1. */

  int sem_val;

  // enter first critical section
  //sem_wait(sem);
  //sem_getvalue(sem, &sem_val);
  //printf("Reader: sem value is: %d", sem_val);

  // locally create a linked list, functions from DB_LinkedList_lib.h
  // create the first node of the linked list
  //create_node(&head, 0);


  // hopefully the shared memory stores the pointer of head.
  //shared_head = head; // The shared memory points to the head struct
  //printf("Where is the actual head: %p.\n", head);

  // Set up head node
  shared_head[0].value = 0;
  shared_head[0].next = NULL;
  shared_head[0].prev = NULL;
  printf("R: Where is the shared mem: %p.\n", shared_head);

  // test if pointed correctly and can read the value;
  printf("Reader: LL created, Value of head is %d.\n", shared_head[0].value);

  //sem_post(sem);
  //sem_getvalue(sem, &sem_val);
  //printf("Reader: sem value is: %d", sem_val);

  // if head successfully created, post writer semaphore
  if (shared_head[0].value == 0){
    printf("Reader: posting writer.\n");
    //sem_post(sem_writer);
  }

  sleep(2);

  while(running){

    // 2nd critical section to check if written to
    //sem_wait(sem);
    //
    sleep(5);
    printf("Reader: entering reader, shared value of %d.\n", (*shared_head).value);
    printf("Reader: entering reader, head value of %d.\n", (*head).value);
    if(shared_head[0].value != 0){
      printf("Reader: Value of head has changed to %d, now ending. \n", shared_head[0].value);
      running = 0;
    }
    //shared_head[0].value = 1;



    //sem_post(sem);

  }

  // closing procedure
  // Free the allocated memory for the linked list
  //free(head);

  // close the semaphore for this process, the semaphore remains in the system
  sem_close(sem);
  sem_close(sem_writer);

  // The sem_unlink() function removes the semaphore identified by name and marks the semaphore to be destroyed once all processes cease using it (this may mean immediately, if all processes that had the semaphore open have already closed it).
  sem_unlink(SEM_LL);
  sem_unlink(SEM_W);

  printf("Reader closing.\n");

  // after finished, detach from shared memory
  if (shmdt(shared_memory_pt) == -1){
  fprintf(stderr, "shmdt failed\n");
  exit(EXIT_FAILURE);
  }

  return 0;
}
