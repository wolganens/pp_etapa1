#include <time.h>
#include "politicas.h"
#include "estruturas.c"

void escreve_log_saida_fcfs(proc* cabeca_lista) {
	char buff[50], pasta_logs[80];
    struct tm *sTm;
    time_t now = time (0);
    int i;
    FILE *saida;

    sTm = gmtime (&now);
	strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
	strcpy(pasta_logs, "./logs/");
    saida = fopen(strcat(pasta_logs, strcat(buff, "-fcfs.log")),"w");

    while(cabeca_lista != NULL) {
    	for ( i = 1 ; i <= cabeca_lista->duracao ; i++) {
    		fprintf(saida, "%c%d ", cabeca_lista->id, i);
    	}
    	fprintf(saida, "\n");
    	cabeca_lista = cabeca_lista->proximo;
    }
    fclose(saida);
}
void escreve_log_saida_sjf(proc* cabeca_lista) {
    proc *corrente;
    char buff[50], pasta_logs[80];
    struct tm *sTm;
    time_t now = time (0);
    int i;
    FILE *saida;

    sTm = gmtime (&now);
    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
    strcpy(pasta_logs, "./logs/");
    saida = fopen(strcat(pasta_logs, strcat(buff, "-fcfs.log")),"w");

    do{
        corrente = menor_duracao(cabeca_lista);
        fprintf(saida, "%c%d ", corrente->id, corrente->ciclos);
        corrente->duracao = corrente->duracao--;
        if(corrente->duracao == 0){
            remove_pelo_id(&cabeca_lista, corrente->id);
        }
    }while(!vazia(cabeca_lista));
    fclose(saida);
}
void fcfs(FILE *entrada) {
	int chegada, duracao;
    char id;
	proc *cabeca_lista = cria_lista();
	do{
		fscanf(entrada, "%c %d %d\n", &id, &chegada, &duracao);
		insere_ordenado_chegada(&cabeca_lista,id,chegada,duracao);
	}while(!feof(entrada));

	escreve_log_saida_fcfs(cabeca_lista);
	destroi_lista(cabeca_lista);
}
void sjf(FILE *entrada) {
    int chegada, duracao;
    char id;
    proc *cabeca_lista = cria_lista();
    do{
        fscanf(entrada, "%c %d %d\n", &id, &chegada, &duracao);
        insere_ordenado_duracao(&cabeca_lista,id,chegada,duracao);
    }while(!feof(entrada));

    escreve_log_saida_sjf(cabeca_lista);
    destroi_lista(cabeca_lista);
}
