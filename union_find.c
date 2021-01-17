#include <stdio.h>
#include <stdlib.h>

/*  Structure to represent a mamber of a set    */
typedef struct union_find_ {
    struct union_find_  *next;
    struct set_         *rep;
    int                 value;    
}union_find;

/*  linked representation of a set    
    Tail points to the last element of the list */

typedef struct set_ {
    union_find  *head;
    union_find  *tail;
    int         size;
}set;

/*  Tree representatoion of Disjoint sets   */
typedef struct set_tree_ {
    struct set_tree_    *parent;// parent (rep) of the set, this node belongs
    int                 value;
    int                 rank;  // height of this node in the tree
}set_tree;

set_tree*   alloc_uf_tree_node(int value)
{
    set_tree    *tnode = (set_tree*)calloc(1, sizeof(set_tree));
    tnode->value = value;
    tnode->rank = 0;
    tnode->parent = NULL;
    return tnode;
}
set_tree*   uf_tree_make_set(int value)
{
    set_tree    *tmp = alloc_uf_tree_node(value);
    tmp->parent = tmp;
    return tmp;
}
/*  Path compression is applied in this function    */
set_tree    *uf_tree_find_set(set_tree  *node)
{
    if (NULL == node) return node;
    if (node != node->parent) {
        node->parent = uf_tree_find_set(node->parent);
    }
    return node->parent;
}
set_tree*   uf_set_update(set_tree  *update_set, set_tree *parent)
{
    if (update_set->parent == update_set) {
        update_set->parent = parent->parent;
        return update_set->parent;
    }
    uf_set_update(update_set->parent, parent);
}
set_tree    *uf_tree_union(set_tree*    set1, set_tree* set2)
{
    set_tree    *tmp  = NULL;
    if (NULL == set1 ) return set2;
    if (NULL == set2) return set1;

    if (set1->rank > set2->rank) {
        set2->parent = set1->parent;
    } else {
        set1->parent = set2->parent;
        if (set1->rank == set2->rank) {
            set2->rank++;
        }
    } 
    return set2->parent;
}
/*  Union FInd Data stucture. List based implementation */

union_find* alloc_union_find_member(int value)
{
    union_find  *uf = (union_find*)calloc(1, sizeof(union_find));
    uf->value = value;
    uf->rep = NULL;
    uf->next = NULL;
    return uf;
}

set*    alloc_set()
{
    set*    p = (set*)calloc(1, sizeof(set));
    p->head = p->tail = NULL;
    return(p); 
}
set*    make_set(int val)
{
    union_find  *um = alloc_union_find_member(val);
    set *tset = alloc_set();
    tset->head = um;
    tset->tail = um;
    tset->size++;
    um->rep = tset;
    return tset;
}
/*  Given a union set member return the SET to which 
    This union member belong to */
set*    find_set(union_find *sm)
{
    if (NULL != sm) {
        return sm->rep;
    }
    return NULL;
}
/*  update the given set with the given rep 
    Helper function for the union operation */

set*    update_set(set* update_set, set* reps)
{
    union_find  *tmp = NULL;
    if ( NULL == update_set || NULL == reps) { 
        return NULL;
    }
    tmp = update_set->head;
    reps->tail->next = tmp;
    reps->tail = update_set->tail; 
    while (tmp) {
        tmp->rep = reps;
        tmp = tmp->next;
        reps->size++;
    }
    return reps;
}
/*      Union of two sets represented by the given unionmembers. 
        if the members belong to same set, NOOP */

set*   uf_union(union_find *um1, union_find *um2)
{
    set *tset1 = NULL, *tset2 = NULL;
    if (um1 != NULL && um2 != NULL) {
        tset1 = (set*)um1->rep;             
        tset2 = (set*)um2->rep;             
        if (tset1 == tset2) {
            return tset1;
        }
        if (tset1->size > tset2->size) {
            // tset1 is bigger so update tset2 with tset1->rep
            return update_set(tset2, tset1);
        } else {
            return update_set(tset1, tset2);
        }
    } else {
       if (um1) { return um1->rep; } 
       if (um2) { return um2->rep; } 
    }
    return NULL;
}
void print_set(set  *ts)
{
    int count = 0;
    if (NULL == ts) return;
    union_find   *tmp = ts->head; 
    for ( count = 0 ; count < ts->size; count++, tmp=tmp->next) {
        printf (" %d, set:0x%x ", tmp->value, (unsigned*)(tmp->rep));
    }
    printf ("\n");
}

void practice_ads(int tc, int argc, char *argv[])
{
    set *s1 = make_set(1);
    set *s2 = make_set(2);
    set *s3 = make_set(3);
    set *s4 = make_set(4);
    set *tmp = NULL;

    set_tree *st1 = uf_tree_make_set(10);
    set_tree *st2 = uf_tree_make_set(22);
    set_tree *st3 = uf_tree_make_set(30);
    set_tree *st4 = uf_tree_make_set(44);
    set_tree *tset = NULL;

    switch (tc) {
        default: // test graphs 11 
            printf("%s 2-> print set implemented as list\n"
                    "3->set implemented as tree\n ",
                    __FUNCTION__);
            print_set(s1);
        case 1:
            tmp = (uf_union(s1->head, s2->head));
            print_set(tmp);
            break;
        case 2:
            tmp = uf_union(s1->head, s2->head);
            tmp = uf_union(tmp->head, s3->head);
            print_set(tmp);
            break;
        case 3:
            tset = uf_tree_union(st1, st2);
            printf("Rank of new set, %d\n", tset->rank);
            tset = uf_tree_union(st3, tset);
            printf("Rank of new set, %d\n", tset->rank);
            tset = uf_tree_union(st4, tset);
            printf("Rank of new set, %d\n", tset->rank);

    };
}
