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
            entra_node(node) ;
            printf("%d %c %d -\n", ts, op, node) ;
            //print_ring() ;
            break ;
        case 'S':
            scanf("%d %c", &node, &trash) ;
            sai_node(node) ;
            printf("%d %c %d -\n", ts, op, node) ;
            //print_ring() ;
            break ;
        case 'L':
            scanf("%d %d", &node, &key) ;
            lookup_key(ts, node, key) ;
            printf("%d %c %d %d\n", ts, op, node, key) ;
            //print_ring() ;
            break ;
        case 'I':
            scanf("%d %d", &node, &key) ;
            insere_key(node, key) ;
            printf("%d %c %d %d\n", ts, op, node, key) ;
            //print_ring() ;
            break ;
        }
        scanf("%d", &ts) ;
    }

    return 0 ;
}
