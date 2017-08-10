#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "politicas.c"

int main(int argc, char const *argv[])
{
	FILE *entrada;
	int i;
	char *arquivo, *politica;
	if (argc < 5) {
		printf("Especifique o arquivo de entrada e a política desejada.\nEx: ./escalonador -e entrada.txt -p fcfs \n");
		exit(1);
	}
	for ( i = 1 ; i < argc ; i++) {		
		if (strcmp(argv[i], "-e") == 0) {
			arquivo = malloc(strlen(argv[i] + 1) * sizeof(char));
			strcpy(arquivo,argv[i + 1]);
		} else if (strcmp(argv[i], "-p") == 0) {
			politica = malloc(strlen(argv[i] + 1) * sizeof(char));
			strcpy(politica,argv[i + 1]);
		}
	}	
	entrada = fopen(arquivo, "r");
	if (entrada == NULL) {
		printf("Impossível abrir o arquivo\n");
		exit(1);
	}	
	if (strcmp("fcfs", politica) == 0) {		
		fcfs(entrada);
	} else if(strcmp("sjf", politica) == 0) {
	} else if(strcmp("rr", politica) == 0){
	}
	
	fclose(entrada);
	return 0;
}