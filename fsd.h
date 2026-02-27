//fsd.h
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <termios.h>
#include <errno.h>
#include <stdbool.h>
#include<arcfour.h>
#include<fcntl.h>

typedef unsigned char int8; //takes 0-255
typedef unsigned int int32; //takes 0--65,535
typedef unsigned short int16;// takes 0--4,294,967,295
typedef unsigned long long int64;// takes 0--18,446,744,073,709,551,615

void changeecho(bool);
int8 *readkey(int8 *);
void usage(int8 *);
int main(int, char **);
int16 grabmagic(Arcfour *, int32);
