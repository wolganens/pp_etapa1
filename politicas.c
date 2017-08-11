#include <time.h>
#include "politicas.h"
#include "estruturas.c"

void fcfs(FILE *entrada) {
	int id = 0, chegada, duracao;
	proc *cabeca_lista = cria_lista();
	do{
		fscanf(entrada, "%d %d", &chegada,&duracao);		
		insere_ordenado_chegada(&cabeca_lista,id,chegada,duracao);
		id++;		
	}while(!feof(entrada));

	escreve_log_saida(cabeca_lista);
	destroi_lista(cabeca_lista);	
}
void escreve_log_saida(proc* cabeca_lista) {
	char buff[50], pasta_logs[80];	
    struct tm *sTm;
    time_t now = time (0);
    int i, ciclo = 1;
    FILE *saida;

    sTm = gmtime (&now);
	strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
	strcpy(pasta_logs, "./logs/");	
    saida = fopen(strcat(pasta_logs, strcat(buff, "-fcfs.log")),"w");

    while(cabeca_lista != NULL) {
    	for ( i = 1 ; i < cabeca_lista->duracao ; i++) {
    		fprintf(saida, "Processo %d ocupou a cpu no ciclo %d\n", cabeca_lista->id, ciclo);
    		ciclo++;
    	}
    	fprintf(saida, "\n");
    	cabeca_lista = cabeca_lista->proximo;
    }
    fclose(saida);
}