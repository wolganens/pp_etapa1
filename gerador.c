#include <stdio.h>
#include "random.c"

int main(int argc, char const *argv[])
{
	int n = 1000, i, duracao, chegada;
	char id;
	FILE * teste = fopen("teste.txt", "a+");
	for (i = 0 ; i < n ; i++){
		unsigned int id = i;
		duracao = random_in_range(1, 100);
		chegada = random_in_range(0, 1000);
		fprintf(teste, "%u %d %d\n", id, chegada, duracao);
	}
	fclose(teste);
	return 0;
}