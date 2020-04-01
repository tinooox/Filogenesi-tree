#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct nodo con etichetta, peso dell'arco entrante e puntatore al nodo successivo nella lista
typedef struct nodo {
        char etichetta_nodo[50];
        struct nodo *next;
        int peso_arco;
    } nodo;

/*struct che rappresenta l'albero, formato da un'array di puntatori alle liste di adiacenza dei nodi e il numero dei nodi
primo elemento della lista, è il proprietario della lista*/
typedef struct albero {
        int n;
        nodo **liste;
    } albero;

/*costruzione lista di adiacenza(inversa).inserisce ill'inizio della lista *primo un nuovo nodo con etichetta e peso in ingresso
e restituisce l'indirizzo del nuovo primo elemento della lista (usiamo una pila, LIFO)*/
nodo *impila(nodo *primo,char etichetta_nodo[50],int peso_arco){
    nodo *x;
    x=malloc(sizeof(nodo));
    strcpy(x->etichetta_nodo,etichetta_nodo);
    x->peso_arco=peso_arco;
    x->next=primo;
    primo=x;
    return(primo);
}

/*inserimento elementi lista di adiacenza di un nodo,inserisce il nodo stesso e poi inserisci i figli in ingresso dall'utente
restituisce il puntatore al primo elemento della lista*/
nodo *leggi_lista(void){
    int n,i;
    char etichetta_nodo[50];
    int peso_arco;
    nodo *primo=NULL;

    printf("\nLISTA DI ADIACENZA DEL NODO (inserisci etichetta): ");
    scanf("%s",etichetta_nodo);
    primo=impila(primo,etichetta_nodo,(int)NULL);

    printf("Quanti elementi ci sono nella lista di %s? ",etichetta_nodo);
    scanf("%d",&n);

    printf("inserisci %d figlio/i \n",n);
    for(i=0;i<n;i++){
        printf("\nFIGLIO %d: ",i+1);
        printf("\ninserisci etichetta: ");
        scanf("%s",etichetta_nodo);
        printf("inserisci peso dell'arco entrante: ");
        scanf("%d",&peso_arco);
        primo=impila(primo,etichetta_nodo,peso_arco);
    }
    return(primo);
}

//stampa a video la lista di adiacenza del nodo in ingresso, scorre tutta la lista dal nodo in ingresso
void stampa_lista(nodo *n){
    while(n!=NULL){
        printf("%s(peso=%d) -> ",n->etichetta_nodo,n->peso_arco);
        n=n->next;
    }
    printf("NULL\n");
}

//stampa tutte le liste di adiacenza
void stampa_albero(albero a){
    int i;
    for(i=1;i<=a.n;i++){
        printf("%s: ",a.liste[i]->etichetta_nodo);
        stampa_lista(a.liste[i]->next);
    }
}

/*inverte la lista di adiacenza, mettendola nell'ordine corretta,
prende in ingresso l'indirizzo al primo elemento, la inverte e restituisce l'indirizzo al nuovo primo elemennto(ex ultimo)*/
nodo *inverti_lista(nodo *p) {
  nodo *q = NULL;
  nodo *z;
  if (p != NULL && p->next != NULL) {
    q = inverti_lista(p->next);
    z=p->next;
    z->next = p;
    p->next = NULL;
  } else {
    q = p;
  }
  return(q);
}

//costruzione dell'albero, salva in numero di nodi, alloca lo spazio per i puntatori alle liste di adiacenza, restituisce l'albero
void crea_albero(albero *a){
    int n_nodi,i;
    nodo *z;
    printf("COSTRUZIONE ALBERO\n");
    printf("numero nodi: ");
    scanf("%d",&n_nodi);
    a->n=n_nodi;
    a->liste = malloc((n_nodi+1)*sizeof(nodo *));
    for(i=1;i<=n_nodi;i++){
        z=leggi_lista();
        a->liste[i]= inverti_lista(z);
    }
}

/*restituisce le etichette dei nodi foglie, controllando quali nodi hanno la lista composta da 1 solo elemento(il nodo stesso),
stampa a video l'etichetta*/
void foglie(nodo *n){
    int c=0;
    nodo *n1=n;
    while(n!=NULL){
        n=n->next;
        c++;
    }
    if(c==1)
        printf("%s\t",n1->etichetta_nodo);
}

//inserire lista di adiacenza del nuovo nodo,alloca uno spazio in più nella lista dei puntatori e la aggiunge alla lista e richiama inverti
void aggiungi_lista(albero *a, nodo *x){
    nodo *z=NULL;
    a->liste =realloc(a->liste,(++a->n)*sizeof(nodo *));
    z=impila(z,x->etichetta_nodo,(int)NULL);
    a->liste[a->n]=inverti_lista(z);
}

