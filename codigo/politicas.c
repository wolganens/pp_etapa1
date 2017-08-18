#include <time.h>
#include "estruturas.c"
#include "politicas.h"
#include "logs.c"

void executa_politica(char* politica, char *arquivo, int quantum) {
    inicializa_logs(politica);
    if (strcmp("fcfs", politica) == 0) {        
        fcfs(arquivo);
    }
    // } else if(strcmp("sjf", politica) == 0) {
    //     sjf(arquivo);
    // } else if(strcmp("rr", politica) == 0){     
    //     rr(arquivo, quantum);
    // }
    finaliza_logs();
}
void executa_processo(fila* fila_de_execucao, int* n_processos) {
    no* inicio_fila = fila_de_execucao->inicio;        
    
    inicio_fila->processo->ciclos = (inicio_fila->processo->ciclos + 1);    
    salva_log_execucao(inicio_fila->processo);        
    if(inicio_fila->processo->duracao == 0) {        
        remove_fila(fila_de_execucao);  
        (*n_processos)--;                
    } else {
        inicio_fila->processo->duracao = (inicio_fila->processo->duracao - 1);
    }
}
// void rr(char* arquivo, int quantum) {    
//     proc* processos = carrega_dados_lista(arquivo, 1);    
//     proc* corrente = processos;
//     int i; 
//     while(restam_processos(&processos)) {
//         if(corrente->duracao >= quantum) {
//             for (i = 0 ; i < quantum ; i++) {
//                 executa_processo(corrente);
//             } 
//         }else {
//             if (corrente->duracao == 0) {
//                 remove_pelo_id(&processos, corrente->id);
//             } else {
//                 while(corrente->duracao > 0){                    
//                     executa_processo(corrente);
//                 }
//             }
//         }
//         corrente = corrente->proximo;
//     }
//     destroi_lista_circular(&processos);
// }
void fcfs(char* arquivo) {
    int n_processos = 0, ciclo_atual = 0;
    lista* processos = carrega_dados_lista(arquivo, 0, &n_processos);
    fila fila_de_execucao;
    proc* processo_ciclo_atual = NULL;
    
    // Inicializa a fila de execução de processos
    cria_fila(&fila_de_execucao);
    
    while(n_processos > 0){        
        encontra_processo_ciclo(&fila_de_execucao, &processos, ciclo_atual);
        executa_processo(&fila_de_execucao, &n_processos);
        ciclo_atual++;
    }    
    
    destroi_lista(processos);
    destroi_fila(&fila_de_execucao);
}
// void sjf(char* arquivo) {
//     proc* processos = carrega_dados_lista(arquivo, 0);
//     proc* corrente;
//     int ciclo_atual = processos->chegada;
//     while(restam_processos(&processos)) {        
//         corrente = busca_processo_ciclo(&processos, ciclo_atual);
//         if (corrente->duracao == 0) {
//             remove_pelo_id(&processos, corrente->id);
//         } else {
//             executa_processo(corrente);
//         }
//         ciclo_atual++;
//     }
//     destroi_lista(processos);    
// }
lista* carrega_dados_lista(char* arquivo, int circular, int *n_processos){
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
        (*n_processos)++;
        // if(circular) {            
        //     insere_ordenado_chegada_circular(&processos,id,chegada,duracao);
        // } else {
        //     insere_ordenado_chegada(&processos,id,chegada,duracao);
        // }
    }while(!feof(entrada));

    fclose(entrada);
    return processos;
}