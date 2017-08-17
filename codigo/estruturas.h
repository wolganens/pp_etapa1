struct processo{
	char id;
	int chegada,duracao,ciclos;	
};
typedef struct processo proc;

struct f {
	proc* processo;
	struct f* proximo, *final;
};

typedef struct f fila;

struct processos
{
	proc* processo;
	struct processos* proximo;
};
typedef struct processos lista;

lista* novo_processo(char id, int chegada, int duracao);
lista* cria_lista();
proc* encontra_processo_ciclo(fila** fila, lista** processos, int ciclo_atual);
void insere_ordenado_chegada(lista **lista, char id, int chegada, int duracao);
void insere_final(fila** fila_ptr, proc* processo);
void pop(fila** fila_ptr);




// proc* menor_duracao(proc** lista);
// proc* carrega_dados_lista(char* arquivo,int circular);
// proc* busca_processo_ciclo(proc** processos, int ciclo_atual);
// void encontra_processo_ciclo(proc** fila, proc** lista, int ciclo);
// void destroi_lista(proc* lista);
// void remove_pelo_id(proc** lista, char id);
// void push(proc** final, proc* processo);
// void insere_final(proc** fila, proc* processo);
