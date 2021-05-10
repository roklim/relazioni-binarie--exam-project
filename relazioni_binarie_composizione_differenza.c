/* inclusione delle librerie */
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 80

int acquisisci_carattere_valido(char *);

int * alloc_mem_insieme(int );

int controllo_duplicato(int *,
					    int ,
					    int );

int trova_max(int *,
              int );

void scambia(int *,
             int );


void stampa_insieme(int *,
				    int );

/* tipo di dato che rappresenta un
    elemento della relazione binaria */
typedef struct {
                int x,  /* 1' valore coppia */
                    y;  /* 2' valore coppia */
               } elem_relazione_t;

elem_relazione_t *acquisisci_relazione(int *,
                                       int ,
                                       int *);

int esiste_in_insieme(int *,
                      int ,
                      int );
int esiste_in_relazione(elem_relazione_t *,
                        int ,
                        int ,
                        int );

void stampa_relazione(elem_relazione_t *,
                      int );

void calcola_diff_simmetrica(elem_relazione_t *,
                             int ,
                             elem_relazione_t *,
                             int );
void calcola_composizione(elem_relazione_t *R1, /* input: prima relazione */
                          int num_elem_R1,        /* input: numero elementi prima relazione */
                          elem_relazione_t *R2, /* input: seconda relazione */
                          int num_elem_R2
                         );

/* definizione della funzione main */
int main()
{
    int *insieme;                /* input: puntatore a un vettore di naturali, l'insieme di partenza */
    int tot;                     /* input: numero totale di elementi da cui e' composto l'insieme di partenza */
    elem_relazione_t *R1 = NULL, /* input: puntatore ad un vettore di coppie che rappresenta la prima relazione */
                     *R2 = NULL; /* input: puntatore ad un vettore di coppie che rappresenta la seconda relazione */
    
    int i;                       /* lavoro: valore di inizializione cicli */
    int elem_inserito;           /* lavoro: elemento dell'insieme acquisito dall'utente */
    int duplicato;               /* lavoro: controllo se un valore dell'insieme è gia stato inserito */
    int num_elem_R1;             /* lavoro: numero elementi relazione 1 */
    int num_elem_R2;             /* lavoro: numero elementi relazione 2 */

    printf("\n****** OPERAZIONI TRA RELAZIONI BINARIE *******\n");

    /* ottenere totale elementi da cui e' composto l'insieme di partenza */
    tot = acquisisci_carattere_valido("\nQuanti elementi vuoi inserire nell' insieme?\n");

    /* allocazione di memoria dell'insieme di partenza */
    insieme = alloc_mem_insieme(tot);

    /* se l'allocazione e' andata a buon fine */
    if(insieme != NULL)
    {
        printf("\nSi prega di inserire massimo ( %d ) numeri naturali: ",
               tot);
        printf("\n");
        /* rihiedere inserimento elementi appartenenti all'insieme di partenza*/
        for(i = 0;
            i < tot;
            i++)
        {
            do
            {
                char prompt[MAX_SIZE];
                sprintf(prompt,
                        "\nElemento [%d]: ",
                        (i+1));
                elem_inserito = acquisisci_carattere_valido(prompt);
                duplicato = controllo_duplicato(insieme,
                                                i,
                                                elem_inserito);
                if(duplicato)
                    printf("\nAttenzione! (%d) e' gia stato inserito!!!\n",
                           elem_inserito);

            }while(duplicato == 1);

            /* salvare l'input nell'array quando non e' duplicato */
            insieme[i] = elem_inserito;
        }
        /* ordinare l'insieme inserito dall'utente */
        scambia(insieme, tot);
        /* stampare i numeri inseriti dall' utente */
        printf("\n*************** INSIEME ACQUISITO **************\n");
        stampa_insieme(insieme,
                       tot);
        printf("************************************************\n");
        /* acquisire le relazioni */
        R1 = acquisisci_relazione(insieme,
                                  tot,
                                  &num_elem_R1);
        printf("\n[relazione 1 inserita correttamente!]\n");


        R2 = acquisisci_relazione(insieme,
                                  tot,
                                  &num_elem_R2);
        printf("\n[relazione 2 inserita correttamente!]\n\n");
        printf("************************************************\n");
        
        /* stampare le relazioni inserite */
        printf("\n[relazione 1] = ");
        stampa_relazione(R1,
                 num_elem_R1);
        printf("\n[relazione 2] = ");
        stampa_relazione(R2,
                 num_elem_R2);
        printf("\n[differenza simmetrica] = ");
        calcola_diff_simmetrica(R1,
                                num_elem_R1,
                                R2,
                                num_elem_R2);
        printf("\n[composizione] = ");
        calcola_composizione(R1,
                             num_elem_R1,
                             R2,
                             num_elem_R2);

        /* liberare memoria precedentemente allocata */
        free(R1);
        free(R2);


    }else
    {
        /* allocazione di memoria fallita */
        printf("Allocazione di memoria dell'insieme fallita!!!\n");
    }
    /* liberare memoria precedentemente allocata */
    free(insieme);

    return 0;

}


