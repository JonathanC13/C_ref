#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/shm.h>
#include <semaphore.h>  // for POSIX semaphore
#include <fcntl.h>      // this also needed

#include <errno.h>


// Reader from array on shared memory

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
	if (shared_memory_arr == (void*)-1){
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
