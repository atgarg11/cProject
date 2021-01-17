#ifndef _ADT_H_
#define _ADT_H_
#include "ds.h"

extern int MINUS_INFINITY;
extern int LINFINITY;

#define NIL             MINUS_INFINITY

#define QSIZE 32
#define HSIZE 32
#define HEAP_EMPTY (0xFFFFFFFF)

typedef int (*hashf)(void *);
typedef struct hash_ {
    int size;
    hashf hash_func;
    list_head *head;
    list_head *head2;
}hash_t;


typedef struct queue_t_ {
    int array[QSIZE];
    int head;   // write index in queue 
    int tail;   // read index in queue
    int size;
}queue_t;

typedef struct heap_node {
    int key;
    int element;
}heap_node_t;

typedef struct heap_ {
    heap_node_t* array[HSIZE];
    int heap_size;
}heap_t;

/***********  hash */
int         func1(void *key);
hash_t*     init_hash(int size, hashf f);
void        hash_insert(hash_t *hash, int data, int value);
listNode*   hash_find(hash_t  *hash, int data);

/** ******* Queue Functions */
queue_t*    init_queue();
void        enqueue(queue_t    *q, int data);
int         dequeue(queue_t *);


/*********  Stack Functios  *****/
int     pop();
void    push(int data);
int     is_empty(int first);
void    push2(int data);
int     pop2();
int     stack_size();
void    print_stack(stack_t    *stack);
/*********  Heap Functios  *****/

#define heapleft(i)     ((2*i)+1)
#define heapright(i)    ((2*i)+2)
#define heapparent(i)   (((i)-1)/2)

int*    heap_sort_array(int ar[], int size);
heap_t* init_heap();

int*    create_max_heap(int *array, int size);
int     heap_extract_max(int *array, int *size);
void    max_heap_insert_key(int *array, int* size, int key);

int*    create_min_heap(int *array, int size);
int     heap_extract_min(int *array, int *size);
void    min_heap_insert_key(int *array, int* size, int key);

int     heap_extract_max_node(heap_t    *hp);
void    max_heap_increase_node_key(heap_t  *hp, int index, int new_key);
void    max_heap_insert_node(heap_t    *hp, int key, int element);
int     heap_extract_min_node(heap_t    *hp);
void    min_heap_decrease_node_key(heap_t  *hp, int index, int new_key);
void    min_heap_insert_node(heap_t    *hp, int key, int element);
void    test_hash();

void    print_hash(hash_t  *hash);
void    test_deque();


/****       list functions  ******/
void    test5_delete_node();
void    test6_cycle();
void    test7_find_odd_numbers();
void    test8_copy_list_with_random();
void    practise_list(int tc);

/*******    insert a node at the head   */
listNode*   list_insert_head(listNode   **head, listNode    *node);
listNode*   listInsertHead(listNode **head, int data);
/*  Insert a node after a given node    */
listNode*   list_insert(listNode **head, listNode    *node);
listNode*   listInsert(listNode **head, int data);
    /*****  delete a node from the list*/
listNode*   delete_node(listNode  *node);
listNode*   print_list(listNode *head);

listNode*   dll_insert(listNode   **head, int data);
listNode*   dll_insert2(listNode  **head, listNode    *node);
/*      Return a linked list node for a given index */
listNode*   getNode(listNode    *head, int index);
int         find_num_list_elements(listNode *head);

//  *****   Test Functions  ******


void test3_queue();
void test4_queue_using_stack();
void test1_test_stack();
#endif