elem_relazione_t *acquisisci_relazione(int *insieme,          /* input: insieme di partenza */
                                       int tot,                /* lavoro: numero elementi dell'insieme */
                                       int *num_elem_relazione)/* output: numero di elementi della relazione */
{
    int x;                              /* lavoro: variabile che rappresenta il primo valore della relazione */
    int y;                              /* lavoro: variabile che rappresenta il primo valore della relazione */
    int esito_lettura;                  /* lavoro: esito lettura della scanf */
    int esiste = 0;                     /* lavoro: variabile che indica la presenza di un duplicato  */
    int i = 0;                          /* lavoro: valore di inizializzazione cicli */
    elem_relazione_t *relazione = NULL; /* output: relazione acquisita (x,y) */
    char sing_plur;                     /* lavoro: carattere utilizzato per stampa sing. plur. */

    /* controllare se singolare o plurale */
    sing_plur = (tot == 1)? 'a' : 'e';

    /* ottenere le relazioni binarie dall'utente */
    printf("\nSi prega di scegliere tra i numeri sopra indicati al massimo (%d) "
           "coppi%c "
           "distint%c! \n",
           tot*tot,
           sing_plur,
           sing_plur);
    /* chiedere all'utente di quanti elementi e' composta la relazione */
    do
    {
        printf("Inserisci di quanti elementi e' composta la relazione: \n");
        esito_lettura = scanf("%d",
                              num_elem_relazione);
        printf("-------------------------------------------------------\n");
        if(esito_lettura !=1)
            printf("L'input deve essere un numero!!!\n");
        else if(*num_elem_relazione < 0)
            printf("L'input deve essere '>' o '=' a 0!!!\n");
        else if(*num_elem_relazione > (tot * tot))
            printf("Hai selezionato troppi elementi!!!\n");
        while(getchar() != '\n');
    }while(esito_lettura != 1 ||
           *num_elem_relazione < 0 ||
           *num_elem_relazione > (tot * tot));

    /* allocazione di memoria per la relazione */
    relazione = (elem_relazione_t *) calloc(*num_elem_relazione,
                                      sizeof(elem_relazione_t));
    /* se è andata a buon fine */
    if(relazione != NULL)
    {
        while(i < *num_elem_relazione)
        {
            /* richiedere l'inserimento delle coppie (x,y) */
            do
            {
                printf("Inserisci il primo elemento della %d coppia:",
                       (i+1));
                esito_lettura = scanf("%d",
                                      &x);
                printf("Inserisci il secondo elemento della %d coppia:",
                       (i+1));
                esito_lettura += scanf("%d",
                                       &y);
                printf("--------------------------------------------------\n");

                if(esito_lettura == 2)
                {
                    /* controllare se la coppia e' gia stata o puo essere inserita*/
                    esiste = esiste_in_insieme(insieme,
                                               tot,
                                               x) &&
                            esiste_in_insieme(insieme,
                                              tot,
                                              y);
                    if(!esiste)
                        printf("I o il valore inserito non e' presente nell'insieme di partenza!!!\n");

                }else
                    printf("Hai inserito caratteri non ammessi!!!\n");
                while(getchar() != '\n');

            }while(esito_lettura != 2 ||
                   !esiste);
            /* controllare nella relazione (con limite il numero di elementi inseriti) se
               la coppia non esiste. Se non esiste e' possibile inserire i due valori */
            if(!esiste_in_relazione(relazione,
                                    i,
                                    x,
                                    y))
            {
                relazione[i].x = x;
                relazione[i].y = y;
                i++;
            } else
                printf("La coppia inserita e' gia presente nella relazione!!!\n");
        }

    } else
    /* la relazione non ha elementi */
    *num_elem_relazione = 0;

    return (relazione);
}


