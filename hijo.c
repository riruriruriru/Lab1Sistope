#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
static volatile int counter = 0;

//Función que es ejecutado al momento de recibir las señales especificadas, SIGUSR1,SIGUSR2,SIGTERM y SIGINT
//Entradas: Entero que representa el numero de la señal que fue escuchada por el proceso hijo correspondiente
//Salidas: Vacio
void controlador(int signum){
	
	//Comprueba si la señal escuchada es SIGUSR1
	if (signum == SIGUSR1){
		printf("Soy el hijo %d y recibí SIGUSR1\n", getpid());
		int pidF = getpid();
		int pid = 0;
		char id[12];
		sprintf(id, "%d", pidF);
		
		//Crea un proceso hijo para que ejecute contralador
		if ((pid=fork())==0){
			if(getpid()!=0){
				
				//Se utiliza execv para ejecutar controlador y manda el pid del padre de este proceso hijo temporañ
				char *argv[] = {"./contador", id,NULL};
				execv("contador", argv);
			}
		}
	}
	
	//Comprueba si la señal escuchada es SIGUSR2
	else if(signum == SIGUSR2){
		printf("Soy el hijo %d y recibí SIGUSR2\n", getpid());
		int pid = 0;
		if((pid=fork())==0){
			if(getpid()!=0){
				char *argv[] = {"./nieto", NULL};
				execv("nieto", argv);
				}
			
			}
		
		}
	//Comprueba si la señal escuchada es SIGTERM
	else if(signum == SIGTERM){
		printf("Soy el hijo %d y recibí SIGTERM\n", getpid());
		printf("Soy el hijo con pid: %d y mi papá me quiere matar\n" ,getpid());
		exit(0);
		}
		
	//Comprueba si la señal escuchada es SIGINT al momento de presionar Ctrl+c
	else if(signum == SIGINT){
		//Primera advertencia al periosionar Ctrl+c
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
	
	while(1){
		signal(SIGTERM,controlador);
		signal(SIGUSR1,controlador);
		signal(SIGUSR2,controlador);
		signal(SIGINT,controlador);	
	}
	return 0;
}
