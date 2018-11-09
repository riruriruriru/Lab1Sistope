#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
static volatile counter = 0;

void controlador(int signum){
	printf("recibi señal del papi uwu, mi pid es: %d y recibi señal %d\n", getpid(),signum);
	
	if (signum == 10){
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
		wait(NULL);
	}
	else if(signum==12){
		printf("el doviarab\n");
		}
	else if(signum==15){
		printf("la harleyquinn\n");
		printf("mi pid es %d y me van a matar uwu\n" ,getpid());
		exit(0);
		}
	else if(signum==2){
		if(counter==0){
			printf("Soy el hijo con pid %d y estoy vivo aun. No me mates papa :c 🤡\n", getpid());
			counter++;
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
