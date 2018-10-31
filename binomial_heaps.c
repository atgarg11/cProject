#include <stdlib.h>

#include "binomial_heaps.h"

binomial_heap   bh;
bn_heap_node    *alloc_bn_heap_node()
{
    bn_heap_node    *tmp = malloc(sizeof(bn_heap_node));
    tmp->parent = NULL; 
    tmp->sibling = NULL;
    tmp->child = NULL;
    return tmp;
}

/*  Returns the head of the binomial Heap   */
binomial_heap*  make_binomial_heap()
{
    return &bh;
}
/*  Union of two Binomial Trees having the same degree  */
bn_heap_node*   binomial_link(bn_heap_node  *tree1, bn_heap_node    *tree2)
{
    return NULL;
}
