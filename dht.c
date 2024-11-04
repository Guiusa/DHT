#include "dht.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

nodo_dht *RING = NULL;
int M = 0 ;

nodo_dht *cria_nodo(int n) {
    nodo_dht *node = malloc(sizeof(nodo_dht)) ;
    node->N = n ;
    node->keys = malloc(KEYS_ALLOC_S * sizeof(nodo_dht)) ;
    node->top = 0 ;
    return node ;
}

void insere_nodo(nodo_dht *nodo) {
    if(RING == NULL) {
        RING = nodo ;
        nodo->prev = nodo ;
        nodo->next = nodo ;
        return ;
    }

    if (nodo->N < RING->N) {
        nodo->prev = RING->prev ;
        RING->prev = nodo ;
        nodo->next = RING ;
        nodo->prev->next = nodo ;
        RING = nodo ;
        return ;
    }

    nodo_dht *aux = RING ;
    do {
        if (aux->N > nodo->N) break ;
        aux = aux->next ;
    } while (aux != RING) ;

    nodo->next = aux ;
    nodo->prev = aux->prev ;
    aux->prev->next = nodo ;
    aux->prev = nodo ;
}

void print_ring() {
    nodo_dht *it = RING ;
    do {
        printf("[%d]\n", it->N) ;
        printf("[ ") ;
        for(int i = 0; i<ceil(log2((double) M)); i++){
            printf("%d:%d ", (int) pow(2, i), it->lookupT[i]->N) ;
        }
        printf("]\n") ;

        printf("{ ") ;
        for(int i = 0; i<it->top; i++)
            printf("%d ", it->keys[i]) ;
        printf("}\n") ;

        it = it->next ;
    } while (it != RING) ;
    printf("\n\n") ;
}

void fix_lookup_tables() {
    nodo_dht *it = RING ;
    do {
        nodo_dht *it_aux = it->next ;
        for(int i = 0; i<ceil(log2((double) M)); i++){
            if(it_aux == RING){
                it->lookupT[i] = RING ;
                continue ;
            }
            while(it->N + (int) pow(2, i) > it_aux->N && it_aux != RING) it_aux = it_aux->next ;
            it->lookupT[i] = it_aux ;
        }

        it = it->next ;
    } while (it != RING) ;
}

void entra_node(int n) {
    nodo_dht *nodo = cria_nodo(n) ;
    insere_nodo(nodo) ;
    if(n > M) M = n ;

    fix_lookup_tables() ;

    print_ring() ;
}

void sai_node() {
    printf("Sai nodo\n") ;
}

void lookup_key() {
    printf("Lookup de chave\n") ;
}

void insere_key(int node, int key) {
    nodo_dht *it = RING ;
    while(it->N != node) it = it->next ;
//    nodo_dht *aux = it ;

    while(it->N < key) {
        int idx ;

        if(key > M) {
            idx = ceil(log2(M)) - 1 ;
        } else idx = ceil(log2(key - it->N)) ;

        if(it->lookupT[idx] == RING) {
            printf("VAI INSERIR NO RING\n") ;
            it = RING ;
            break ;
        }
        it = it->lookupT[idx] ;
    }
    it->keys[it->top] = key ;
    it->top++ ;

    print_ring() ;
}
