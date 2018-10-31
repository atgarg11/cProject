#ifndef GRAPHS_H_
#define GRAPHS_H_

#define WHITE 1
#define GREY    2
#define BLACK   3

#define CHAR_INDEX(c) ((c)-'a')
#define INDEX_CHAR(i) ((i)+'a')

typedef struct  GRAPHS_ {
    int v;
    list_head   *adj_list;
    int *color;             // used to maintain visit status
    int *start;             // time when this node ws first discovered
    int *finish;            // time when this node is traversed fully
    int *pred;        // node predecessor of this node in path
}graph_t;


#endif
