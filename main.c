#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	FILE *entrada = fopen("entrada.txt", "r");
	int a,b,c, linha;

	if (entrada == NULL) {
		printf("Impossível abrir o arquivo\n");
		exit(1);
	}	
	do{
		linha = fscanf(entrada, "%d %d %d\n", &a,&b,&c);
	}while(!feof(entrada));

	printf("%d %d %d\n", a,b,c);
	fclose(entrada);
	return 0;
}