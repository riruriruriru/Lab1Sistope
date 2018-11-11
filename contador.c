#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int auxCont;
	char directorio[50];
	char archivo[20];
	strcpy(directorio,"temp/");
	strcpy(archivo,argv[1]);
	strcat(archivo,".txt");
	strcat(directorio,archivo);
	
	if (opendir("temp")==NULL){
		system("mkdir temp");
	}
	
	//printf("Directorio %s\n",directorio);
	FILE *cont;
	cont = fopen(directorio,"r");
	if (cont == NULL){
		cont = fopen(directorio,"w");
		fprintf(cont,"%d",1);
		printf("pid: %s, y he recibido esta llamada 1 vez.\n",argv[1]);
		fclose(cont);
	}
	else{
		fscanf(cont,"%d",&auxCont);
		auxCont+=1;
		printf("pid: %s, y he recibido esta llamada %d veces.\n",argv[1],auxCont);
		fclose(cont);
		FILE *cont;
		cont = fopen(directorio,"w");
		fprintf(cont,"%d",auxCont);
		fclose(cont);
		
	}
	//printf("Hola soy un contador y mi archivo es: %s/n",archivo);
	exit(0);
}
