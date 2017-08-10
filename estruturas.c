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
proc* insere_ordenado_chegada(proc *lista, int id, int chegada, int duracao){	
	proc* percorrer = lista;
	proc* anterior = NULL;
	proc* aux;
	proc* novo = malloc(sizeof(proc));
	novo->id = id;
	novo->chegada = chegada;
	novo->proximo = NULL;
	novo->duracao = duracao;
	if (!lista) {
		lista = novo;
	} else {
		while(percorrer != NULL && percorrer->chegada <= chegada) {
			anterior = percorrer;
			percorrer = percorrer->proximo;
		}
		if (percorrer == NULL) {		
			anterior->proximo = novo;			
		} else {
			if (anterior != NULL) {
				novo->proximo = anterior->proximo;
				anterior->proximo = novo;
			} else {
				percorrer->proximo = lista;
				lista = novo;
			}
		}
	}
	return lista;
}