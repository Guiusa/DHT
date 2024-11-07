#include <stdio.h>
#include "dht.h"

int main(){

    int ts, node, key ;
    char op, trash;

    scanf("%d", &ts) ;

    while(scanf(" %c ", &op) == 1) {
        switch (op){
        case 'E':
            scanf("%d %c", &node, &trash) ;
#ifdef DEBUG
            printf("%d %c %d -\n", ts, op, node) ;
#endif
            entra_node(node) ;
#ifdef DEBUG
            print_ring() ;
#endif
            break ;
        case 'S':
            scanf("%d %c", &node, &trash) ;
#ifdef DEBUG
            printf("%d %c %d -\n", ts, op, node) ;
#endif
            sai_node(node) ;
#ifdef DEBUG
            print_ring() ;
#endif
            break ;
        case 'L':
            scanf("%d %d", &node, &key) ;
#ifdef DEBUG
            printf("%d %c %d %d\n", ts, op, node, key) ;
#endif
            lookup_key(ts, node, key) ;
#ifdef DEBUG
            print_ring() ;
#endif
            break ;
        case 'I':
            scanf("%d %d", &node, &key) ;
#ifdef DEBUG
            printf("%d %c %d %d\n", ts, op, node, key) ;
#endif
            insere_key(node, key) ;
#ifdef DEBUG
            print_ring() ;
#endif
            break ;
        }
        scanf("%d", &ts) ;
    }

    return 0 ;
}
