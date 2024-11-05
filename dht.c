#include "dht.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

nodo_dht *pilha_nodo[32] ;
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

void rouba_chaves(nodo_dht *nodo) {
    nodo_dht *aux = nodo->next ;
    for(int i = 0; i<aux->top;){
        if(aux->keys[i] <= nodo->N){
            if(aux == RING && aux->keys[i] <= aux-> N){
                i++ ;
                continue ;
            }
            nodo->keys[nodo->top] = aux->keys[i] ;
            aux->keys[i] = aux->keys[aux->top - 1] ;
            aux->top--;
            nodo->top++;
        } else i++ ;
    }

}

void entra_node(int n) {
    nodo_dht *nodo = cria_nodo(n) ;
    insere_nodo(nodo) ;
    if(n > M) M = n ;

    fix_lookup_tables() ;
    rouba_chaves(nodo) ;

    print_ring() ;
}

void sai_node(int node) {
    nodo_dht *it = RING ;
    while(it->N != node) it = it->next ;
    nodo_dht *aux = it->next ;
    for(int i = 0; i<it->top; i++){
        aux->keys[aux->top++] = it->keys[i] ;
    }
    it->next->prev = it->prev ;
    it->prev->next = it->next ;
    if(RING == it) RING = it->next ;
    fix_lookup_tables() ;
    print_ring() ;
}


void insere_key(int node, int key) {
    nodo_dht *it = RING ;
    while(it->N != node) it = it->next ;

    while(it->N < key) {
        int idx ;

        if(key > M) {
            idx = ceil(log2(M)) - 1 ;
        } else idx = ceil(log2(key - it->N)) ;

        if(it->lookupT[idx] == RING) {
            it = RING ;
            break ;
        }
        it = it->lookupT[idx] ;
    }
    it->keys[it->top] = key ;
    it->top++ ;

    print_ring() ;
}

void lookup_key(int ts, int node, int key) {
    int t = 0;

    nodo_dht *it = RING ;
    while(it->N != node) it = it->next ;

    do {
        pilha_nodo[t] = it ;
        t ++ ;
        int idx ;
        if(key > M){
            idx = ceil(log2(M)) - 1 ;
        } else idx = ceil(log2(key - it->N)) ;

        if(it->lookupT[idx] == RING) {
            it = RING ;
            break ;
        }
        it = it->lookupT[idx] ;
    } while(it->N < key) ;

    printf("%d L %d {", ts, key) ;
    for(int i = 0; i<t; i++){
        printf("%d", pilha_nodo[i]->N) ;
        if(i < i-1) printf(",") ;
    }
    printf("}\n") ;
}
