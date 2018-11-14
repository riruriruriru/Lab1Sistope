#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
static volatile int counter = 0;

//Función que es ejecutado al momento de recibir la señale especificada SIGINT, recibe solo esta ya que es un preceso nieto
//Entradas: Entero que representa el numero de la señal que fue escuchada por el proceso correspondiente
//Salidas: Vacio
void controlador(int signum){
	
	if(signum==SIGINT){
		//Primer advertencia
		if(counter==0){
			printf("Soy el nieto con pid: %d y estoy vivo aún. No me mates abuelo\n", getpid());
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
		signal(SIGINT,controlador);	
	}
	return 0;
}
