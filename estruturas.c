#include "estruturas.h"

proc* cria_lista(){	
	return NULL;
}
void destroi_lista(proc* lista) {
	proc* aux;
	while(lista != NULL) {
		aux = lista;
		lista = lista->proximo;
		free(aux);
	}
}
void insere_ordenado_chegada(proc **lista, int id, int chegada, int duracao){	
	proc** percorrer = lista;
	proc* anterior = NULL;
	proc* aux = *lista;
	proc* novo = malloc(sizeof(proc));
	if (!novo) {
		
		exit(1);
	}
	novo->id = id;
	novo->chegada = chegada;
	novo->proximo = NULL;
	novo->duracao = duracao;
	// Se a lista estivar vazia, o lemento novo é o começo da lista
	if (!*lista) {
		*lista = novo;
	} else {
		// Percorre a lista até encontrar a posição do novo processo
		while(*percorrer != NULL && (*percorrer)->chegada < novo->chegada){
			anterior = *percorrer;
			*percorrer = (*percorrer)->proximo;
		}
		// Se não ouver nenhum anterior é porque o novo processo tem chegada menor que o primeiro
		// elemento e deve ser inserido no inicio da lista
		if (anterior == NULL) {
			aux = *percorrer;			
			novo->proximo = aux;
			*lista = novo;
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
			*lista = aux;
		}
	}
}