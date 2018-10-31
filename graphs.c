/*  Graph Example */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ds.h"
#include "graphs.h"
#include "util.h"
#include "adt.h"

void practice_ads(int tc, int argc, char *argv[]);
static int time = 1;
void print_graph(graph_t  *g)
{
    int i = 0 ; 
    listNode *adj = NULL;
    for (i = 0 ; i < g->v; i++) {
       adj = g->adj_list[i].head;
       print_list(adj);
    }
}

graph_t* create_graph(int nov) 
{
    int i = 0;
    graph_t *g = (graph_t*)malloc(sizeof(graph_t));
    g->v = nov;
    g->adj_list = (list_head*) malloc(g->v * sizeof(list_head));
    g->color = (int*) malloc(g->v * sizeof(int));
    g->start = (int*)malloc(g->v * sizeof(int));
    g->finish = (int*)malloc(g->v * sizeof(int));
    g->pred = (int*)malloc(g->v * sizeof(int));
    for ( i = 0 ; i < g->v; i++) {
        g->adj_list[i].head = NULL;
        g->color[i] = WHITE;
        g->start[i] = g->finish[i] = 0;
        g->pred[i] = MINUS_INFINITY;
    }
    return g;
}
// Creat an edge from src to dest. c if the graphs is for alphabets
void add_edge(graph_t   *g, int src, int dest, int weight)
{
    listNode    *tmp = NULL;
    /*  the src and dest specified are not the vertices of the graph    */
    if ( (src >= g->v ) || (dest >=g->v)) return;

    tmp = allocListNode(dest);
    g->adj_list[src].head = 
        list_insert_head(&(g->adj_list[src].head), tmp);
    tmp->g_weight   =   weight;
}
void dfs_node(graph_t *g, int vertex)
{
    listNode    *tmp = NULL;
    if( g->color[vertex] == WHITE) {
        printf("%d,",vertex);
        g->start[vertex] = time++;
        g->color[vertex] = GREY;
        tmp = g->adj_list[vertex].head;
        while (tmp) {
            if (g->color[tmp->int_data] == WHITE ) dfs_node(g, tmp->int_data);
            tmp = tmp->next;
        }
        g->color[vertex] = BLACK;
        g->finish[vertex] = time++;
    }
}
void dfs(graph_t* g, int vertex)
{
    int i = 0, count = 0; 
    listNode *tmp = NULL;

    for ( count = 0, i = vertex ; count < g->v; count++, i++) {
        if (i == g->v) i = 0;
        if (g->color[i] == WHITE) {
            dfs_node(g, i);
        }
    }
}

void bfs(graph_t *g, int vertex)
{
    int i = vertex, count = 0 ; 
    listNode    *tmp = NULL;
    queue_t *que = init_queue();

    for ( count = 0 ; count < g->v && i > -1; count++) {
            g->color[i] = GREY;
            printf("%d,", i);
            tmp = g->adj_list[i].head;
            while (tmp) {
                if (g->color[tmp->int_data] == WHITE) {
                    g->color[tmp->int_data] = GREY;
                    enqueue(que, tmp->int_data);
                }
                tmp = tmp->next;
            }
        g->color[i] = BLACK;
        i = dequeue(que);
    }
}

void top_sort_node(graph_t *g, int vertex)
{
    listNode    *tmp = NULL;
    if( g->color[vertex] == WHITE) {
        g->start[vertex] = time++;
        g->color[vertex] = GREY;
        tmp = g->adj_list[vertex].head;
        while (tmp) {
            if (g->color[tmp->int_data] == WHITE ) top_sort_node(g, tmp->int_data);
            tmp = tmp->next;
        }
        g->color[vertex] = BLACK;
        push(vertex);
        g->finish[vertex] = time++;
    }
}
void top_sort(graph_t* g, int vertex)
{
    int i = 0, count = 0; 
    listNode *tmp = NULL;

    for ( count = 0, i = vertex ; count < g->v; count++, i++) {
        if (i == g->v) i = 0;
        if (g->color[i] == WHITE) {
            top_sort_node(g, i);
        }
    }
}
void test_top_sort(graph_t  *graph, int vertex)
{
    int v;
    top_sort(graph, vertex);
    v = pop();
    while (0xFFFFFFFF != v) { 
        printf("%d,",v);
        v = pop();
    }

}

