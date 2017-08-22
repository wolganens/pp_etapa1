#include <time.h>
#include "estruturas.c"
#include "politicas.h"
#include "logs.c"
int n_processos = 0, ciclo_atual = 0;
void executa_politica(char* politica, char *arquivo, unsigned int quantum) {
    inicializa_logs(politica);
    lista* processos = carrega_dados_lista(arquivo);
    if (strcmp("fcfs", politica) == 0) {
        fcfs(processos);
    } else if(strcmp("sjf", politica) == 0) {
        sjf(processos);
    } else if(strcmp("rr", politica) == 0){
        rr(processos, quantum);
    }
    finaliza_logs();
}
void executa_processo(proc* processo) {
    if(processo != NULL){
        (processo->ciclos)++;
        (processo->duracao)--;
    }
    salva_log_execucao(processo);
}
void fcfs(lista* processos) {
    fila fila_de_execucao;
    // Inicializa a fila de execução de processos
    cria_fila(&fila_de_execucao);
    while(n_processos > 0){
        encontra_processo_ciclo(&fila_de_execucao, &processos, ciclo_atual);
        no* inicio_fila = fila_de_execucao.inicio;
        if (inicio_fila != NULL) {
            executa_processo(inicio_fila->processo);
            if(inicio_fila->processo->duracao == 0){
                remove_fila(&fila_de_execucao);
                n_processos--;
            }
        } else {
            executa_processo(NULL);
        }
        ciclo_atual++;
    }
    destroi_lista(processos);
}
void sjf(lista* processos){
    lista *execucao = cria_lista();
    // Inicializa a fila de execução de processos
    while(n_processos > 0){
        encontra_processo_sjf(&execucao, &processos, ciclo_atual);
        if (execucao != NULL) {
            executa_processo(execucao->processo);
            if(execucao->processo->duracao == 0){
                remove_lista_inicio(&execucao);
                n_processos--;
            }
        } else {
            executa_processo(NULL);
        }
        ciclo_atual++;
    }
    destroi_lista(processos);
}
void rr(lista* processos, unsigned int quantum){
    lista *execucao = cria_lista();
    while(n_processos > 0){    	
        encontra_processo_rr(&execucao, &processos, ciclo_atual);        
        if (execucao != NULL) {
        	if (execucao->processo->controle == quantum) {
        		execucao->processo->controle = 0;
        		execucao = execucao->proximo;
        	}
            executa_processo(execucao->processo);
            execucao->processo->controle+=1;
            if(execucao->processo->duracao == 0){
                remove_lista_circular_inicio(&execucao);
                n_processos--;
            }
        } else {
            executa_processo(NULL);
        }
        ciclo_atual++;
    }
    destroi_lista(processos);
}
lista* carrega_dados_lista(char* arquivo){
    int chegada, duracao;
    char id;
    lista *processos = cria_lista();
    FILE* entrada = fopen(arquivo, "r");
    if (entrada == NULL) {
        printf("Impossível abrir o arquivo\n");
        exit(1);
    }
    do{
        fscanf(entrada, "%c %d %d\n", &id, &chegada, &duracao);
        insere_ordenado_chegada(&processos,id,chegada,duracao);
        n_processos++;        
    }while(!feof(entrada));
    fclose(entrada);
    return processos;
}