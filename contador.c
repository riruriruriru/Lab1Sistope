#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


//Función contador que generá un archivo con el nombre del proceso que lo llamó y guarda las veces que ha sido llamado por el proceso
//Entradas: String que representa el pid del proceso que llamó a este proceso
//Salidas: Vacio
void contadorHijo(char *pid){
	int auxCont;
	char directorio[50];
	char archivo[20];
	
	//Se copia el directorio donde esta el archivo en la variable directorio
	strcpy(directorio,"temp/");
	strcpy(archivo,pid);
	strcat(archivo,".txt");
	strcat(directorio,archivo);
	
	if (opendir("temp")==NULL){ //Verifica si no existe la carpeta temporal temp, que guarda los archivos para el contador
		system("mkdir temp");   //Crea la carpeta temp
	}
	FILE *cont;
	cont = fopen(directorio,"r");
	
	if (cont == NULL){ //Verifica si el archivo de nombre del pid del proceso no existe
		cont = fopen(directorio,"w");//Si no existe el archivo lo crea 
		fprintf(cont,"%d",1);
		printf("pid: %s, y he recibido esta llamada 1 vez.\n",pid);
		fclose(cont);
	}
	
	//Si existe el archivo, recupera el numero le suma uno, lo muestra por pantalla y guarda ese numero
	else{
		fscanf(cont,"%d",&auxCont);
		auxCont+=1;
		printf("pid: %s, y he recibido esta llamada %d veces.\n",pid,auxCont);
		fclose(cont);
		FILE *cont;
		cont = fopen(directorio,"w");
		fprintf(cont,"%d",auxCont);
		fclose(cont);
		
	}
}



int main(int argc, char *argv[]){
	//argv[1] contiene el pid del proceso que recibio la señal para llamar a contador
	contadorHijo(argv[1]);
	exit(0);
}
