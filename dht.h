#define KEYS_ALLOC_S 512

typedef struct nodo_dht {
    struct nodo_dht *next, *prev ;
    int N ;
    struct nodo_dht *lookupT[128] ;
    int* keys ;
    int top ;
} nodo_dht ;

void print_ring() ;
void entra_node(int n) ;
void sai_node(int n) ;
void lookup_key(int ts, int node, int key) ;
void insere_key(int node, int key) ;
