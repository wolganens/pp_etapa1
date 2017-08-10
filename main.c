#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	FILE *entrada;
	int id = 0, chegada, duracao, i;
	char *arquivo, *politica;
	if (argc < 5) {
		printf("Especifique o arquivo de entrada e a política desejada.\nEx: ./escalonador -e entrada.txt -p fcfs \n");
		exit(1);
	}
	for ( i = 1 ; i < argc ; i++) {
		if (strcmp(argv[i], "-e") == 0) {
			arquivo = malloc(strlen(argv[i]) * sizeof(char));
			strcpy(arquivo,argv[i + 1]);
		} else if (strcmp(argv[i], "-p") == 0) {
			politica = malloc(strlen(argv[i]) * sizeof(char));
			strcpy(politica,argv[i] + 1);
		} else {
			printf("Parâmetros incorretos. Verifique se você informou o arquivo de entrada (-e) e a política desejada (-p)\n");
		}
	}	
	entrada = fopen(arquivo, "r");
	if (entrada == NULL) {
		printf("Impossível abrir o arquivo\n");
		exit(1);
	}	
	do{
		fscanf(entrada, "%d %d\n", &chegada,&duracao);
		id++;
		// Neste laço cada linha do arquivo é mapeada para as variaveis chegada e duração.
		// Aqui deve ser armazenado na estrutura adequada a chegada identificador (id) e duração do processo
	}while(!feof(entrada));

	fclose(entrada);
	return 0;
}