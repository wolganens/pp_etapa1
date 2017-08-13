#include "estruturas.h"

proc* cria_lista(){	
	return NULL;
}
int vazia(proc** lista){
	return *lista == NULL;
}
void remove_pelo_id(proc** lista, char id){	
	proc** percorrer = lista;
	proc* anterior = NULL;
	proc* aux = *lista;		
	if (!*lista) {
		printf("Lista vazia\n");
		exit(1);
	} else {
		// Percorre a lista até encontrar o processo
		while(*percorrer != NULL && (*percorrer)->id != id){
			anterior = *percorrer;
			*percorrer = (*percorrer)->proximo;
		}
		// Se não ouver nenhum anterior é porque o novo processo tem chegada menor que o primeiro
		// elemento e deve ser inserido no inicio da lista
		if (anterior == NULL) {
			aux = *percorrer;			
			*lista = aux->proximo;
		} else {
			if (*percorrer == NULL) {
				printf("Não encontrado\n");
				exit(1);
			} else {
				anterior->proximo = (*percorrer)->proximo;				
			}
			*lista = aux;
		}
	}
}
proc* menor_duracao(proc** lista) {
	if (*lista == NULL) {
		printf("Não há processos para execução\n");
		exit(1);
	}
	proc **percorrer = lista;
	proc *aux = *lista;
	proc *menor = *lista;
	while(*percorrer != NULL) {		
		if((*percorrer)->duracao < menor->duracao) {
			menor = (*percorrer);
		}
		*percorrer = (*percorrer)->proximo;		
	}
	*lista = aux;
	return menor;
}
void destroi_lista(proc* lista) {
	proc* aux;
	while(lista != NULL) {		
		aux = lista;
		lista = lista->proximo;
		free(aux);
	}
}
void destroi_lista_circular(proc** lista) {
	proc* aux = (*lista);
	proc* remover;	
	while (aux->proximo != (*lista)) {		
		aux = aux->proximo;		
	}
	free(aux);
}
void insere_ordenado_chegada(proc **lista, char id, int chegada, int duracao){	
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
	novo->ciclos = 0;
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
proc* novo_processo(char id, int chegada, int duracao){
	proc* novo = malloc(sizeof(proc));
	if (novo == NULL) {
		printf("Falha ao alocar memória para o processo\n");
		exit(1);
	}
	novo->id = id;
	novo->chegada = chegada;
	novo->duracao = duracao;
	return novo;
}
void insere_ordenado_chegada_circular(proc **lista, char id, int chegada, int duracao){	
	proc* novo = novo_processo(id, chegada, duracao);
	proc* anterior = NULL;
	if ((*lista) == NULL) {
		*lista = novo;
		novo->proximo = novo;
	} else {
		proc* aux = (*lista);
		while(aux->proximo != (*lista) && aux->chegada < novo->chegada){
			anterior = aux;
			aux = aux->proximo;
		}
		if (anterior == NULL) {
			if (novo->chegada > aux->chegada) {
				aux->proximo = novo;
				novo->proximo = aux;
			} else {
				(*lista) = novo;
				novo->proximo = aux;
				aux->proximo = novo;				
			}
		} else {
			aux->proximo = novo;
			novo->proximo = (*lista);
		}
	}	
}
int restam_processos(proc** lista) {
	int restam = 0;
	proc* inicio = *lista;
	proc** percorrer = lista;			
	while(*percorrer != NULL && (*percorrer)->proximo != inicio) {
		if ((*percorrer)->duracao > 0) {
			restam = 1;			
		}
		*percorrer = (*percorrer)->proximo;
	}
	*lista = inicio;
	return restam;
}
proc* busca_processo_ciclo(proc** processos, int ciclo_atual) {
	proc** percorrer = processos;
	proc* inicio = *processos;
	proc* processo = NULL;	

	while(*percorrer != NULL) {		
		if ((*percorrer)->chegada <= ciclo_atual) {			
			if (processo != NULL) {
				if ((*percorrer)->duracao < processo->duracao) {					
					processo = *percorrer;
				}
			} else {				
				processo = *percorrer;
			}
		}
		*percorrer = (*percorrer)->proximo;
	}
	if (processo == NULL) {
		processo = inicio;
		*percorrer = inicio->proximo;		
		while(*percorrer != NULL) {
			if ((*percorrer)->duracao < processo->duracao) {
				processo = *percorrer;
			}
			*percorrer = (*percorrer)->proximo;
		}
	}
	*processos = inicio;
	return processo;
}