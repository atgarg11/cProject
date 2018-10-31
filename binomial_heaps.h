#include <stdlib.h>

#include "binomial_heaps.h"

typedef struct bn_heap_node_t_ {
    struct bn_heap_node_t_  *parent;    
    struct bn_heap_node_t_  *child;
    struct bn_heap_node_t_  *sibling;   
    int                     value;
    int                     degree;     //number of children of this node
}bn_heap_node;

typedef struct binomial_heap_t_ {
    bn_heap_node    *head;
}binomial_heap;

bn_heap_node    *alloc_bn_heap_node();
binomial_heap   *make_binomial_heap();
