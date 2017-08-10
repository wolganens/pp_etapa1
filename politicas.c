#include "politicas.h"
#include "estruturas.c"

void fcfs(FILE *entrada) {
	int id = 0, chegada, duracao,i;
	proc *cabeca_lista = cria_lista();	
	do{
		fscanf(entrada, "%d %d", &chegada,&duracao);		
		cabeca_lista = insere_ordenado_chegada(cabeca_lista,id,chegada,duracao);
		printf("%d\n", cabeca_lista->id);
		id++;
		// Neste laço cada linha do arquivo é mapeada para as variaveis chegada e duração.
		// Aqui deve ser armazenado na estrutura adequada a chegada identificador (id) e duração do processo
	}while(!feof(entrada));	
	
	// while(cabeca_lista != NULL) {		
	// 	for (i = 0 ; i < cabeca_lista->duracao ; i++) {			
	// 		printf("| %d ", cabeca_lista->id);
	// 	}
	// 	cabeca_lista = cabeca_lista->proximo;
	// }
	// printf("|\n");
	destroi_lista(cabeca_lista);
}