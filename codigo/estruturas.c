#include "estruturas.h"
lista* cria_lista(){
	return NULL;
}
void cria_fila(fila* f){
	f->inicio = NULL;
	f->fim = NULL;
}
void encontra_processo_ciclo(fila* fila_ptr, lista** processos, int ciclo_atual){
	lista* aux = *processos;
	while(aux != NULL) {
		if(aux->processo->chegada == ciclo_atual){
			insere_fila(fila_ptr, aux->processo);
		}
		aux = aux->proximo;
	}
}
void encontra_processo_rr(lista** execucao, lista** processos, int ciclo_atual) {
	lista* aux = *processos;
	while(aux != NULL) {
		if(aux->processo->chegada == ciclo_atual){
			insere_ordenado_chegada_circular(execucao, aux->processo);
		}
		aux = aux->proximo;
	}
}
void insere_fila(fila* fila_ptr, proc* processo) {
	no* novo = malloc(sizeof(no));
	novo->processo = processo;
	novo->proximo = NULL;
	if(fila_ptr->fim != NULL){
		fila_ptr->fim->proximo = novo;
	} else {
		fila_ptr->inicio = novo;
	}
	fila_ptr->fim = novo;
}
void encontra_processo_sjf(lista** execucao, lista** processos, int ciclo_atual){
	lista* aux = *processos;
	while(aux != NULL) {
		if(aux->processo->chegada == ciclo_atual){
			insere_ordenado_duracao(execucao, aux->processo);
		}
		aux = aux->proximo;
	}
}
void remove_fila(fila* fila_ptr){
	if(fila_ptr->inicio != NULL){
		no* inicio = fila_ptr->inicio;
		if (inicio->proximo != NULL) {
			fila_ptr->inicio = inicio->proximo;
			free(inicio);
		}
		if(inicio == fila_ptr->fim) {
			free(fila_ptr->fim);
			fila_ptr->inicio = NULL;
			fila_ptr->fim = NULL;
		}
	}
}
void remove_lista_inicio(lista** lista_ptr) {
	if (*lista_ptr != NULL) {
		lista* aux = *lista_ptr;
		if ((*lista_ptr)->proximo != NULL) {
			(*lista_ptr) = aux->proximo;
		} else {
			*lista_ptr = NULL;
		}
		free(aux);
	}
}
void remove_lista_circular_inicio(lista** lista_ptr) {
	if (*lista_ptr != NULL) {
		if (*lista_ptr == (*lista_ptr)->proximo) {
			free(*lista_ptr);
			*lista_ptr = NULL;
		} else {
			lista* aux = *lista_ptr;
			while(aux->proximo != *lista_ptr) {
				aux = aux->proximo;
			}
			lista* inicio = *lista_ptr;
			*lista_ptr = (*lista_ptr)->proximo;
			free(inicio);
			aux->proximo = *lista_ptr;
		}
	}
}
void insere_ordenado_duracao(lista **lista_ptr, proc* processo){
	lista** percorrer = lista_ptr;
	lista* anterior = NULL;
	lista* aux = *lista_ptr;
	lista* novo = malloc(sizeof(lista));
	novo->proximo = NULL;
	if(novo == NULL) {
		printf("Falha ao alocar memória para novo nó da lista\n");
		exit(1);
	}
	novo->processo = processo;
	// Se a lista estivar vazia, o lemento novo é o começo da lista
	if (*lista_ptr == NULL) {
		*lista_ptr = novo;
	} else {
		// Percorre a lista até encontrar a posição do novo processo
		while((*percorrer) != NULL && (*percorrer)->processo->duracao < novo->processo->duracao){
			anterior = *percorrer;
			*percorrer = (*percorrer)->proximo;
		}
		// Se não ouver nenhum anterior é porque o novo processo tem duracao menor que o primeiro
		// elemento e deve ser inserido no inicio da lista
		if (anterior == NULL) {
			aux = *percorrer;
			novo->proximo = aux;
			*lista_ptr = novo;
		} else {
			// Se chegou no final da lista, ou seja o novo processo chegou por último
			// apenas insere ele no final
			if (*percorrer == NULL) {
				anterior->proximo = novo;
			} else {
				// Caso contrário, insere o novo processo no meio da lista na posição adequada
				anterior->proximo = novo;
				novo->proximo = *percorrer;
			}
			//Mantem o começo da lista apontando para o primeiro elemento (aux);
			*lista_ptr = aux;
		}
	}
}
void insere_ordenado_chegada(lista **lista_ptr, unsigned int id, int chegada, int duracao){
	lista** percorrer = lista_ptr;
	lista* anterior = NULL;
	lista* aux = *lista_ptr;
	lista* novo = malloc(sizeof(lista));
	novo->proximo = NULL;
	if(novo == NULL) {
		printf("Falha ao alocar memória para novo nó da lista\n");
		exit(1);
	}
	proc* novo_processo = malloc(sizeof(proc));
	if (novo_processo == NULL) {
		printf("Falha ao alocar memória para o processo\n");
		exit(1);
	}
	novo_processo->id = id;
	novo_processo->chegada = chegada;
	novo_processo->duracao = duracao;
	novo_processo->ciclos = 0;
	novo_processo->controle = 0;
	novo->processo = novo_processo;
	// Se a lista estivar vazia, o lemento novo é o começo da lista
	if (*lista_ptr == NULL) {
		*lista_ptr = novo;
	} else {
		// Percorre a lista até encontrar a posição do novo processo
		while((*percorrer) != NULL && (*percorrer)->processo->chegada < novo->processo->chegada){
			anterior = *percorrer;
			*percorrer = (*percorrer)->proximo;
		}
		// Se não ouver nenhum anterior é porque o novo processo tem chegada menor que o primeiro
		// elemento e deve ser inserido no inicio da lista
		if (anterior == NULL) {
			aux = *percorrer;
			novo->proximo = aux;
			*lista_ptr = novo;
		} else {
			// Se chegou no final da lista, ou seja o novo processo chegou por último
			// apenas insere ele no final
			if (*percorrer == NULL) {
				anterior->proximo = novo;
			} else {
				// Caso contrário, insere o novo processo no meio da lista na posição adequada
				anterior->proximo = novo;
				novo->proximo = *percorrer;
			}
			//Mantem o começo da lista apontando para o primeiro elemento (aux);
			*lista_ptr = aux;
		}
	}
}
void destroi_lista(lista* lista_ptr) {
	lista* aux = lista_ptr;
	lista* prox = NULL;
	while(aux != NULL) {
		prox = aux->proximo;
		free(aux->processo);
		free(aux);
		aux = prox;
	}
}
void insere_ordenado_chegada_circular(lista** execucao, proc* processo){
	lista* novo = malloc(sizeof(lista));
	novo->proximo = NULL;
	processo->controle = 0;
	novo->processo = processo;
 	lista* anterior = NULL;
 	if ((*execucao) == NULL) {
 		*execucao = novo;
 		novo->proximo = novo;
 	} else {
 		lista* aux = (*execucao);
 		while(aux->proximo != (*execucao) && aux->processo->chegada < novo->processo->chegada){
 			anterior = aux;
 			aux = aux->proximo;
 		}
 		if (anterior == NULL) {
 			if (novo->processo->chegada > aux->processo->chegada) {
 				aux->proximo = novo;
 				novo->proximo = aux;
 			} else {
 				(*execucao) = novo;
 				novo->proximo = aux;
 				aux->proximo = novo;
 			}
 		} else {
 			novo->proximo = aux->proximo;
 			aux->proximo = novo;
 		}
 	}
}
