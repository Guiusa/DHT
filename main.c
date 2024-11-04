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
            break ;
        case 'S':
            scanf("%d %c", &node, &trash) ;
            sai_node() ;
            break ;
        case 'L':
            scanf("%d %d", &node, &key) ;
            lookup_key() ;
            break ;
        case 'I':
            scanf("%d %d", &node, &key) ;
            insere_key() ;
            break ;
        }
        scanf("%d", &ts) ;
    }

    return 0 ;
}
