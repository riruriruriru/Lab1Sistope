#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
static volatile int counter = 0;

void controlador(int signum){
	if (signum == 10){
		printf("Soy el hijo %d y recibí SIGUSR1\n", getpid());
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
		//wait(NULL);
	}
	else if(signum==12){
		printf("Soy el hijo %d y recibí SIGUSR2\n", getpid());
		int pid = 0;
		if((pid=fork())==0){
			if(getpid()!=0){
				char *argv[] = {"./nieto", (const char*)NULL};
				execv("nieto", argv);
				}
			
			}
		
		}
	else if(signum==15){
		printf("Soy el hijo %d y recibí SIGTERM\n", getpid());
		printf("Soy el hijo con pid: %d y mi papá me quiere matar\n" ,getpid());
		exit(0);
		}
	else if(signum==2){
		//Primer advertencia
		if(counter==0){
			printf("Soy el hijo con pid: %d, y estoy vivo aún. No me mates papá\n", getpid());
			counter++;
			}
		//La segunda vez que se preciona Ctrl + c se termina el proceso	
		else if(counter==1){
			exit(0);
			}
		
		}
	
}

int main(){
	//printf("soy hijo %d de %d\n", getpid(),getppid());
	//printf("xao\n");
	while(1){
		signal(SIGTERM,controlador);
		signal(SIGUSR1,controlador);
		signal(SIGUSR2,controlador);
		signal(SIGINT,controlador);	
		/*if(signal(15,controlador)==SIG_ERR){
			printf("OWO\n");
			}
		if(signal(16,controlador)==SIG_ERR){
			printf("OWO\n");
			}
		if(signal(17,controlador)==SIG_ERR){
			printf("OWO\n");
			}
			*/	
		
	}
	return 0;
}
