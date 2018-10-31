#include <stdio.h>
#include <stdlib.h>
#include "adt.h"

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

heap_t* init_heap()
{
    heap_t* hp = (heap_t*)malloc(sizeof(heap_t));
    hp->heap_size = 0;
    return hp;
}

int heap_key(heap_t *hp, int index)
{
    return (hp->array[index]->key);
}

void heap_swap_elements(heap_t  *hp, int index1, int index2)
{
    heap_node_t*    tmp;
    tmp = hp->array[index1];
    hp->array[index1] = hp->array[index2];
    hp->array[index2] = tmp;
}
/*  node at index should satisfy the heapify_max property.
    node->left and node->right are already max heaps but the node is not
    */
int*    heapify_max2(int *ar, int index, int size);

/**     heapify_max is an opertion performed downwards. 
        Underlying assumption is that the left and right subtree at 
        given index are already max heaps   
        input: index which needs to be heapified**/

static void heapify_max(int *array, int size, int index)
{
    while (heapleft(index) < size ) {
        if (heapright(index) < size) {
            if (array[heapright(index)] > array[heapleft(index)]) {
                swap(array+heapright(index), array+index);
                index = heapright(index);
                continue;
            }
        }
        if (array[heapleft(index)] > array[index]) {
            swap(array+heapleft(index), array+index);
            index = heapleft(index);
        }
    }
}

static void heapify_min(int *array, int size, int index)
{
    while (heapleft(index) < size ) {
        if (heapright(index) < size) {
            if (array[heapright(index)] < array[heapleft(index)]) {
                swap(array+heapright(index), array+index);
                index = heapright(index);
                continue;
            }
        }
        if (array[heapleft(index)] < array[index]) {
            swap(array+heapleft(index), array+index);
            index = heapleft(index);
        }
    }
}

int*    create_max_heap(int *array, int size)
{
    int nleaves = (size+1)/2;
    int i  = size-nleaves; 
    for ( i = size-nleaves-1 ; i >=0 ; i--) {
        if ( array [i] >= array[2*i+1] && 
                (((2*i)+2 >= size) || 
                (((2*i)+2)<size && array[i] >= array[2*i+2]))) {
            ;
        } else {
            heapify_max(array, size, i);
        }
    }
}
int*    create_min_heap(int *array, int size)
{
    int nleaves = (size+1)/2;
    int i  = size-nleaves; 
    for ( i = size-nleaves-1 ; i >=0 ; i--) {
        if ( array [i] <= array[2*i+1] && 
                (((2*i)+2 >= size) || 
                (((2*i)+2)<size && array[i] >= array[2*i+2]))) {
            ;
        } else {
            heapify_min(array, size, i);
        }
    }
}

/*  Heap sort function  */
int*    heap_sort_array(int ar[], int size)
{
    int i  = 0; 
    int *res = ar;

    for (i = 0 ; i < size; ) {
        ar++; size--;
        ar = heapify_max2(ar, 0, size);
    }
    return res;
}

/*  Extract the max out of the heap */
int heap_extract_max(int *array, int *size)
{
    int i = 0, res = -1;
    int s = *size;
    if (( NULL == array) || 0 == *size)
        return res;
    
    res = array[0]; array[0] = array[*size-1] ;
    array[*size-1 ] = MINUS_INFINITY;
    (*size)--;
    heapify_max(array, *size, 0 );
    return res;
}
/*  Extract the min out of the heap */
int heap_extract_min(int *array, int *size)
{
    int i = 0, res = -1;
    int s = *size;
    if (( NULL == array) || 0 == *size)
        return res;
    
    res = array[0]; array[0] = array[*size-1] ;
    array[*size-1 ] = INFINITY;
    (*size)--;
    heapify_min(array, *size, 0 );
    return res;
}

/*  Get the max out of heap*/
int heap_get_max(int *array, int size) 
{
    if (NULL == array || 0 == size) return 0;
    return array[0];
}

int heap_get_min(int *array, int size) 
{
    if (NULL == array || 0 == size) return 0;
    return array[0];
}

void max_heap_increase_key(int *array, int size, int index, int new_key)
{
    if (NULL == array || 0 == size || index >= size) return;
    int nleaves = (size+1)/2;
    array[index] = new_key;
    while (index) {
        if (array[heapparent(index)]< array[index]) {
            swap(array+heapparent(index), array+index);
            index = heapparent(index);
        } else { break; }
    }
}
void max_heap_insert_key(int *array, int* size, int key)
{
    int index = *size;
    if (NULL == array || 0 == size) return;
    *size++;
    array[index] = key;
    max_heap_increase_key(array, *size, index, key);
}

void min_heap_decrease_key(int *array, int size, int index, int new_key)
{
    if (NULL == array || 0 == size || index >= size) return;
    int nleaves = (size+1)/2;
    array[index] = new_key;
    while (index) {
        if (array[heapparent(index)] > array[index]) {
            swap(array+heapparent(index), array+index);
            index = heapparent(index);
        } else { break; }
    }
}
void min_heap_insert_key(int *array, int* size, int key)
{
    int index = *size;
    if (NULL == array || 0 == size) return;
    *size++;
    array[index] = key;
    min_heap_decrease_key(array, *size, index, key);
}

