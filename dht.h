#define KEYS_ALLOC_S 500

typedef struct nodo_dht {
    struct nodo_dht *next, *prev ;
    int N ;
    struct nodo_dht *lookupT[128] ;
    int* keys ;
} nodo_dht ;

void print_ring() ;
void entra_node(int n) ;
void sai_node() ;
void lookup_key() ;
void insere_key() ;