/******************************************************/
/* Definizione della funzione per verificare tramite  */
/* l'algoritmo di ricerca binaria in un algoritmo     */
/* ordinato se un valore esiste o no restituendo      */
/******************************************************/
int esiste_in_insieme(int *insieme,          /* input: puntatore all'insieme */
                      int num_elem,          /* lavoro: numero elementi dell'insieme*/
                      int elem_inserito)     /* input: elemento da verificare */
{
    int primo_elem = 0;             /* lavoro: indice del primo elem. dell'insieme */
    int ultimo_elem = num_elem - 1; /* lavoro: indice dell'ultimo elem dell'insieme */
    int meta;                       /* lavoro: indice dell'elem a meta' insieme */
    int esiste = 0;                 /* output: valore che indica se l'elem. esiste gia */

    /* controllare se il valore inserito si trova nell'insieme */
    if(elem_inserito >= insieme[0] &&
       elem_inserito <= insieme[ultimo_elem])
    {
        /* controllare finche non si trova il primo elem e l'indice del primo elem
           non supera quello dell'ultimo */
        while(!esiste &&
              primo_elem <= ultimo_elem)
        {   /* assegnare l'indice che rappresenta meta vettore */
            meta = (primo_elem + ultimo_elem) / 2;
            /* controllare se l'elemento inserito si trova a meta vettore */
            esiste = (insieme[meta] == elem_inserito);
            /* controllare se l'elem inserito e piu grande della meta dell'insieme, in quel caso
               viene scartata la prima meta scambiando l'indice dell'elemento con il primo
               dopo la meta */
            if(insieme[meta] < elem_inserito)
                primo_elem = meta + 1;
            else
                ultimo_elem = meta - 1;
        }
    }
    return (esiste);
}

/****************************************************/
/* Definizione della funzione per                   */
/* ottenere un carattere valido dall'utente         */
/****************************************************/
int acquisisci_carattere_valido(char *prompt)
{
	int esito_lettura;    /* lavoro: condizione di validità */
	int num_elem_insieme; /* input: carattere digitato */

    /* richiedere all'utente l'inserimento degli elementi dell'insieme */
	do
    {
		printf("%s",prompt);
		esito_lettura = scanf("%d",
						      &num_elem_insieme);

		if(esito_lettura != 1 )
			printf("L'input deve essere un numero!!!\n");
		while(getchar() != '\n');
		if(esito_lettura && num_elem_insieme < 0)
		{
			printf("L'input deve essere '>' o '=' a 0!!!\n");
			esito_lettura = 0;
		}
    }while(!esito_lettura);

	return (num_elem_insieme);
}

/****************************************************/
/* Definizione della funzione per per l'allocazione */
/* dinamica di un array di valori interi            */
/****************************************************/

int *alloc_mem_insieme(int tot)      /* input: valori da allocare */
{
	int *insieme = NULL;           /* lavoro: puntatore ad un vettore di naturali */
    int i;                         /* lavoro: indice di accesso */

    insieme = (int*)malloc(sizeof(int)*tot);


    for(i = 0; i < tot; i++)
        insieme[i] = -1;

    return (insieme);
}

/**************************************************************/
/* Definizione della funzione per                             */
/* controllare la presenza di un duplicato intero nel vettore */
/**************************************************************/

    int controllo_duplicato(int *num,           /* input: puntatore ad un array di naturali */
                            int indice,         /* input: l'elemento da cui si inzia il confronto*/
                            int elem_inserito)  /* input: numero da verificare */
{
	int i;                 /* lavoro: indice di accesso */
	int trovato = 0;       /* lavoro/output: condizione di esistenza */

	for(i = indice; i >= 0 && !trovato; i--)
	    trovato = (num[i] == elem_inserito);

	return (trovato);
}

/*******************************************************/
/* Definizione della funzione per la stampa dell'array */
/*******************************************************/

void stampa_insieme(int *insieme,	  /* input: puntatore ad un vettore di naturali */
                    int size)         /* input: size del vettore */
{
	int i;             /* lavoro: indice di accesso */

    /* stampare array */
    printf("[ ");
	for(i = 0; i < size; i++)
		printf("'%d ",
               insieme[i]);
	printf("]\n");
}

/***************************************************************************/
/* Definizione della funzione per verificare se una coppia e' gia presente */
/* all'interno della relazione restituendo 1 se presente, altrimenti  0    */
/***************************************************************************/

