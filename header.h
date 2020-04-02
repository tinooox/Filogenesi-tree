#ifndef FILOGENESI
#define FILOGENESI

typedef struct nodo {
        char etichetta_nodo[50];
        struct nodo *next;
        int peso_arco;
    } nodo;
    
typedef struct albero {
        int n;
        nodo **liste;
    } albero;
    
 
nodo *impila(nodo *primo,char etichetta_nodo[50],int peso_arco);

nodo *leggi_lista(void);

void stampa_lista(nodo *n);

void stampa_albero(albero a);

nodo *inverti_lista(nodo *p);

void crea_albero(albero *a);

void foglie(nodo *n);

void aggiungi_lista(albero *a, nodo *x);

void aggiunta_nodo(albero *a);

int controllo_foglia(nodo *n);

void cancella_nodo(albero *a);

void modifica_nodo(albero *a);

void crea_matrice(albero *a)

#endif
