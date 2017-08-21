#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codigo/politicas.c"
int define_var_argumento(const char *argv, char** variavel) {
	int tam_nome_arquivo = strlen(argv) + 1;
	*variavel = malloc(tam_nome_arquivo * sizeof(char));
	strcpy(*variavel, argv);
}
int main(int argc, char const *argv[])
{
	int i, quantum = 2;
	char *arquivo, *politica;
	if (argc < 5) {
		printf("Especifique o arquivo de entrada e a política desejada.\nEx: ./escalonador -e entrada.txt -p fcfs \n");
		exit(1);
	}
	for ( i = 1 ; i < argc ; i++) {
		if (strcmp(argv[i], "-e") == 0) {
			define_var_argumento(argv[i + 1], &arquivo);
		} else if (strcmp(argv[i], "-p") == 0) {
			define_var_argumento(argv[i + 1], &politica);
		} else if (strcmp(argv[i], "-q") == 0) {
			quantum = atoi(argv[i + 1]);
		}
	}
	executa_politica(politica, arquivo, quantum);
	free(arquivo);
	free(politica);
	return 0;
}