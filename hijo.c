#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
int main(){
	printf("soy hijo %d de %d\n", getpid(),getppid());
	printf("xao\n");
	
	return 0;
	}