int esiste_in_relazione(elem_relazione_t *relazione, /* input : puntatore al vettore che rappresenta la relazione */
                        int num_elem_relazione,      /* lavoro: numero di elementi della relazione */
                        int x,                       /* input : primo valore della coppia da confrontare */
                        int y)                       /* input : secondo valore della coppia daconfrontare */
{
    int esiste = 0, /* output: variabile che indica la presenza o meno della coppia nella relazione */
    i = 0;          /* lavoro: indice di accesso */

    /* eseguire l'iterazione fino a che si trova una coppia equivalente ai parametri passati
       o fino a che non termina il vettore */
    while (!esiste && i < num_elem_relazione)
    {
    esiste = relazione[i].x == x &&
    relazione[i].y == y;
    i++;
    }
    return (esiste);
}

/*************************************/
/* Definizione della funzione per    */
/* stampare una relazione binaria    */
/*************************************/
void stampa_relazione(elem_relazione_t *relazione, /* input : puntatore al vettore che rappresenta la relazione */
                      int num_elem_relazione)        /* lavoro: numero di elementi della relazione */
{
    int i;           /* lavoro: indice di accesso */

    printf("{");
    for (i = 0;
        (i < num_elem_relazione);
         i++)
    {
        printf("(%d, %d)",
        relazione[i].x,
        relazione[i].y);
        if ((i + 1) != num_elem_relazione)
            printf(", ");
    }
    printf("} \n");
}

/**************************************************************/
/* Definizione della funzione per trovare il valore           */
/* massimo tra gli elementi dell'insieme inserito             */
/**************************************************************/
int trova_max(int *insieme,          /* input: puntatore ad un vettore di naturali */
              int num_elem_insieme)  /* input: numero elementi insieme da controllare */
{
    int max = 0,     /* lavoro/output: valore massimo del vettore */
        i;           /* lavoro: indice di accesso */

    for (i = 1; i <= num_elem_insieme; i++)
    {
        if (insieme[i] > insieme[max])
        {
            max = i;
        }
    }
    return(max);
}

/***************************************************************/
/* Definizione della funzione che dopo aver ordinato l'insieme */
/* scambia l'insieme non ordinato con quello ordinato          */
/***************************************************************/
void scambia(int *insieme,         /* input: puntatore ad un vettore di naturali */
             int num_elem_insieme) /* input: numero elementi insieme da controllare */
{
    int  temp,
         big,
         i;       /* lavoro: indice di accesso */
    for (i = num_elem_insieme - 1; i >= 1; i--)
    {
        big = trova_max(insieme, i);
        temp = insieme[big];
        insieme[big] = insieme[i];
        insieme[i] = temp;
    }
}

/***************************************************************/
/* Definizione della funzione per calcolare la composizione    */
/***************************************************************/
void calcola_composizione(elem_relazione_t *R1, /* input: prima relazione */
                          int num_elem_R1,        /* input: numero elementi prima relazione */
                          elem_relazione_t *R2, /* input: seconda relazione */
                          int num_elem_R2)        /* input: num. elementi seconda relazione */
{
    /* lavoro/output: risultato composizione tra relazioni */
    int i=0;                            /* lavoro: contatore per assegnazioni valori composizione */
    int j=0;                                /* lavoro: contatore per assegnazioni valori composizione */
    int x;                                /* lavoro: primo valore della coppia nella rel 1 (x,y) */
    elem_relazione_t *composizione = NULL;                                /* lavoro: secondo valore della coppia nella rel 1 (x,y) */
    int s;                                /* lavoro: primo valore della coppia nella rel 2 (s,z) */
    int z;                                /* lavoro: secondo valore della coppia nella rel 2 (s,z) */
    int num_elem_composizione=0;         /* lavoro: numero elementi composizione */

    
        
    if (num_elem_R1 == 0)  
        stampa_relazione(composizione,num_elem_composizione);
    else {
            if(i <= num_elem_R1)
            {
                
                if ( j <= num_elem_R2)
                {
                    if (R1[num_elem_R1].y ==R2[num_elem_R2].x)
                    {
                        num_elem_composizione++;
                        composizione = (elem_relazione_t *) realloc(composizione,num_elem_composizione *sizeof(elem_relazione_t));
                        composizione[num_elem_composizione-1].x = R1[num_elem_R1].x;
                        composizione[num_elem_composizione-1].y = R2[num_elem_R2].y;
                    }
                
                    calcola_composizione(R1,num_elem_R1,R2,num_elem_R2 +1);
        
                    calcola_composizione(R1,num_elem_R1+1,R2,0);
                }
            }
        }
}

