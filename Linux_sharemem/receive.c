#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/shm.h>

#define SHM_SIZE 1024
#define KEY_NUM 1000

static const char* MUTEX_NAME = "mutex_shm";
static const char* FULL_NAME = "full_shm";

int main(int argc, char const* argv[])
{
	int shmid;
	char* shmptr;
	key_t key = KEY_NUM;
	char result[SHM_SIZE];
	sem_t* mutex = sem_open(MUTEX_NAME, 0);
	sem_t* full = sem_open(FULL_NAME, 0);
	
	shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0644);
	shmptr = shmat(shmid, NULL, 0);

	sem_wait(mutex);
	strcpy(result, shmptr);
	printf("From Sender: \"%s\"\n", result);
	strcpy(shmptr, "over");
	sem_post(full);

	sem_close(mutex);
	sem_close(full);
	sem_unlink(MUTEX_NAME);
	sem_unlink(FULL_NAME);
	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	printf("Receiver :  Process End \n");
	return 0;
}
