#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


static volatile int keepRunning = 1;
static volatile int counter = 0;

//Estructura que se utiliza para guardar los datos de una señal
//Guarda el numero del hijo que recibira la señal y el numero de la señal
typedef struct Signal{
	int numHijo;
	int sName;
	
	}Signal;

//Funcion que comprueba si una señal fue enviada correctamente verificando que se envien por pantalla solo señales de numero 15, 16 y 17, es decir sigusr1, sigusr2 y sigterm
//SIGINT solo se recibe cuando se presiona ctrl+c, por lo tanto no se considera como opcion para mandarlo por pantalla
//Entradas: estructura vacia de tipo Signal y string con todo lo que escribio el usuario por pantalla
//Salidas: Entero igual a 1 si la señal cumple con todos los parametros o entero igual a 0 si la señal no cumple con el formato
int comprobarSenial(char *strSignal, Signal *sig){
	printf("INICIO COMPROBAR SEÑAL\n");
	char *strAux, *strAux2, *aux3;
	int i = 0,bool=0, cont=0, contNumber=0,contSig=0, nChild=0, nSig=0; //se inicializan variables
	for(i=0;i<25;i++){ //se recorre el string ingresado por el usuario
		if(bool==0&&strSignal[i]!='-'){ //se cuenta el numero de digitos del numero de hijo ingresado
			contNumber++;
			}
		else if(bool==1&&strSignal[i]!='-'){ //se cuenta el numero de digitos de la señal ingresada
			contSig++;
			}
		if(strSignal[i]=='-'){//cuando se encuentra el guion, se cambia el valor de variable bool para buscar el numero de la señal ingresada
			bool = 1;
			}
		
		}
	if(bool==1){//si bool = 1, la señal se encuentra separada por un guion y por lo tanto se procede a parsear sus componentes
		bool = 0;
		strAux = (char *)malloc(contNumber*sizeof(char));
		strAux2 = (char *)malloc(contSig*sizeof(char));
		for(i=0;i<25;i++){ //se recorre otra vez el string
			if(bool==0&&strSignal[i]!='-'){ //se ingresan a un arreglo los caracteres que constituyen el numero del hijo
				strAux[cont]=strSignal[i];
				cont++;
			}
			else if(bool==1&&strSignal[i]!='-'){//se ingresan a un arreglo los caracteres que constituyen el numero de la señal
				strAux2[cont]=strSignal[i];
				cont++;
				}
			if(strSignal[i]=='-'){//se reinicia contador al leer un guion
				bool = 1;
				cont = 0;
				}
			}
		nChild = strtol(strAux, &aux3, 10);
		nSig = strtol(strAux2, &aux3, 10); //se castean los arreglos de caracteres con strtol
		printf("%s - %s\n",strAux,strAux2);
		printf("numero hijo: %d\n",nChild);
		printf("señal; %d\n", nSig);
		if(nChild==0||nSig==0){ //si la conversion falla, strtol retorna 0, por lo tanto se retorna con un error
			return 0;
			}
		else{//si se cumplen todas las condiciones, se guarda la señal en la estructura signal
			sig->numHijo = nChild;
			sig->sName = nSig;
			}
		return 1;
		}
	else{ //si bool == 0, no se cumple con el formato N-S, por lo tanto se retorna con un error
		return 0;
		}
	}

void createSons(int numHijos, int *arrayPID, int flag){
	if(flag==1){
		printf("Mostrando informacion por pantalla:\n");
		}
	int i = 0, pid=0;
	for(i = 0; i<numHijos;i++){
		if((pid=fork())==0){	
			if(getpid()!=0){
				if(flag==1){
					printf("Número: %d, PID: %d\n",1+i,getpid());
				}
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
		counter++; //Numero de veces que se precionó Ctrl + c
		}
	
	/*if(counter==1){
		printf("mandar sigint\n");
		//kill(0,2);
		}*/
	
	//cuando se apretó por segunda vez Ctrl + c
	if(counter==2){
		if (opendir("temp")==NULL){
			keepRunning=0;
			exit(0);
			printf("XAO\n");
		}
		else{
			system("rm -r ./temp"); //función para eliminar la carpeta con los archivos del contador
			keepRunning=0;
			exit(0);
			printf("XAO\n");
		}
	}
	printf("keeprunning: %d\n",keepRunning);
	}

void getArguments(int argc, char *argv[], int *numHijos, int *flag){
	int flags, opt;
	int tfnd;

	int nChild = -1;
	tfnd = 0;
	flags = 0;
	while ((opt = getopt(argc, argv, "mh:")) != -1) {
	   switch (opt) {
	   case 'm':
		   flags = 1;
		   break;
	   case 'h':
		   nChild = atoi(optarg);
		   if(optarg!=0 && nChild==0){
				fprintf(stderr, "Usage: %s [-h nchild] [-m]\n", argv[0]);
				exit(EXIT_FAILURE);
			   }
		   printf("optarg: %s\n", optarg);
		   tfnd = 1;
		   break;
	   default: /* '?' */
		   fprintf(stderr, "Usage: %s [-h nchild] [-m]\n",
				   argv[0]);
		   exit(EXIT_FAILURE);
	   }
	}

	printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d\n",
		   flags, tfnd, nChild, optind);
	if(flags==1){
		(*flag) = 1;
		}
	(*numHijos) = nChild;
	/* Other code omitted */
	if(tfnd==0){
		fprintf(stderr, "Usage: %s [-h nchild] [-m]\n", argv[0]);
		exit(EXIT_FAILURE);
		}
	if(nChild<0){
		fprintf(stderr, "Usage: %s [-h nchild] [-m]\n", argv[0]);
		exit(EXIT_FAILURE);
		}


}

int main(int argc, char *argv[]){

	int numHijos = 0, flag = 0;
	pid_t *arrayPID;
	char *string,*signal2,*string2;
	Signal *sig;
	getArguments(argc, argv, &numHijos, &flag);
	printf("NUMERO HIJOS GETOPT: %d - ESTADO FLAG N: %d\n",numHijos,flag);
	sig = (Signal *)malloc(sizeof(Signal));
	signal2 = (char *)malloc(25*sizeof(char));
	string = (char *)malloc(25*sizeof(char));
	string2 = (char *)malloc(25*sizeof(char));
	arrayPID = (pid_t *) malloc(numHijos*sizeof(pid_t));
	createSons(numHijos, arrayPID, flag);
	signal(SIGINT,handler);	//Se agrega nuevamente para poder eliminar los archivos de contador
	int comprobacion = 0;
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
		getchar();
		
		}
	for(int i=0;i<numHijos;i++){ 
		exit(0);
		wait(NULL); 
	}
	printf("FINALIZANDO...\n");
	//exit(0);
	
	}
