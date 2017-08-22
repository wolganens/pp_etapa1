struct processo{
	char id;
	int chegada,duracao,ciclos;
	unsigned int controle;
};
typedef struct processo proc;

struct __no {
	proc* processo;
	struct __no* proximo;
};

typedef struct __no no;

struct __fila
{
	no* inicio, *fim;
};

typedef struct __fila fila;

struct processos
{
	proc* processo;
	struct processos* proximo;
};
typedef struct processos lista;

lista* novo_processo(char id, int chegada, int duracao);
void cria_fila();
void insere_fila(fila* fila_ptr, proc* processo);
void insere_fila_ord_duracao(fila* fila_ptr, proc* processo);
void insere_inicio_fila(fila* fila_ptr, proc* processo);
void remove_fila(fila* fila_ptr);

void encontra_processo_ciclo(fila* fila_ptr, lista** processos, int ciclo_atual);
void encontra_processo_sjf(lista** execucao, lista** processos, int ciclo_atual);
void insere_ordenado_chegada(lista **lista, char id, int chegada, int duracao);
void insere_ordenado_duracao(lista **lista_ptr, proc* processo);
void insere_ordenado_chegada_circular(lista** execucao, proc* processo);

lista* cria_lista();
void insere_final(fila** fila_ptr, proc* processo);
void destroi_lista(lista* lista_ptr);
void remove_lista_inicio(lista** lista_ptr);

