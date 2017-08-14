#include <time.h>
#include "politicas.h"
#include "estruturas.c"
#include "logs.c"

void executa_politica(char* politica, char *arquivo, int quantum) {
    inicializa_logs();
    if (strcmp("fcfs", politica) == 0) {        
        fcfs(arquivo);
    } else if(strcmp("sjf", politica) == 0) {
        sjf(arquivo);
    } else if(strcmp("rr", politica) == 0){     
        rr(arquivo, quantum);
    }
    finaliza_logs();
}
void executa_processo(proc* processo) {
    processo->duracao = (processo->duracao - 1);
    processo->ciclos = (processo->ciclos + 1);
    salva_log_execucao(processo);
}
void rr(char* arquivo, int quantum) {    
    proc* processos = carrega_dados_lista(arquivo, 1);    
    proc* corrente = processos;
    int i;    
    while(restam_processos(&processos)) {
        if(corrente->duracao >= quantum) {
            for (i = 0 ; i < quantum ; i++) {
                executa_processo(corrente);
            } 
        }else {
            for (i = 0 ; i < corrente->duracao ; i++){
                executa_processo(corrente);
            }
        }
        corrente = corrente->proximo;
    }
    destroi_lista_circular(&processos);
}
void fcfs(char* arquivo) {
	proc* processos = carrega_dados_lista(arquivo, 0);    
    proc* corrente = processos;
    int id;
    while(restam_processos(&processos)) {        
        while(corrente->duracao > 0) {
            executa_processo(corrente);
        }
        id = corrente->id;
        corrente = corrente->proximo;
        remove_pelo_id(&processos, id);
    }    
    destroi_lista(processos);
}
void sjf(char* arquivo) {
    proc* processos = carrega_dados_lista(arquivo, 0);
    proc* corrente;    
    int ciclo_atual = processos->chegada;

    while(restam_processos(&processos)) {        
        corrente = busca_processo_ciclo(&processos, ciclo_atual);
        if (corrente->duracao == 0) {            
            remove_pelo_id(&processos, corrente->id);
        } else {
            executa_processo(corrente);            
        }        
        ciclo_atual++;
    }    
    destroi_lista(processos);    
}
proc* carrega_dados_lista(char* arquivo, int circular){
    int chegada, duracao;
    char id;
    proc *processos = cria_lista();

    FILE* entrada = fopen(arquivo, "r");

    if (entrada == NULL) {
        printf("Impossível abrir o arquivo\n");
        exit(1);
    }
    do{
        fscanf(entrada, "%c %d %d\n", &id, &chegada, &duracao);
        if(circular) {            
            insere_ordenado_chegada_circular(&processos,id,chegada,duracao);
        } else {
            insere_ordenado_chegada(&processos,id,chegada,duracao);
        }
    }while(!feof(entrada));

    fclose(entrada);
    return processos;
}