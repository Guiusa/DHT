#include "dht.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

nodo_dht *pilha_nodo[1024] ;
nodo_dht *RING = NULL;
int M = 1 ;
int Mp = 2 ;
int Maior = 0 ;

void fix_lookup_tables() {
    nodo_dht *it = RING ;
    do {
        nodo_dht *aux = it->next ;
        for(int i = 0; i<M; i++){
            int fac = it->N + (int) pow(2, i) ;
            while(fac > aux->N){
                aux = aux->next ;
                if(aux == RING) fac -= Mp ;
            }
            it->lookupT[i] = aux ;
        }
        it = it->next ;
    }   while (it!=RING) ;
}

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
        for(int i = 0; i<M; i++){
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
}


void insere_key(int node, int key) {
    nodo_dht *it = RING ;

    while(key > it->N){
        it = it->next ;
        if(it == RING) break ;
    }

    it->keys[it->top] = key ;
    it->top++ ;

}

void print_pilha(int t, int ts, int key) {
    printf("%d L %d {", ts, key) ;
    for(int i = 0; i<t; i++){
        printf("%d", pilha_nodo[i]->N) ;
        if(i < t-1) printf(",") ;
    }
    printf("}\n") ;

    for(int i = 0; i<t; i++){
        printf("%d T %d {", ts, pilha_nodo[i]->N) ;
        for(int j = 0; j<M; j++){
            printf("%d", pilha_nodo[i]->lookupT[j]->N) ;
            if(j < M-1) printf(",") ;
        }
        printf("}\n") ;
    }

}

void entra_node(int n) {
    nodo_dht *nodo = cria_nodo(n) ;
    if(n > Maior) Maior = n ;
    int nm = (int) ceil(log2(n)) ;
    if(nm > M){
        M = nm ;
        Mp = 1 << M ;
    }
    insere_nodo(nodo) ;
    fix_lookup_tables() ;
    rouba_chaves(nodo) ;
}

void lookup_key(int ts, int node, int key) {
    int t = 0 ;
    nodo_dht *it = RING;
    for(; it->N != node; it=it->next) ;

    if(key > M){
        int k1 = M ;
        while(it != RING) {
            pilha_nodo[t++] = it ;
            int i = floor(log2(Mp - it->N));
            it = it->lookupT[i] ;
        }
        pilha_nodo[t++] = it ;
        print_pilha(t, ts, key) ;
        return ;
    }

}
