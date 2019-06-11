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
	char input[SHM_SIZE];
	sem_t* mutex = sem_open(MUTEX_NAME, O_CREAT, 0644, 0);
	sem_t* full = sem_open(FULL_NAME, O_CREAT, 0644, 0);

	shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0644);
	shmptr = shmat(shmid, NULL, 0);
	
	scanf("%s", input);
	strcpy(shmptr, input);
	sem_post(mutex);
	sem_wait(full);
	printf("From Receiver: \"%s\"\n", shmptr);

	sem_close(mutex);
	sem_close(full);
	sem_unlink(MUTEX_NAME);
	sem_unlink(FULL_NAME);
	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	printf("Sender:  Process End\n");
	return 0;
}
