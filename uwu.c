#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

typedef struct Signal{
	int numHijo;
	char *sName;
	
	}Signal;

int comprobarSenial(char *strSignal, Signal *sig){
	printf("INICIO COMPROBAR SEÑAL\n");
	char *strAux, *strAux2, *aux3;
	int i = 0,bool=0, cont=0, contNumber=0,contSig=0, nChild=0;
	for(i=0;i<25;i++){
		if(bool==0&&strSignal[i]!='-'){
			contNumber++;
			}
		else if(bool==1&&strSignal[i]!='-'){
			contSig++;
			}
		if(strSignal[i]=='-'){
			bool = 1;
			}
		
		}
	if(bool==1){
		bool = 0;
		strAux = (char *)malloc(contNumber*sizeof(char));
		strAux2 = (char *)malloc(contSig*sizeof(char));
		for(i=0;i<25;i++){
			if(bool==0&&strSignal[i]!='-'){
				strAux[cont]=strSignal[i];
				cont++;
			}
			else if(bool==1&&strSignal[i]!='-'){
				strAux2[cont]=strSignal[i];
				cont++;
				}
			if(strSignal[i]=='-'){
				bool = 1;
				cont = 0;
				}
			}
		printf("UWU\n");
		nChild = strtol(strAux, &aux3, 10);
		printf("%s - %s\n",strAux,strAux2);
		printf("numero hijo: %d\n",nChild);
		if(nChild==0){
			return 0;
			}
		else{
			sig->numHijo = nChild;
			sig->sName = strAux2;
			}
		return 1;
		}
	else{
		return 0;
		}
	}




int main(int argc, char *argv[]){
	int numHijos = 0, i = 0;
	printf("Ingrese el numero de hijos que desea crear: \n");
	scanf("%d", &numHijos);
	printf("Se crearan %d hijos\n", numHijos);
	pid_t *arrayPID;
	char *string, *signal, *string2;
	Signal *sig;
	sig = (Signal *)malloc(sizeof(Signal));
	sig->numHijo = 500;
	sig->sName = (char *)malloc(20*sizeof(char));
	int nHijo=0;
	char aux;
	signal = (char *)malloc(25*sizeof(char));
	string = (char *)malloc(25*sizeof(char));
	string2 = (char *)malloc(25*sizeof(char));
	arrayPID = (pid_t *) malloc(numHijos*sizeof(pid_t));
	for(i = 0; i<numHijos;i++){
		if(fork()==0){	
			if(getpid()!=0){
				arrayPID[i]=getpid();
				//printf("Soy hijo n° %d con pid %d de %d\n",1+i,getpid(),getppid());
				//char *argv[] = { "gcc", "-c", "-o", "hijo.o", "hijo.c", 0 };
				execl("./hijo","","", (char *)0);
				
				}
			else{
				printf("UWU\n");
				}
			}
		}
	int comprobacion = 0;
	printf("Esperando...");
	while(1){
		do{
			printf("Ingresar numero de hijo y señal a enviar (X-Y)\n");
			scanf("%s",string);
			comprobacion=comprobarSenial(string,sig);
			if(comprobacion==0){
				printf("Senial ingresada de manera incorrecta, intente otra vez\n");
				}
		}while(comprobacion==0);
		printf("Se enviara señal %s al hijo %d\n",sig->sName,sig->numHijo);
		//comprobarSenial(signal,sig);
		getchar();
		
		}
	for(int i=0;i<numHijos;i++){ 
		exit(0);
		wait(NULL); 
	}
	printf("FINALIZANDO...\n");
	//exit(0);
	
	}
