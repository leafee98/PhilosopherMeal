#include "mysemop.h"
#include "philosopher.h"
#include <unistd.h>
#include <sys/types.h>

void philosopher(int i);

// the array and the variable below storage their sem_id
int chopsticks[5];

int main(int argc, char * args[]) {
	for (int i = 0; i < 5; ++i)
		chopsticks[i] = CreateSem(1);

	int fpid = 1;
	int amount = 5;
	while (fpid != 0 && --amount)
		fpid = fork();

	philosopher(amount);

	return 0;
}

void philosopher(int i) {
	printf("my i = %d\n", i);
	while (true) {
		think(i);

		// for each philosopher, the i-th chopstick is at his left,
		// and the (i + 1) % 5 th chopstick is at his right;

		// odd get left first, and even get right first
		if (i % 2 == 1) {
			Psem(chopsticks[i]);
			printf("philosopher %d get left\n", i);

			Psem(chopsticks[(i + 1) % 5]);
			printf("philosopher %d get right\n", i);

			eat(i);

			Vsem(chopsticks[i]);
			printf("philosopher %d put down left\n", i);

			Vsem(chopsticks[(i + 1) % 5]);
			printf("philosopher %d put down left\n", i);
		} else {
			Psem(chopsticks[(i + 1) % 5]);
			printf("philosopher %d get right\n", i);

			Psem(chopsticks[i]);
			printf("philosopher %d get left\n", i);

			eat(i);

			Vsem(chopsticks[(i + 1) % 5]);
			printf("philosopher %d put down left\n", i);

			Vsem(chopsticks[i]);
			printf("philosopher %d put down left\n", i);
		}
	}
}