/*  
    if (num_elem_R1 == 0)
         stampa_relazione(R1,
                          num_elem_R1);

else {
          if( num_elem_R1 > i)
            {
                if(R1[i].y ==R2[j].x){
               composizione = (elem_relazione_t *) realloc(composizione,num_elem_composizione *sizeof(elem_relazione_t));
                composizione[num_elem_composizione].x = R1[num_elem_R1].x;
                composizione[num_elem_composizione].y = R2[num_elem_R2].y;


                num_elem_composizione= calcola_composizione(R1,num_elem_R1,R2,num_elem_R2-1);





 */
/*
     scorrere ogni elemento dell prima relazione per ogni elemento della seconda relazione
    while (i  < num_elem_R1)
    {
        x = R1[i].x;
        y = R1[i].y;
        j = 0;

        while(j < num_elem_R2)
        {
            s = R2[j].x;
            z = R2[j].y;
             controllo se il il secondo valore della prima coppia e uguale al primo della seconda
                (x,y) , (s,z) e se è gia stato inserito , se non e' stato inserito e y=s lo inserisco
            if(y==s && !esiste_in_relazione(composizione,
                                            num_elem_composizione,
                                            x,
                                            z))
            {

                composizione = (elem_relazione_t *) realloc(composizione,num_elem_composizione *sizeof(elem_relazione_t));
                composizione[num_elem_composizione].x = R1[i].x;
                composizione[num_elem_composizione].y = R2[j].y;
                num_elem_composizione++;
            }

            j++;
        }
        i++;
    }
     stampare la relazione composizione
    stampa_relazione(composizione,num_elem_composizione);
     liberare la memoria free(composizione);*/


/*************************************************************************/
/* Definizione della funzione per calcolare la differenza  simmetrica    */
/*************************************************************************/
void calcola_diff_simmetrica(elem_relazione_t *R1,   /* input: prima relazione */
                                   int num_elem_R1,        /* input: numero elementi prima relazione */
                                   elem_relazione_t *R2, /* input: seconda relazione */
                                   int num_elem_R2)        /* input: num. elementi seconda relazione */
{
    elem_relazione_t *diff_simmetrica = NULL; /* lavoro/output: risultato diff. simmetrica tra relazioni */
    int i = 0,                                /* lavoro: contatore per assegnazioni valori diff. simmetrica */
        j = 0,                                /* lavoro: contatore per assegnazioni valori diff. simmetrica */
        num_elem_diff_simm = 0;               /* lavoro: numero elementi diff. simmetrica */

    /* per ogni elemento della prima relazione, controllare che non esiste nella seconda relazione, se
       non esiste viene aggiunto agli elementi della differenza simmetrica */
    while (i < num_elem_R1)
    {
        if (!esiste_in_relazione(R2,
                                num_elem_R2,
                                R1[i].x,
                                R1[i].y))
        {
            num_elem_diff_simm++;
            diff_simmetrica = (elem_relazione_t *) realloc(diff_simmetrica,
                                                             num_elem_diff_simm *
                                                             sizeof(elem_relazione_t));
            diff_simmetrica[num_elem_diff_simm - 1].x = R1[i].x;
            diff_simmetrica[num_elem_diff_simm - 1].y = R1[i].y;
        }
        i++;
    }
    /* per ogni elemento della seconda relazione, controllare che non esiste nella seconda relazione, se
       non esiste viene aggiunto agli elementi della differenza simmetrica */
    while (j < num_elem_R2)
    {
        if (!esiste_in_relazione(R1,
                                 num_elem_R1,
                                 R2[j].x,
                                 R2[j].y))
        {
            num_elem_diff_simm++;
            diff_simmetrica = (elem_relazione_t *) realloc(diff_simmetrica,
                                                             num_elem_diff_simm *
                                                             sizeof(elem_relazione_t));
            diff_simmetrica[num_elem_diff_simm - 1].x = R2[j].x;
            diff_simmetrica[num_elem_diff_simm - 1].y = R2[j].y;
        }
        j++;
    }

    /* stampare l'insieme differenza simmetrica */
    stampa_relazione(diff_simmetrica,
                      num_elem_diff_simm);
    /* liberare la memoria associata alla differenza simmetrica */
    free(diff_simmetrica);
}