int*    heapify_max2(int *ar, int index, int size)
{
    int i = 0, n ;
    int v = 0; i = index;
    while (i < (size/2)-1 ) { 
        v = (2*(i+1) < size) ? 1: 0; 
        if (v) {
            if (ar[2*(i+1)] > ar[i] || 
                    ar[2*i+1] > ar[i]) {
                index = (ar[2*i+2] > ar[2*i+1]) ? 2*i+2: 2*i+1;
                swap(ar+i, ar+index);
                i = index;
            } 
        }else if (ar[2*i+1] > ar[i]) {  
            index = 2*i+1;
            swap(ar+i, ar+index);
            i = index;
        } else break;
    }
    return ar;
}

int array[] =   {6,2,7,14,10,12,9,4,8};
void practise_heaps(int argc)
{
    int array1[] =   {6,2,7,14,10,12,9,4,8};
    int *a;
    int size = sizeof(array)/sizeof(int);
    char    ar[] = "hello world\n";
    create_max_heap(array1, sizeof(array1)/ sizeof(int));

    switch(argc) {
        case 1:
            a = heap_sort_array(array1, sizeof(array1)/sizeof(int));
            break;
        case 2:
            printf("%d, ", heap_extract_max(array1, &size));
            printf("%d, ", heap_extract_max(array1, &size));
            break;
        case 3:
            printf("%d, ", heap_extract_max(array1, &size));
            max_heap_insert_key(array1, &size, 20);
            printf("%d, ", heap_extract_max(array1, &size));
            printf("%d, ", heap_get_max(array1, size));
        default:
            break;
    }
}
static void heap_heapify_max(heap_t *hp, int index)
{
    while (heapleft(index) < hp->heap_size ) {
        if (heapright(index) < hp->heap_size) {
            if (hp->array[heapright(index)]->key > 
                    hp->array[heapleft(index)]->key) {
                heap_swap_elements(hp, heapright(index), index);
                index = heapright(index);
                continue;
            }
        }
        if (hp->array[heapleft(index)]->key > 
                hp->array[index]->key) {
            heap_swap_elements(hp, heapleft(index), index);
            index = heapleft(index);
        }
    }
}

int heap_extract_max_node(heap_t    *hp)
{
    heap_node_t *hn = NULL;
    int i = 0, res = -1;
    if (hp->heap_size == 0)
        return res;
    
    hn = hp->array[0]; hp->array[0] = hp->array[hp->heap_size-1] ;
    hp->array[hp->heap_size-1]->key = MINUS_INFINITY;
    hp->heap_size--;
    heap_heapify_max(hp, 0);
    return res;
}

void max_heap_increase_node_key(heap_t  *hp, int index, int new_key)
{
    hp->array[index]->key = new_key;
    while (index) {
        if (hp->array[heapparent(index)]->key < hp->array[index]->key) {
            heap_swap_elements(hp, heapparent(index), index);
            index = heapparent(index);
        } else { break; }
    }
}

void max_heap_insert_node(heap_t    *hp, int key, int elem)
{
    if (hp->heap_size > HSIZE-1) return;
    heap_node_t*    node = (heap_node_t*)malloc(sizeof(heap_node_t));
    node->key = key; 
    node->element = elem;

    int index = hp->heap_size;
    if ( 0 == index) { 
        hp->array[hp->heap_size++] = node;
        return;
    }

    hp->array[hp->heap_size++] = node;
    max_heap_increase_node_key(hp, index, key);
}
/****   min heap    **/
static void heap_heapify_min(heap_t *hp, int index)
{
    while (heapleft(index) < hp->heap_size ) {
        if (heapright(index) < hp->heap_size) {
            if (hp->array[heapright(index)]->key < 
                    hp->array[heapleft(index)]->key) {
                heap_swap_elements(hp, heapright(index), index);
                index = heapright(index);
                continue;
            }
        }
        if (hp->array[heapleft(index)]->key < 
                hp->array[index]->key) {
            heap_swap_elements(hp, heapleft(index), index);
            index = heapleft(index);
        }
    }
}

int heap_extract_min_node(heap_t    *hp)
{
    heap_node_t *hn = NULL;
    int i = 0, res = HEAP_EMPTY;
    if (hp->heap_size == 0)
        return res;
    
    hn = hp->array[0]; hp->array[0] = hp->array[hp->heap_size-1] ;
    hp->array[hp->heap_size-1]->key = INFINITY;
    hp->heap_size--;
    heap_heapify_min(hp, 0);
    return res;
}
/**
 * decrease a key in min heap. This might change the heap property 
 * and so we need to do the heapification from the node upwards. 
 */

void min_heap_decrease_node_key(heap_t  *hp, int index, int new_key)
{
    hp->array[index]->key = new_key;
    while (index) {
        if (hp->array[heapparent(index)]->key > hp->array[index]->key) {
            heap_swap_elements(hp, heapparent(index), index);
            index = heapparent(index);
        } else { break; }
    }
}
/**
 * Insert a key in heap. Allocate memory for the heap node
 */
void min_heap_insert_node(heap_t    *hp, int key, int elem)
{
    if (hp->heap_size > HSIZE-1) return;
    heap_node_t*    node = (heap_node_t*)malloc(sizeof(heap_node_t));

    node->key = key; 
    node->element = elem;

    /*  if no elements in heap, insert this element at index 0
        and nothing to heapify. return  */
    int index = hp->heap_size;
    if ( 0 == index) { 
        hp->array[hp->heap_size++] = node;
        return;
    }
    /*  insert the element at the last index and 
     heapify from that index    */
    hp->array[hp->heap_size++] = node;
    min_heap_decrease_node_key(hp, index, key);
}

