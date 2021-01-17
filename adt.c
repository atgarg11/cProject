#include <stdio.h>
#include <stdlib.h>
#include "adt.h"

int MINUS_INFINITY =  0xFFFFFFF;
int LINFINITY = 0x7FFFFFF;
/**
  * this file represents the abstract data type like stacks, queues, 
  * hash tables, disjoint sets and like
  */

/********   Stack implementation in Array *******/
int  stack[SSIZE];
int  stack2[SSIZE];
int  *queue = stack;

int first = -1, first2= -1;
int head = -1, tail = -1;

void push(int data)
{
    if ((first+1) < SSIZE) {
        first++;
        stack[first] = data;
    }
}
int pop()
{
    if (first > -1) {
        return stack[first--];
    } else {
        return 0xFFFFFFFF;// error handling
    }
}
int is_empty(int first)
{
    if ( -1 == first) return 1;
    return 0;
}

void push2(int data)
{
    if ((first2+1) < SSIZE) {
        first2++;
        stack2[first2] = data;
    }
}
int pop2()
{
    if (first2 > -1) {
        return stack2[first2--];
    } else {
        return 0xFFFFFFFF;// error handling
    }
}

int stack_size()
{
    return (first+1);
}

queue_t* init_queue()
{
    queue_t *que = (queue_t*)calloc(1, sizeof(queue_t));
    que->head = que->tail = -1;
    que->size = QSIZE;
    return que;
}
void enqueue(queue_t*   q, int data)
{
    if ((q->head>=q->tail) && ((q->head-q->tail) < QSIZE-1)) {
        if ((q->head+1) < QSIZE-1)  {
            q->head++;
        } else { 
            q->head = 0; 
        }
        q->array[q->head] = data; 
    } else  {
        printf("queue is full\n");
    } 
}

int dequeue(queue_t *q) 
{
    if ((q->head - q->tail) == 0) { 
        return -1;
        printf("no element in the queue\n");
    } else {
        if ((q->tail+1) < QSIZE) {
            q->tail++;
        } else {
            q->tail = 0;
        }
        return q->array[q->tail];
    }
    return -1;
}

void test3_queue()
{
    int el;
    queue_t *q= NULL;
    q=init_queue();
    printf("queue example:\n");
    do {
        el = dequeue(q);
        printf("%d,", el);
    }while (-1 != el);
}
/*  double ended queue */
void enqueue_head(queue_t   *q, int data) 
{
    if (q->tail >= q->size-1 || 
            (q->tail + q->head >= q->size-1) ||
            q->head >= q->size-1 ) {
        return;
    } else { 
        q->head++;
        q->array[q->head] = data;
    }
}

void enqueue_tail(queue_t   *q, int data) 
{
    if (q->tail >= q->size-1 || 
            (q->tail + q->head >= q->size-1) ||
            q->head >= q->size-1 ) {
        return;
    } else { 
        q->tail++;
        q->array[q->size-1-q->tail] = data;
    }
}
int dequeue_head(queue_t    *q)
{
    if (-1 == q->head) {
        return MINUS_INFINITY;
    } else { //if ((q->head < q->size-1) && (q->tail + q->head)< q->size-1){
        return q->array[q->head--];
    }
}

int dequeue_tail(queue_t    *q)
{
    if (-1 == q->tail) {
        return MINUS_INFINITY;
    } else { 
        return q->array[q->size-1-q->tail--];
    }
}

void test_deque()
{
   queue_t  *q = init_queue(); 
   enqueue_head(q, 2);
   enqueue_head(q, 3);
   enqueue_tail(q, 22);
   printf("Tail:%d, head:%d\n", dequeue_tail(q), dequeue_head(q));
}

void print_stack(stack_t    *stack)
{
    int i = 0; 
    stack = NULL;   // to avoid warnings
    for ( i = stack_size(); i > 0; i--) { 
        printf("%d, " , pop());
    }
}
void test1_test_stack()
{
    int i = 0, size = 0;
    printf("stack example:\n");
    push(1); push(2);
    push(3); push(4);
    size = stack_size();
    for ( i = 0 ; i < size ; i++) {
        printf("%d, ", pop());
    }
}

void pushq2(int data)
{
    push(data);
}
int popq2()
{
    int i;
    int empty = is_empty(first);
    while(!empty) {
        push2(pop());
        empty = is_empty(first);
    }
    i = pop2();
    while (!is_empty(first2)) 
    push(pop2());

    return i;
}
void test4_queue_using_stack()
{
    int i = 0;
    pushq2(1);
    pushq2(2);
    pushq2(3);
    pushq2(4);
    for ( i = 0; i < stack_size(); ) {
        printf("%d,", popq2());
    }
}

hash_t* init_hash(int size, hashf f)
{
    int i = 0;
    hash_t  *hash = 
        (hash_t*) calloc(0, sizeof(hash_t));
    hash->head = (list_head*) malloc((size * sizeof(list_head*)));
    hash->head2 = (list_head*) malloc((size * sizeof(list_head*)));
    hash->size = size;
    hash->hash_func = f;
    for ( i = 0 ; i < size; i++) { 
        hash->head[i].head = NULL;
        hash->head2[i].head = NULL;
    }
    return hash;
}
void hash_insert(hash_t *hash, int data, int value)
{
    listNode    *head = NULL;
    listNode    *tmp;
    int index = hash->hash_func((void*)&data);
    //int index = func1((void*)&data);
    if (data < 0)  {
        head = hash->head2[index].head;
        tmp  = (listNode*)listInsertHead(&head, data);
        tmp->int_data = index;
        tmp->value = value;
        hash->head2[index].head = tmp;
    } else {
        head = hash->head[index].head;
        tmp  = (listNode*)listInsertHead(&head, data);
        tmp->int_data = index;
        tmp->value = value;
        hash->head[index].head = tmp;
    }
}
listNode*   hash_find(hash_t  *hash, int data)
{
    int index = hash->hash_func((void*)&data);
    listNode    *head = hash->head[index].head;
    if ( data < 0) 
        head = hash->head2[index].head;
    while (head) {
        if (head->int_data == data) return head;
    }
    return NULL;
}
int func1(void *key) 
{
    int i = *(int*)key;
    if ( i < 0) return ((0-i)%10);
    return (*(int*)key)%10;
}
void print_hash(hash_t  *hash)
{
    int i = 0; 
    for ( i = hash->size -1 ; i >=0 ; i--) {
        print_list(hash->head2[i].head);
    }
    for ( i = 0 ; i < hash->size; i++) {
        print_list(hash->head[i].head);
    }
}
void test_hash()
{
    int x = 2, y = 3;
    hash_t *hash = init_hash(8, func1);
    hash_insert(hash, 2,2);
    hash_insert(hash, 3,3);
    hash_insert(hash, 13, 13);
    print_hash(hash);
}