/*aggiunge un nuovo nodo, collegato ad una foglia
stampa la lista delle foglie, fa scegliere all'utente, fa inserire nuova etichetta e peso, alloca lo spazio e lo aggiunge
nella lista del padre*/
void aggiunta_nodo(albero *a){
    int i,p;
    char s[50];
    char e[50];
    nodo *x;
    printf("\nLISTA FOGLIE: \n");
    for(i=1;i<=a->n;i++){
        foglie(a->liste[i]);
    }
    printf ("\na quale foglia vuoi aggiungere un nodo? ");
    scanf("%s",s);

    for(i=1;i<=a->n;i++){
        if((strcmp(s,a->liste[i]->etichetta_nodo))==0){
            x=a->liste[i];
            printf("etichetta nuovo nodo: ");
            scanf("%s",e);
            printf("peso nuovo nodo: ");
            scanf("%d",&p);
            x->next=malloc(sizeof(nodo));
            x=x->next;
            strcpy(x->etichetta_nodo,e);
            x->peso_arco=p;
            x->next=NULL;

            aggiungi_lista(a,x);
        }
    }

}

//controlla se il nodo in ingresso è una foglia, restituendo il numero di elementi della sua lista di adiacenza
int controllo_foglia(nodo *n){
    int c=0;
    while(n!=NULL){
        n=n->next;
        c++;
    }
    return c;
}

/*cancellazione di una foglia
stampa le foglie e la fa scegliere, controlla che il nodo inserito sia una foglia(con CONT).
elimina la lista di adiacenza del nodo e poi elimina il nodo dalla lista del padre*/
void cancella_nodo(albero *a){
    int i,j,cont=0;
    int c=0;
    nodo *x;
    nodo *prev;
    char s[50];
    printf("\nLISTA FOGLIE: \n");
    for(i=1;i<=a->n;i++){
        foglie(a->liste[i]);
    }
    printf ("\nQuale foglia vuoi eliminare? ");
    scanf("%s",s);

    for(i=1;i<=a->n;i++){
        c=0;
        c=controllo_foglia(a->liste[i]);                          //elimina lista di adiacenza del nodo
        if(((strcmp(s,a->liste[i]->etichetta_nodo))==0)&&(c==1)){
            cont=1;
            for(j=i;j<=a->n;j++){
                a->liste[j]=a->liste[j+1];
            }
            free(a->liste[j]);
            a->n=a->n-1;
        }
    }

    if(cont==0){
        printf("NON HAI INSERITO UNA FOGLIA\n");
        return;
    }

    for(i=1;i<=a->n;i++){
    x=a->liste[i];
        while(x!=NULL&&((strcmp(s,x->etichetta_nodo)!=0))){      //eliminare nodo dalla lista del padre
            prev=x;
            x=x->next;
        }
        if(x==NULL){}
        else{
        prev->next=x->next;
        free(x);}
    }
}

/*modifica di una foglia
stampa la lista delle foglie, controlla se è una foglia(con CONT)
modifica la propria lista e modifica la lista del padre*/
void modifica_nodo(albero *a){
    int i,c=0,cont=0,peso;
    nodo *x;
    char s[50];
    char vecchia[50];
    printf("\nLISTA FOGLIE: \n");
    for(i=1;i<=a->n;i++){
        foglie(a->liste[i]);
    }
    printf ("\nQuale foglia vuoi modificare? ");
    scanf("%s",s);

    for(i=1;i<=a->n;i++){
        c=0;
        c=controllo_foglia(a->liste[i]);                          //modifica lista di adiacenza del nodo
        if(((strcmp(s,a->liste[i]->etichetta_nodo))==0)&&(c==1)){
            cont=1;
            printf("Inserisci nuova etichetta: ");
            scanf("%s",s);
            printf("Inserisci nuovo peso: ");
            scanf("%d",&peso);
            strcpy(vecchia,a->liste[i]->etichetta_nodo);
            strcpy(a->liste[i]->etichetta_nodo,s);
        }
    }

    if(cont==0){
        printf("NON HAI INSERITO UNA FOGLIA\n");
        return;
    }

    for(i=1;i<=a->n;i++){
    x=a->liste[i];
        while(x!=NULL&&((strcmp(vecchia,x->etichetta_nodo)!=0))){      //modifica nodo dalla lista del padre
            x=x->next;
        }
        if(x==NULL){}
        else{
        strcpy(x->etichetta_nodo,s);
        x->peso_arco=peso;    }
    }
}

