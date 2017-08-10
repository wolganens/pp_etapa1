struct processo{
	int id,chegada,duracao;
	struct processo *proximo;
};
typedef struct processo proc;

proc* cria_lista();
void destroi_lista(proc* lista);
proc* insere_ordenado_chegada(proc *lista, int id, int chegada, int duracao);