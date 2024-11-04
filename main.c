#include <stdio.h>
//#include "dht.h"

int main(){

    int ts, node, key ;
    char op ;

    scanf("%d", &ts) ;
    while(ts > 0) {
        scanf(" %c ", &op) ;
        switch (op){
        case 'E':
            scanf("%d", &node) ;
            printf("Operação entrada de nó %d\n", node) ;
            break ;
        case 'S':
            scanf("%d", &node) ;
            printf("Operação saída de nó %d\n", node) ;
            break ;
        case 'L':
            scanf("%d %d", &node, &key) ;
            printf("Operação lookup de %d de nó %d\n", key, node) ;
            break ;
        case 'I':
            scanf("%d %d", &node, &key) ;
            printf("Operação inclusão de %d de nó %d\n", key, node) ;
            break ;
        }
        scanf("%d", &ts) ;
    }

    return 0 ;
}
