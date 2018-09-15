// run consumer first ./Consumer &

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/shm.h>
#include <semaphore.h>  // for POSIX semaphore
#include <fcntl.h>      // this also needed

#include <errno.h>

#include "sh_arrayStruct.h"  // The shared structure

#define SNAME "/mysem"

#define SEM_DELAY "/semDelay"

int main(){

  int arr_size = 1;

  int running = 1;
	void *shared_memory = (void *)0;
	struct shared_Array_st *shared_stuff;
	int shmid;

  int curr_index = 0;

	srand((unsigned int)getpid());	// seed for random. next = getpid() value

	// create, but since there is a shared memory with the same key that already exists it just gets the id.
	shmid = shmget((key_t)2345, sizeof(struct shared_Array_st), 0666 | IPC_CREAT);	//
  errno=0;
	if(shmid == -1){
		fprintf(stderr, "shmget failed: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	// attach
	shared_memory = shmat(shmid, (void*)0, 0);	//attach the shared memory to shmid. Returns pointer to the first byte of the shared memory
	if (shared_memory == (void*)-1){
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Memory attached at %X\n", (int)shared_memory);

  // assign shared_memory to shared stuff.
	shared_stuff = (struct shared_Array_st *)shared_memory;	//point to first byte

  // Create semaphore to be shared, sem_open does this while sem_init will give a copy to child processes.
  //Use sem_open with O_CREAT in the process that creates them
	sem_t *sem = sem_open(SNAME, O_CREAT, 0644, 0); /* Initial value is 0. */
  // https://stackoverflow.com/questions/8359322/how-to-share-semaphores-between-processes-using-shared-memory/8359403#8359403
  errno=0;  /* <---- This is an important thing I learned when using errno. */
  if (sem == SEM_FAILED){
    fprintf(stderr, "sem_open() failed.  errno:%d\n", errno);
    return 1;
  }

  sem_t *sem_delay = sem_open(SEM_DELAY, O_CREAT, 0644, 1); /* Initial value is 1. */


  int prev_cnt;
  int pause = 0;
  while(running){
    printf("Waiting for producer\n");
    pause = 0;
    // has to wait for something to be produced

    sem_wait(sem);

    // enter critical section and access to the shared Memory
    sem_wait(sem_delay);

    // check for newly produced
    /*
    while (shared_stuff[curr_index].old == 0){
      prev_cnt = curr_index;
      curr_index ++;
      if (curr_index >= arr_size){
        curr_index = 0;
      }

      // this means it looped back to original position
      if(curr_index == prev_cnt){
        pause = 1;
        break;
      }
    }

    // couldn't find new item, wait again.
    if (pause == 1){
      continue;
    }
    */
    // got to newly produced
    //fflush(stdout);
    printf("You wrote: %s\n", shared_stuff[curr_index].string1);
    sleep(3);	// since sleep, makes other processes wait for this to finish
    shared_stuff[curr_index].old = 0;
    if(strncmp(shared_stuff[curr_index].string1, "end", 3) == 0){		// if end was written, finished
      running = 0;
    }
    sem_post(sem_delay);

  }

  // close the semaphore for this process, the semaphore remains in the system
  sem_close(sem);
  sem_close(sem_delay);

	// The sem_unlink() function removes the semaphore identified by name and marks the semaphore to be destroyed once all processes cease using it (this may mean immediately, if all processes that had the semaphore open have already closed it).
	sem_unlink(SNAME);
  sem_unlink(SEM_DELAY);

  // after finished, detach from shared memory
  if (shmdt(shared_memory) == -1){
  fprintf(stderr, "shmdt failed\n");
  exit(EXIT_FAILURE);
  }

  // Delete the shared memory, good practice to let creator/ last process to use it to delete it.
  if(shmctl(shmid, IPC_RMID, 0) == -1){
  fprintf(stderr,"shmctl(IPC_RMID) failed\n");
  exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);

}

/*
Reader from array on shared memory

int main(){

	int arr_size = 5;

	int *shared_memory_arr;
  	int shmid;

  	// create a shared memory to fit the struct array.
  	//int shmget(key_t key, size_t size, int shmflg);
	shmid = shmget((key_t)1234, sizeof(int) * arr_size, 0666 | IPC_CREAT);
	//errno = 0;
	if(shmid == -1){
		fprintf(stderr, "shmget failed: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	// attach
  	//void *shmat(int shm_id, const void *shm_addr, int shmflg);
  	shared_memory_arr = shmat(shmid, (void*)0, 0);	//attach the shared memory to shmid. Returns pointer to the first byte of the shared memory
  	if (shared_memory == (void*)-1){
   		fprintf(stderr, "shmat failed\n");
    		exit(EXIT_FAILURE);
  	}

 	printf("Memory attached at %X\n", (int)shared_memory_arr);

	//Read from the array on shared memory
	printf("Reader reads: \n");
	for (int i = 0; i < arr_size; i ++){
		printf("%d \n", shared_memory_arr[i]);
	}

	// after finished, detach from shared memory
	if (shmdt(shared_memory_arr) == -1){
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	return 0;

}

*/
