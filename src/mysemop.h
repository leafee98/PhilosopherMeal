#ifndef MYSEMOP_H
#define MYSEMOP_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <fcntl.h>

int CreateSem(int value);
int SetSemValue(int sem_id, int value);
void DeleteSem(int sem_id);

int Psem(int sem_id);
int Vsem(int sem_id);

#endif
