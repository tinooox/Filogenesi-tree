
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
