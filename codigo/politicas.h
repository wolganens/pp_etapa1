lista* carrega_dados_lista(char* arquivo);
void fcfs(lista* processos);
void sjf(lista* processos);
void rr(lista* processos, unsigned int quantum);
void exec_escalonador(char* politica, char *arquivo, unsigned int quantum);