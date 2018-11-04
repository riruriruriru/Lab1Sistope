#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void controlador(int signum){
	printf("recibi señal del papi uwu, mi pid es: %d y recibi señal %d\n", getpid(),signum);
	
	if (signum == 16){
		int pidF = getpid();
		int pid = 0;
		char id[12];
		sprintf(id, "%d", pidF);
		if ((pid=fork())==0){
			if(getpid()!=0){
				char *argv[] = {"./contador", id,(const char*)NULL};
				execv("contador", argv);
			}
			else{
				printf("UWU\n");
			}
		}
	}
	
}
int main(){
	//printf("soy hijo %d de %d\n", getpid(),getppid());
	printf("xao\n");
	while(1){
		signal(SIGTERM,controlador);
		signal(SIGUSR1,controlador);
		signal(SIGUSR2,controlador);	
		signal(15,controlador);
		signal(16,controlador);
		signal(17,controlador);	
		
	}
	return 0;
}
