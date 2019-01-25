#ifndef GRAPHS_H_
#define GRAPHS_H_

#define WHITE 1
#define GREY    2
#define BLACK   3

#define CHAR_INDEX(c) ((c)-'a')
#define INDEX_CHAR(i) ((i)+'a')

#define NOV 5   // Number of vertices
#define TWO 2
#define MI MINUS_INFINITY
#define IN  INFINITY

typedef struct  GRAPHS_ {
    int v;
    char offset;    // This offset is used to represet char 
                    // having vertices start from other than a
    int *color;     // used to maintain visit status
    int *start;     // time when this node ws first discovered
    int *finish;    // time when this node is traversed fully
    int *pred;      // node predecessor of this node in path
    int *dist;   
    list_head   adj_list[0];
}graph_t;

/*      Practice Problems   */
void mother_vertex(graph_t  *graph);
void mst_prim(graph_t   *g, int root);
void mst_kruskal(graph_t *graph);
void floyd_warshall(int graph[][NOV]);
void test_floyd_warshall(void);

#endif
