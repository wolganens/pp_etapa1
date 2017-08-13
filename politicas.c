#include <time.h>
#include "politicas.h"
#include "estruturas.c"

#define quantum 2

char* gera_nome_log() {
	char buff[50], pasta_logs[80];
    struct tm *sTm;
    time_t now = time (0);    
    sTm = gmtime (&now);
	strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
	strcpy(pasta_logs, "./logs/");
    return strcat(pasta_logs, buff);
}
void escreve_log_saida_fcfs(proc* processo, int ciclo) {
    FILE *saida;
    char pasta_logs[80];
    strcpy(pasta_logs,gera_nome_log());
    saida = fopen(pasta_logs,"a+");    
	fprintf(saida, "%c%d ", processo->id, ciclo);    	    		
    fclose(saida);
}
void escreve_log_saida_sjf(proc* processo) {
    FILE *saida;
    char pasta_logs[80];
    strcpy(pasta_logs, gera_nome_log());
    saida = fopen(pasta_logs, "a+");
    fprintf(saida, "%c%d ", processo->id, processo->ciclos);
    fclose(saida);
}
void rr(char* arquivo) {    
    proc* processos = carrega_dados_lista(arquivo, 1);    
    proc* corrente = processos;
    int i;
    printf("%c\n", processos->id);
    
    // while(restam_processos(&processos)) {
    //     if (corrente->duracao == 0) {            
    //         remove_pelo_id(&processos, corrente->id);
    //     } else {
    //         for (i = 0 ; i < quantum ; i++) {
    //             corrente->duracao = (corrente->duracao - 1);
    //             corrente->ciclos = (corrente->ciclos + 1);
    //             escreve_log_saida_sjf(corrente);            
    //         }        
    //     }
    //     corrente = corrente->proximo;
    // }
    //destroi_lista(processos);
}
void fcfs(char* arquivo) {
	proc* processos = carrega_dados_lista(arquivo, 0);
    int i;
    
    while(processos != NULL) {
        for (i = 0 ; i < processos->duracao ; i++) {
            escreve_log_saida_fcfs(processos,i);
        }
        processos = processos->proximo;
    }
    destroi_lista(processos);
}
void sjf(char* arquivo) {
    proc* processos = carrega_dados_lista(arquivo, 0);
    proc* corrente;    
    int ciclo_atual = processos->chegada, ciclo = 1;        

    while(restam_processos(&processos)) {        
        corrente = busca_processo_ciclo(&processos, ciclo_atual);        
        if (corrente->duracao == 0) {            
            remove_pelo_id(&processos, corrente->id);
        } else {
            corrente->duracao = (corrente->duracao - 1);
            corrente->ciclos = (corrente->ciclos + 1);
            escreve_log_saida_sjf(corrente);            
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