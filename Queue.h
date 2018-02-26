/*
Implementa un coda FIFO oppure LIFO, su una struttura dati di tipo Array.
Complessità delle varie operazione O(1)
Ideale per code di dimensioni pressochè statiche, altrimenti meglio orientarsi
su code basate su una struttura dati di tipo lista(attenzione però la funzione malloc è molto onerosa!!).
*/

#ifndef QUEUE_H
#define QUEUE_H

/*La #define DEBUG rende compilabile i controlli delle varie funzioni, conviene
lasciarla fin quando il progetto non è terminato.*/

#define DEBUG

#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#endif //DEBUG

typedef struct Queue_ *Queue;

typedef int Item;

/*Inizializza la struttura dati adatta a contenere al più maxSize elementi (è presente malloc)*/
Queue queue_init(uint32_t maxSize);

/*Libera la memoria occupata da Queue in*/
void queue_free(Queue in);

/*Ritorna 1 se la coda è vuota altrimenti 0*/
uint8_t queue_is_empty(Queue in);

/*Ritorna 1 se la coda è piena altrimenti 0*/
uint8_t queue_is_full(Queue in);

/*Inserisce l'elemento in testa, utile per gestire la coda come uno stack*/
void queue_put_head(Queue in,Item item); //LIFO

/*Inserisce l'elemento in coda, utile per gestire la coda come una FIFO*/
void queue_put_tail(Queue in,Item item); //FIFO

/*Restituisce l'elemento in testa alla coda senza estrarlo*/
Item queue_get(Queue in);

/*Estrae l'elemento presente in testa.Notare che l'inserimento è variabile e l'estrazione è fissa,
fare attenzione nell'uso delle due differenti queue_put l'uso dev'essere coerente.*/
Item queue_extract(Queue in);

/*Ritorna il numero di elementi presenti nella coda*/
uint32_t queue_count(Queue in);

/*Ridimensiona la struttura dati di Queue in a contenere al più maxSize elementi, è necessario
 che la dimensione di Queue in sia >= a maxSize (è presente malloc)*/
void queue_resize(Queue in,uint32_t maxSize);


#endif // QUEUE_H
