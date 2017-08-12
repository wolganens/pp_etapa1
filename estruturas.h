struct processo{
	char id;
	int chegada,duracao,ciclos;
	struct processo *proximo;
};
typedef struct processo proc;

proc* cria_lista();
proc* menor_duracao(proc* lista);
void destroi_lista(proc* lista);
void insere_ordenado_chegada(proc **lista, char id, int chegada, int duracao);
void escreve_log_saida();
void remove_pelo_id(proc* lista, char id);