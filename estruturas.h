struct processo{
	char id;
	int chegada,duracao;
	struct processo *proximo;
};
typedef struct processo proc;

proc* cria_lista();
void destroi_lista(proc* lista);
void insere_ordenado_chegada(proc **lista, char id, int chegada, int duracao);
void escreve_log_saida();