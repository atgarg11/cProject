#ifndef _ADT_H_
#define _ADT_H_
#include "ds.h"

typedef int (*hashf)(void *);
typedef struct hash_ {
    int size;
    hashf hash_func;
    list_head *head;
    list_head *head2;
}hash_t;

#define QSIZE 32
typedef struct queue_t_ {
    int array[QSIZE];
    int head;   // write in dex in queue 
    int tail;   // read index in queue
}queue_t;

#define HEAP_EMPTY (0xFFFFFFFF)

typedef struct heap_node {
    int key;
    int element;
}heap_node_t;

#define HSIZE 32
typedef struct heap_ {
    heap_node_t* array[HSIZE];
    int heap_size;
}heap_t;

/***********  hash */
int func1(void *key);
hash_t* init_hash(int size, hashf f);
void hash_insert(hash_t *hash, int data, int value);
listNode*   hash_find(hash_t  *hash, int data);

/** ******* Queue Functions */
queue_t*    init_queue();
void enqueue(queue_t    *q, int data);
int dequeue(queue_t *);


/*********  Stack Functios  *****/
/*********  Heap Functios  *****/

#define heapleft(i)     ((2*i)+1)
#define heapright(i)    ((2*i)+2)
#define heapparent(i)   (((i)-1)/2)
#define MINUS_INFINITY  (0xFFFFFFFF)
#define INFINITY  (0x7FFFFFFF)

int*    heap_sort_array(int ar[], int size);
heap_t* init_heap();

int*    create_max_heap(int *array, int size);
int heap_extract_max(int *array, int *size);
void max_heap_insert_key(int *array, int* size, int key);

int*    create_min_heap(int *array, int size);
int heap_extract_min(int *array, int *size);
void min_heap_insert_key(int *array, int* size, int key);

int heap_extract_max_node(heap_t    *hp);
void max_heap_increase_node_key(heap_t  *hp, int index, int new_key);
void max_heap_insert_node(heap_t    *hp, int key, int element);
int heap_extract_min_node(heap_t    *hp);
void min_heap_decrease_node_key(heap_t  *hp, int index, int new_key);
void min_heap_insert_node(heap_t    *hp, int key, int element);
#endif
