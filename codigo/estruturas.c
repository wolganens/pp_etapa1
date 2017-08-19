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
void remove_fila(fila* fila_ptr){	
	if(fila_ptr->inicio != NULL){
		no* inicio = fila_ptr->inicio;
		if (inicio->proximo != NULL) {
			fila_ptr->inicio = inicio->proximo;			
			free(inicio);
			inicio = NULL;
		}
		if(inicio == fila_ptr->fim) {
			free(fila_ptr->fim);
			fila_ptr->fim = NULL;
		}
	}
}
void insere_fila(fila* fila_ptr, proc* processo) {
	no* novo = malloc(sizeof(fila));
	novo->processo = processo;
	novo->proximo = NULL;

	if(fila_ptr->fim != NULL){
		fila_ptr->fim->proximo = novo;
	} else {
		fila_ptr->inicio = novo;
	}
	fila_ptr->fim = novo;	
}
void destroi_fila(fila* fila_ptr) {
	no* aux = fila_ptr->inicio;
	no* prox;
	while(aux != NULL) {
		prox = aux->proximo;
		free(aux->processo);
		free(aux);
		aux = prox;
	}		
}
void insere_ordenado_chegada(lista **lista_ptr, char id, int chegada, int duracao){	
	lista** percorrer = lista_ptr;
	lista* anterior = NULL;
	lista* aux = *lista_ptr;
	lista* novo = novo_processo(id, chegada, duracao);
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
	lista* aux = NULL;
	while(lista_ptr != NULL) {		
		aux = lista_ptr;
		lista_ptr = lista_ptr->proximo;			
		free(aux);
	}
}
// int vazia(proc** lista){
// 	return *lista == NULL;
// }
// void remove_pelo_id(proc** lista, char id){	
// 	proc** percorrer = lista;
// 	proc* anterior = NULL;
// 	proc* aux = *lista;		
// 	if (!*lista) {
// 		printf("Lista vazia\n");
// 		exit(1);
// 	} else {
// 		// Percorre a lista até encontrar o processo
// 		while(*percorrer != NULL && (*percorrer)->id != id){
// 			anterior = *percorrer;
// 			*percorrer = (*percorrer)->proximo;
// 		}
// 		// Se não ouver nenhum anterior é porque o novo processo tem chegada menor que o primeiro
// 		// elemento e deve ser inserido no inicio da lista
// 		if (anterior == NULL) {
// 			aux = *percorrer;			
// 			*lista = aux->proximo;
// 		} else {
// 			if (*percorrer == NULL) {
// 				printf("Não encontrado\n");
// 				exit(1);
// 			} else {
// 				anterior->proximo = (*percorrer)->proximo;				
// 			}
// 			*lista = aux;
// 		}
// 	}
// }
// proc* menor_duracao(proc** lista) {
// 	if (*lista == NULL) {
// 		printf("Não há processos para execução\n");
// 		exit(1);
// 	}
// 	proc **percorrer = lista;
// 	proc *aux = *lista;
// 	proc *menor = *lista;
// 	while(*percorrer != NULL) {		
// 		if((*percorrer)->duracao < menor->duracao) {
// 			menor = (*percorrer);
// 		}
// 		*percorrer = (*percorrer)->proximo;		
// 	}
// 	*lista = aux;
// 	return menor;
// }
// void destroi_lista_circular(proc** lista) {
// 	proc* aux = (*lista);
// 	proc* remover;	
// 	while (aux->proximo != (*lista)) {		
// 		aux = aux->proximo;		
// 	}
// 	free(aux);
// }
lista* novo_processo(char id, int chegada, int duracao){
	lista* no_lista = malloc(sizeof(lista));
	if(no_lista == NULL) {
		printf("Falha ao alocar memória para novo nó da lista\n");
		exit(1);
	}
	proc* novo = malloc(sizeof(proc));
	if (novo == NULL) {
		printf("Falha ao alocar memória para o processo\n");
		exit(1);
	}
	novo->id = id;
	novo->chegada = chegada;
	novo->duracao = duracao;
	novo->ciclos = 0;	
	
	no_lista->proximo = NULL;
	no_lista->processo = novo;
	
	return no_lista;
}
// void insere_ordenado_chegada_circular(proc **lista, char id, int chegada, int duracao){	
// 	proc* novo = novo_processo(id, chegada, duracao);
// 	proc* anterior = NULL;
// 	if ((*lista) == NULL) {
// 		*lista = novo;
// 		novo->proximo = novo;
// 	} else {
// 		proc* aux = (*lista);
// 		while(aux->proximo != (*lista) && aux->chegada < novo->chegada){
// 			anterior = aux;
// 			aux = aux->proximo;
// 		}
// 		if (anterior == NULL) {
// 			if (novo->chegada > aux->chegada) {
// 				aux->proximo = novo;
// 				novo->proximo = aux;
// 			} else {
// 				(*lista) = novo;
// 				novo->proximo = aux;
// 				aux->proximo = novo;				
// 			}
// 		} else {
// 			aux->proximo = novo;
// 			novo->proximo = (*lista);
// 		}
// 	}	
// }
// int restam_processos(proc** lista) {
// 	int restam = 0;
// 	proc* inicio = *lista;
// 	proc** percorrer = lista;			
// 	while(*percorrer != NULL && (*percorrer)->proximo != inicio) {
// 		if ((*percorrer)->duracao > 0) {
// 			restam = 1;
// 		}		
// 		*percorrer = (*percorrer)->proximo;
// 	}
// 	*lista = inicio;
// 	return restam;
// }
// proc* busca_processo_ciclo(proc** processos, int ciclo_atual) {
// 	proc** percorrer = processos;
// 	proc* inicio = *processos;
// 	proc* processo = NULL;	