//creazione matrice associata (matrice dei pesi dei cammini tra foglie), utilizzando Floyd-Warshall
void crea_matrice(albero *a){
    nodo *x;
    char etichette[a->n+1][50];
    int matrice[a->n+1][a->n+1];
    int i,j,c=0,h,dij,dih,dhj;

    for(i=1;i<=a->n;i++){                                       //salvo le etichette di tutti i nodi ui un array, per avere il
       strcpy(etichette[i],a->liste[i]->etichetta_nodo);        //riferimento tra indici della lista ed etichetta
    }

    for(i=0;i<=a->n;i++){                                         //inizializza la matrice a 100, e la diagonale a 0
       for(j=0;j<=a->n;j++){                                      //anche riga[0] e colonna[0] a 0
            matrice[i][j]=100;
            if((i==0)||(j==0))
                matrice[i][j]=0;
            if(i==j)
                matrice[i][j]=0;
       }
    }

    for(i=1;i<=a->n;i++){                                           //MATRICE DI ADIACENZA
           x=a->liste[i];
           while(x!=NULL){                                          //scorro nodo per nodo le liste di adiacenza, salvandomi l'indice del padre
                for(j=1;j<=a->n;j++){                                  //metto nella matrice il peso dell'arco
                    if(strcmp(x->etichetta_nodo,etichette[j])==0)
                        c=j;
                }
                matrice[i][c]=x->peso_arco;
                matrice[c][i]=x->peso_arco;
                x=x->next;
           }
    }

    //FLOYD-WARSHALL
    for(h=1;h<=a->n;h++){
        for(i=1;i<=a->n;i++){
            for(j=1;j<=a->n;j++){
                dij=matrice[i][j];
                dih=matrice[i][h];
                dhj=matrice[h][j];
                if(dij>dih+dhj){
                    matrice[i][j]=matrice[i][h]+matrice[h][j];
                    }
            }
        }
    }

    int cont=0;

    for(i=1;i<=a->n;i++){                                           //mette tutta la matrice di adiacenza a -1, tranne le righe e colonne foglie
        if(controllo_foglia(a->liste[i])!=1){
            for(j=1;j<=a->n;j++){
                matrice[i][j]=-1;
                matrice[j][i]=-1;
                }
            cont++;                                                    //conta quanti ne ho "eliminati", quindi facendo tot_nodi-cont=num_foglie
        }
    }

    for(i = 1; i<= a->n; i++){                                          //setto a NULL tutte le non foglie nell'array delle etichette
            if(controllo_foglia(a->liste[i])!=1)
                strcpy(etichette[i], "null");
        }

    int b=(a->n)-cont;    //numero foglie
    int dist[b+1][b+1];     //matrice delle foglie
    int z=0,t=0;
    t=((a->n)-cont)*((a->n)-cont);  //array per salvare i cammini tra le foglie
    int val[t];         //array di supporto

    for(i=1;i<=b;i++){              //inizializza tutta la matrice a -1
       for(j=1;j<=b;j++){
            dist[i][j]=-1;
       }
    }

    for(i=1;i<=a->n;i++){               //salvo nell'array di supporto i cammini tra le foglie, prendendoli dalla matrice di adiacenza
       for(j=1;j<=a->n;j++){
            if(matrice[i][j]!=-1){
                val[z]=matrice[i][j];
                z++;
            }
        }
    }

    z=0;

    for(i=1;i<=b;i++){                      //metto nella matrice associata i valori presi dall'array
       for(j=1;j<=b;j++){
                dist[i][j]=val[z];
                z++;
        }
    }

    printf("\n");

    char fogliea[b+1][50];
    int g = 1;



    for(i = 1; i<= a->n; i++){                      //stampo etichette
        if(strcmp(etichette[i], "null")!=0){
            strcpy(fogliea[g], etichette[i]);
            g++;
        }
    }
    for(i = 1; i<=b; i++)
        printf("\t%s", fogliea[i]);
    printf("\n\n");

    for(i=1;i<=b;i++){
       printf(" %s\t", fogliea[i]);                 //stampo matrice associata (anche le etichette delle righe)
       for(j=1;j<=b;j++){
            printf("%d\t",dist[i][j]);
       }
       printf("\n");
    }
}

void main()
{
    int risposta=0;
    albero a;
    do{
    printf("\n\nFILOGENESI\n1-> Inserisci un albero\n2-> Stampa le liste di adiacenza\n3-> Aggiungi una foglia\n4-> Cancella una foglia\n");
    printf("5-> Modifica una foglia\n6-> Crea la matrice associata(cammini tra foglie)\n7-> ESCI\n");
    printf("\nEffettua la scelta(digitare numero): ");
    scanf("%d",&risposta);
    switch (risposta){
    case 1:     crea_albero(&a); break;
    case 2:     printf("\n\nLISTE DI ADIACENZA: \n"); stampa_albero(a); break;
    case 3:     aggiunta_nodo(&a); break;
    case 4:     cancella_nodo(&a); break;
    case 5:     modifica_nodo(&a); break;
    case 6:     crea_matrice(&a); break;
    case 7:     break;
    }
    }while(risposta!=7);
    return;

}
