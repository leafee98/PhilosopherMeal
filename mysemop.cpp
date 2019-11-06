#include "mysemop.h"


int CreateSem(int value) {
	int sem_id;
	sem_id = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
	if (sem_id == -1) return -1;
	if (SetSemValue(sem_id, value) == 0) return -1;
	return sem_id;
}

int SetSemValue(int sem_id, int value) {
	if (semctl(sem_id, 0, SETVAL, value) == -1) return 0;
	return 1;
}

void DeleteSem(int sem_id) {
	if (semctl(sem_id, 0, IPC_RMID) == -1)
		fprintf(stderr, "Failed to delete semaphore\n");
}

int Psem(int sem_id) {
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;

	if (semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "P failed\n");
		return 0;
	}

	return 1;
}

int Vsem(int sem_id) {
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;

	if (semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "V failed\n");
		return 0;
	}

	return 1;
}