// 	while(*percorrer != NULL) {
// 		if ((*percorrer)->chegada == ciclo_atual) {
// 			if (processo != NULL) {
// 				if((*percorrer)->duracao < processo->duracao) {
// 					processo = (*percorrer);
// 				} else {
// 					*percorrer = (*percorrer)->proximo;
// 					continue;			
// 				}
// 			}
// 			processo = (*percorrer);
// 		}
// 		*percorrer = (*percorrer)->proximo;
// 	}
// 	if (processo == NULL) {
// 		processo = inicio;
// 		*percorrer = inicio->proximo;		
// 		while(*percorrer != NULL) {
// 			if ((*percorrer)->duracao < processo->duracao) {
// 				processo = *percorrer;
// 			}
// 			*percorrer = (*percorrer)->proximo;
// 		}
// 	}
// 	*processos = inicio;
// 	return processo;
// }
// void encontra_processo_ciclo(proc** fila, proc** lista, int ciclo){
// 	proc* aux = *lista;
// 	printf("fila 1: %p\n", fila);
// 	while (aux != NULL) {
// 		if(aux->chegada == ciclo){
// 			insere_final(fila,aux);
// 		}
// 		aux = aux->proximo;
// 	}
// }
// void insere_final(proc** fila, proc* processo) {
// 	proc* aux = (*fila);
// 	proc* inserir = processo;
// 	if (vazia(fila)){
// 		(*fila) = inserir;
// 		printf("processo: %c\n", inserir->proximo->id);
// 		getchar();
// 	} else {
// 		while(aux->proximo != NULL){
// 			printf("processo: %c\n", inserir->proximo->id);
// 			getchar();
// 			aux = aux->proximo;
// 		}
// 		aux->proximo = inserir;
// 	}
// }
// void pop(proc** inicio) {	
// 	proc* aux = *inicio;
// 	*inicio = aux->proximo;	
// 	free(aux);
// }
// proc* cria_fila() {
// 	proc* fila = malloc(sizeof(proc));
// 	fila->id = '~';
// 	fila->proximo = NULL;
// 	fila->duracao = -1;
// 	fila->chegada = -1;
// 	return fila;
// }