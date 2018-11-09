#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static volatile int keepRunning = 1;
static volatile int counter = 0;

typedef struct Signal{
	int numHijo;
	int sName;
	
	}Signal;

int comprobarSenial(char *strSignal, Signal *sig){
	printf("INICIO COMPROBAR SEÑAL\n");
	char *strAux, *strAux2, *aux3;
	int i = 0,bool=0, cont=0, contNumber=0,contSig=0, nChild=0, nSig=0;
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
		nSig = strtol(strAux2, &aux3, 10);
		printf("%s - %s\n",strAux,strAux2);
		printf("numero hijo: %d\n",nChild);
		printf("señal; %d\n", nSig);
		if(nChild==0||nSig==0){
			return 0;
			}
		else{
			sig->numHijo = nChild;
			sig->sName = nSig;
			}
		return 1;
		}
	else{
		return 0;
		}
	}

void createSons(int numHijos, int *arrayPID){
	int i = 0, pid=0;
	for(i = 0; i<numHijos;i++){
		if((pid=fork())==0){	
			if(getpid()!=0){
				printf("Soy hijo n° %d con pid %d de %d\n",1+i,getpid(),getppid());
				//char *argv[] = { "gcc", "-c", "-o", "hijo.o", "hijo.c", 0 };
				execl("./hijo","","", (char *)0);
				
			}
			else{
				printf("UWU\n");
			}
		}
		else{
			arrayPID[i]=pid;
			}
		}
	}

int sendSignal(Signal *s, int *arrayPID, int numHijos){
	int bool=0;
	if(s->numHijo-1>numHijos){
		printf("Hijo invalido\n");
		return 0;
		}
	if(arrayPID[s->numHijo-1]==-1){
		printf("Hijo ya esta muerto\n");
		return 0;
		}
	printf("hijo destino pid: %d\n", arrayPID[s->numHijo-1]);
	if(s->sName==15||s->sName==16||s->sName==17){
		if(s->sName==16){
			kill(arrayPID[s->numHijo-1],10);
			}
		else if(s->sName==15){
			bool=kill(arrayPID[s->numHijo-1],s->sName);
			printf("bool: %d\n", bool);
			arrayPID[s->numHijo-1]=-1;
			
			}
		else{
			kill(arrayPID[s->numHijo-1],12);
			}
		
		return 1;
		}
	return 0;
	}
void handler(int signum){
	printf("RECIBI UN %d\n",signum);
	if(signum==2){
		counter++;
		}
	
	if(counter==1){
		printf("mandar sigint\n");
		kill(0,2);
		}
	if(counter>2){
		keepRunning=0;
		exit(0);
		printf("XAO\n");
		}
	printf("keeprunning: %d\n",keepRunning);
	}

int main(int argc, char *argv[]){
	int numHijos = 0;
	printf("Ingrese el numero de hijos que desea crear: \n");
	scanf("%d", &numHijos);
	printf("Se crearan %d hijos\n", numHijos);
	pid_t *arrayPID;
	char *string,*signal2,*string2;
	Signal *sig;
	sig = (Signal *)malloc(sizeof(Signal));
	sig->numHijo = 500;
	//sig->sName = (char *)malloc(20*sizeof(char));
	int nHijo=0;
	char aux;
	signal2 = (char *)malloc(25*sizeof(char));
	string = (char *)malloc(25*sizeof(char));
	string2 = (char *)malloc(25*sizeof(char));
	arrayPID = (pid_t *) malloc(numHijos*sizeof(pid_t));
	createSons(numHijos, arrayPID);
	int comprobacion = 0;
	printf("Esperando...");
	if(signal(SIGINT, handler)!=SIG_ERR){
			printf("RECIBI UN CTRL + C\n");
			}
	while(keepRunning){
		do{
			printf("Ingresar numero de hijo y señal a enviar (X-Y)\n");
			scanf("%s",string);
			comprobacion=comprobarSenial(string,sig);
			if(comprobacion==0){
				printf("Senial ingresada de manera incorrecta, intente otra vez\n");
				}
		}while(comprobacion==0);
		
		printf("Se enviara señal %d al hijo %d\n",sig->sName,sig->numHijo);
		sendSignal(sig, arrayPID, numHijos);
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
