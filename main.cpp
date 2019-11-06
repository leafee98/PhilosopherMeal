#include "mysemop.h"
#include "philosopher.h"
#include <unistd.h>
#include <sys/types.h>

void philosopher(int i);

// the array and the variable below storage their sem_id
int room;
int chopsticks[5];

int main(int argc, char * args[]) {
	for (int i = 0; i < 5; ++i) {
		chopsticks[i] = CreateSem(1);
	}
	room = CreateSem(4);


	int fpid = 1;
	int amount = 4;
	while (fpid != 0 && amount-- ) {
		fpid = fork();
	}


	if (fpid != 0)
		philosopher(amount + 1);
	else 
		philosopher(amount);


	return 0;
}

void philosopher(int i) {
	while (true) {
		think(i);

		// to each philosopher, the i-th chopstick is at his left,
		// and the (i + 1) % 5 th chopstick is at his right;
		Psem(room);

		Psem(chopsticks[i]);
		printf("philosopher %d pick up the chopstick on his left\n", i);

		Psem(chopsticks[(i + 1) % 5]);
		printf("philosopher %d pick up the chopstick on his right\n", i);

		eat(i);

		Vsem(chopsticks[i]);
		printf("philosopher %d put down the chopstick on his left\n", i);

		Vsem(chopsticks[(i + 1) % 5]);
		printf("philosopher %d put down the chopstick on his left\n", i);
		Vsem(room);
	}
}


