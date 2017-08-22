lista* carrega_dados_lista(char* arquivo, int circular);
void fcfs(lista* processos);
void sjf(lista* processos);
void rr(lista* processos, int quantum);
void exec_escalonador(char* politica, char *arquivo, int quantum);