void test_alien_dictionary(int nov, char* argv[])
{
    graph_t *graph = NULL;
    int v, c;
    int i = 0 , j = 0;
    int len1, len2;
    char    *word1 = NULL, *word2 = NULL;
    nov = atoi(argv[0]);
    graph = create_graph(nov);
    argv++;
    // assuming more than one words
    for ( i = 0 ; i+1 < nov; i++) {
        word1 = argv[i]; word2 = argv[i+1];
        len1 = strlen(argv[i]); 
        len2 = strlen(argv[i+1]);
        for ( j = 0 ; j < (len1>len2 ? len2:len1); j++) {
            if (word1[j] != word2[j]) { 
                add_edge(graph, CHAR_INDEX(word1[j]), 
                        CHAR_INDEX(word2[j]), 0);
                break;
            }
        }
    }

    top_sort(graph, 0);
    v = pop();
    while (0xFFFFFFFF != v) { 
        printf("%c,", (char)INDEX_CHAR(v));
        v = pop();
    }
}

int top_sort_from_to(graph_t *g, int vertex, int dest)
{
    listNode    *tmp = NULL;
    int count = 0;
    if( (g->color[vertex] == WHITE) && (vertex != dest)) {
        g->start[vertex] = time++;
        g->color[vertex] = GREY;
        tmp = g->adj_list[vertex].head;
        while (tmp) {
            if (tmp->int_data == dest) ++count;
            else if (g->color[tmp->int_data] == WHITE ) 
                count+=top_sort_from_to(g, tmp->int_data, dest);
            tmp = tmp->next;
        }
        g->color[vertex] = WHITE; // to print all the paths
        push(vertex);
        g->finish[vertex] = time++;
    }
    return count;
}

/*  Tell number of paths between two verteces*/
int num_paths()
{
    int count = 0;
    graph_t *graph = create_graph(4);
    add_edge(graph,0,3, 0); 
    add_edge(graph,0,1, 0); 
    add_edge(graph,1,3, 0); 
    add_edge(graph,2,1, 0); 
    add_edge(graph,2,0, 0); 
    count = top_sort_from_to(graph, 2, 3);
    printf("no of paths:%d\n", count);
}
/*  this function relaxes all the edges from a given source vertex
    */
void graph_relax_edge(graph_t* g, int src, int* distance)
{
    listNode    *start = g->adj_list[src].head;
    while (start) {
        if (distance[start->int_data] > distance[src]+start->g_weight) {
            distance[start->int_data] = distance[src]+start->g_weight;
        }
        start = start->next;
    }
}
/****
  * Maintain a min priority QUEUE of all the vertices
  * extract the min element and insert in set of finished elements
  * relax all the edges from the extraced vertex.
  * 
  ****/
queue_t*  dikjstra(graph_t   *graph, int source)
{
    int v = -1;
    queue_t* q = init_queue();  // This queue is way of maintaing the 
                                // SET keeping the finished vertices
    heap_t  *pq = init_heap();  // min priority queue

    int i, d[graph->v];         /* maintain distance of all the vertices
                                   from source */
    for (i = 0; i < graph->v; i++ ) {
        d[i] = INFINITY; 
        min_heap_insert_node(pq, d[i], i); 
    }
    d[source] = 0;
    min_heap_decrease_node_key(pq, source, d[source]); 

    v = heap_extract_min_node(pq);
    while ( HEAP_EMPTY != v) {
        graph_relax_edge(graph, v, d);
        enqueue(q, source);
    }

}
void practise_graphs(int tc, int argc, char * argv[])
{

    graph_t *graph = NULL;
    graph = create_graph(6);
    add_edge(graph, 5, 0, 0);
    add_edge(graph, 5, 2,0);
    add_edge(graph, 4, 0,0);
    add_edge(graph, 4,1,0);
    add_edge(graph, 2,3,0);
    add_edge(graph, 3,1,0);

    switch (tc) {
        case 0:
            print_graph(graph);
            break;
        case 1: 
            dfs(graph, 5);
            break;
        case 2: 
            bfs(graph, 0);
            break;
        case 3: 
            test_top_sort(graph, 0);
            break;
        case 4: 
            test_alien_dictionary(argc-3, argv+3);
            break;
        case 5: 
            num_paths();
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            printf("%s calling practice_ads() \n", __FUNCTION__);
            argc = argc - 3;
            argv = argv + 3;
            if (argc) { 
                practice_ads(atoi(argv[0]), argc-1,argv+1); 
            }
            break;
        default :
            break;
    };
    printf("\n");
}
