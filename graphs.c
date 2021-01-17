/*  Graph Example */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ds.h"
#include "graphs.h"
#include "util.h"
#include "adt.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
using namespace std;


void practice_ads(int tc, int argc, char *argv[]);
static int gl_time = 1;


// Creat an edge from src to dest. c if the graphs is for alphabets
void add_edge(graph_t   *g, int src, int dest, int weight)
{
    listNode    *tmp = NULL;
    /* the src and dest specified are not the vertices of the graph  */
    if ( (src >= g->v ) || (dest >=g->v)) return;

    if (g->adj_list[src].head) {
        tmp = g->adj_list[src].head;
        while(tmp) {
            if (tmp->int_data == dest) return;
            tmp = tmp->next;
        }
    }
    tmp = allocListNode(dest);
    g->adj_list[src].head = 
        list_insert_head(&(g->adj_list[src].head), tmp);
    tmp->g_weight   =   weight;
}

graph_t* create_graph(int nov) 
{
    int i = 0;
    graph_t *g = (graph_t*)malloc(nov* sizeof(list_head) + 
                                    sizeof(graph_t));
    g->v = nov;
    g->offset = 'a';
    g->color = (int*) malloc(g->v * sizeof(int));
    g->start = (int*)malloc(g->v * sizeof(int));
    g->finish = (int*)malloc(g->v * sizeof(int));
    g->pred = (int*)malloc(g->v * sizeof(int));
    g->dist = (int*)malloc(g->v * sizeof(int));
    for ( i = 0 ; i < g->v; i++) {
        g->adj_list[i].head = NULL;
        g->color[i] = WHITE;
        g->start[i] = g->finish[i] = 0;
        g->pred[i] = MINUS_INFINITY;
    }
    return g;
}
/*  Function to create a graph
    input: 
            Number of vertices
            edges array with source, destination, weight touple
            number of edges
 */
graph_t*    get_graph1(int v, int edges[][3], int n_edges)
{
    graph_t *graph;
    int i = 0;
    graph = create_graph(v);
    for ( i = 0; i < n_edges; i++) {
        add_edge(graph, edges[i][0], edges[i][1], edges[i][2]);
    }
    return graph;
}
void print_graph_list(listNode *head)
{
    listNode    *node = head;
    listNode    *next = head;
    if (NULL == head) return ;
    do {
        printf("%d,",next->g_weight);
        node = next;
        next    = node->next;
    }while (NULL != next && next != head);
}
void print_graph(graph_t  *g)
{
    int i = 0 ; 
    listNode *adj = NULL;
    for (i = 0 ; i < g->v; i++) {
       adj = g->adj_list[i].head;
       printf("\nRow: %d-> ", i);
       print_graph_list(adj);
    }
}

void dfs_node(graph_t *g, int vertex)
{
    listNode    *tmp = NULL;
    if( g->color[vertex] == WHITE) {
        printf("%d,",vertex);
        g->start[vertex] = gl_time++;
        g->color[vertex] = GREY;
        tmp = g->adj_list[vertex].head;
        while (tmp) {
            if (g->color[tmp->int_data] == WHITE ) dfs_node(g, tmp->int_data);
            tmp = tmp->next;
        }
        g->color[vertex] = BLACK;
        g->finish[vertex] = gl_time++;
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

void top_sort_node(graph_t *g, int vertex)
{
    listNode    *tmp = NULL;
    if( g->color[vertex] == WHITE) {
        g->start[vertex] = gl_time++;
        g->color[vertex] = GREY;
        tmp = g->adj_list[vertex].head;
        while (tmp) {
            if (g->color[tmp->int_data] == WHITE ) top_sort_node(g, tmp->int_data);
            tmp = tmp->next;
        }
        g->color[vertex] = BLACK;
        push(vertex);
        g->finish[vertex] = gl_time++;
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
        g->start[vertex] = gl_time++;
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
        g->finish[vertex] = gl_time++;
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
        d[i] = LINFINITY; 
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
/*  Nov 2018, Graph Practice    */
graph_t*  graph_transpose(graph_t    *graph)
{
    int i = 0;
    listNode    *head = NULL;
    graph_t *tgraph = create_graph(graph->v);
    for ( i = 0 ; i < graph->v; i++) { 
        if ( graph->adj_list[i].head) {
            head = graph->adj_list[i].head;
            while (head) {
                add_edge(tgraph, head->int_data, i, head->g_weight);
                head = head->next;
            }
        }
    }
    print_graph(tgraph);
    return tgraph;
}
/*  Nov 5,2018  
    inputs: Graph and source vertex s
    int s is the vertex in the graph. 
    should be less than the max vertex. */
void graph_bfs(graph_t  *graph, int s)
{
    listNode    *node = NULL;
    queue_t     *que =  init_queue();
    int         dest = 0;
    if ( NULL == graph || s >= graph->v || 
            graph->adj_list[s].head == NULL) {
        printf("%s: Invalid Params\n", __FUNCTION__);
        return;
    }
    graph->color[s] = GREY;
    graph->pred[s] = MINUS_INFINITY;
    printf("\n BFS tree: ");
    do {
        printf("%d, ", s);
        node = graph->adj_list[s].head;
        while(node) {
            dest = node->int_data;
            if (graph->color[dest] == WHITE) {
                graph->color[dest] = GREY;
                graph->pred[dest] = s;
                enqueue(que, dest);
            }
            node = node->next;
        }
        graph->color[s] = BLACK;
        s = dequeue(que);
    } while(s != -1);
}

/*  graph_dfs() : Nov 11, 2018
    inputs: the graph, no source vertex is needed 
 */
void dfs_visit(graph_t  *graph, int s)
{
    listNode    *node = NULL;
    int         new_node_data = -1;
    graph->color[s] = GREY;
    gl_time = gl_time+1;
    graph->dist[s] = gl_time;
    graph->start[s] = gl_time;
    node = graph->adj_list[s].head;
    while(node) {
        new_node_data = node->int_data;
        /*  code to determine numner pf paths*/
        if (graph->color[new_node_data] == WHITE) {
            graph->pred[new_node_data] = s;
            dfs_visit(graph, new_node_data);
        }
        node = node->next;
    }
    graph->finish[s] = ++gl_time;
    graph->color[s] = BLACK;
    printf("%d, ", s);
    push(s+graph->offset);
}
void graph_dfs(graph_t   *graph)
{
    int i = 0;
    for ( i = 0 ; i < graph->v; i++) {
        if (graph->color[i] == WHITE) {
            dfs_visit(graph, i);
        }
    }
}
/*  Topological sort. C tells if it is a char graph */
void graph_top_sort(graph_t    *graph, int c)
{
    int i = 0;
    graph_dfs(graph);
    if ( 0 == c) {
        print_stack(NULL);
    } else { 
        for ( i = stack_size(); i > 0; i--) { 
            printf("%c, " , pop());
        }
    }
}

int char_vertex(char v, graph_t  *g)
{
    return (v-(g->offset));
}
//  Call this function before calloing add_cedge() 
void graph_set_offset(graph_t    *graph, char offset)
{
    graph->offset = offset;
}
/*  Nov 15, 2018    add char vertex graph   */
void add_cedge(graph_t  *graph, char src, char dest, int weight)
{
    int s = char_vertex(src, graph);
    int d = char_vertex(dest, graph);
    add_edge(graph, s, d, weight);
}
/*  Nov 19, 2018    
    graph_num_paths() Tells number of paths between two ver */
int graph_num_paths(graph_t *graph, int s, int d)
{
    listNode    *node = graph->adj_list[s].head;
    int         ndata = -1;
    int count = 0;
    while(node) {
        ndata = node->int_data;
        if (ndata == d) { 
            count++;
        }
        if (graph->color[ndata] == WHITE) {
            count += graph_num_paths(graph, ndata, d);
        }
        node = node->next;
    }
    return count;
}
/*  Nov 20, 2018    
    bellman_ford() Determine the shortest path from a src   */
void graph_relax(graph_t    *g, listNode    *src, listNode  *dst)
{
    if (g->dist[dst->int_data] > g->dist[src->int_data]+dst->g_weight) {
        g->dist[dst->int_data] = g->dist[src->int_data] + dst->g_weight;
        g->pred[dst->int_data] = src->int_data;
    }
}
/*  In each v-1 iterations, have to relax all the edges and 
    not just the edges originating from ith vertex  */
void graph_bellman_ford(graph_t *graph, int src)
{
    int i = 0, count;
    listNode    *node = NULL;
    graph->dist[src] = 0;
    for ( count = 1; count < graph->v; count++) { // v-1 iterations
        //  Run for each edge
        for (i = 0; i<=graph->v-1; i++) {
            node = graph->adj_list[i].head;
            while (node) {
                graph_relax(graph, graph->adj_list[src].head, node); 
                node = node->next;
            }
        }
    }
}

void print_path(graph_t *g, int dest)
{
    if (MINUS_INFINITY != g->pred[dest]) {
        print_path(g, g->pred[dest]);
    }
    printf("%d,  ",dest);
}
void practise_graphs(int tc, int argc, char * argv[])
{
    graph_t *graph = NULL, *cgraph = NULL;
    graph_t *wgraph = NULL, *w2cgraph = NULL;
    int paths = 0;
    int edges8[][3] =           // nov 7, noe = 8
    {   {0,1, 11}, {0,2, 12}, 
        {1, 3, 13},
        {4,1, 14}, {4, 5, 45}, 
        {5,2, 17},{5,6, 18},
        {6,4, 15}, {6,0, 16} }; 
    int edges9[][3] =           // nov = 9, noe = 14 
    {   {0, 1, 4}, 
        {1, 2, 8}, {1, 7, 11},
        {2, 3, 7}, {2, 8, 2}, {2, 5, 4},
        {3,4, 9},  {3, 5, 14},
        {4, 5, 10},
        {5, 6, 2}, 
        {6, 7, 1}, 
        {7, 0, 8}, {7, 8, 7},
        {8, 6, 6} };
    graph = create_graph(6);
    add_edge(graph, 5, 0, 50);
    add_edge(graph, 5, 2,52);
    add_edge(graph, 4, 0,40);
    add_edge(graph, 4,1,41);
    add_edge(graph, 2,3,23);
    add_edge(graph, 3,1,31);

    cgraph = create_graph(14);
    graph_set_offset(cgraph, 'm');
    add_cedge(cgraph, 'm', 'x',11);
    add_cedge(cgraph, 'm','r',5);
    add_cedge(cgraph, 'm', 'q', 4);
    add_cedge(cgraph, 'n','u',18);
    add_cedge(cgraph, 'n','q',14);
    add_cedge(cgraph, 'n','o',12);
    add_cedge(cgraph, 'o','v',29);
    add_cedge(cgraph, 'o','s',26);
    add_cedge(cgraph, 'o','r',25);
    add_cedge(cgraph, 'p','z',313);
    add_cedge(cgraph, 'p','s',36);
    add_cedge(cgraph, 'p','o',32);
    add_cedge(cgraph, 'q','t',47);
    add_cedge(cgraph, 'r','y',512);
    add_cedge(cgraph, 'r','u',58);
    add_cedge(cgraph, 's','r',65);
    add_cedge(cgraph, 'u','t',87);
    add_cedge(cgraph, 'v','x',911);
    add_cedge(cgraph, 'v','w',910);
    add_cedge(cgraph, 'w','z',1013);
    add_cedge(cgraph, 'y','v',129);

    wgraph = create_graph(8);
    graph_set_offset(wgraph, 's');
    add_cedge(wgraph, 's', 't', 6);
    add_cedge(wgraph, 's', 'y', 7);
    add_cedge(wgraph, 't', 'x', 5);
    add_cedge(wgraph, 't', 'z', -4);
    add_cedge(wgraph, 't', 'y', 8);
    add_cedge(wgraph, 'x', 't', -2);
    add_cedge(wgraph, 'y', 'x', -3);
    add_cedge(wgraph, 'y', 'z', 9);
    add_cedge(wgraph, 'z', 'x', 7);
    add_cedge(wgraph, 'z', 's', 2);


    switch (tc) {
        case 0:
            print_graph(cgraph);
            break;
        case 1: 
            graph = get_graph1(7, edges8, 8);
            //dfs(graph, 5);
            graph_dfs(graph);
            break;
        case 2: 
            if (argc) {
                graph_bfs(graph, atoi(argv[0]));
                printf("\n");
                //print_path(graph, atoi(argv[1]));
            }
            break;
        case 3: 
            //test_top_sort(graph, 0);
            printf("New topological Sort\n");
            graph_top_sort(cgraph, 1);
            break;
        case 4: 
            test_alien_dictionary(argc-3, argv+3);
            break;
        case 5: 
            //num_paths();
            paths = graph_num_paths(cgraph, char_vertex('p', cgraph), 
                                    char_vertex('v', cgraph));
            printf("Number of paths: %d\n", paths);
            break;
        case 6:
            graph_transpose(graph);
            break;
        case 7:
            print_graph(wgraph);
            graph_bellman_ford(wgraph, char_vertex(argv[0][0], wgraph));
            print_path(wgraph, char_vertex(argv[1][0], wgraph));
            break;
        case 8:
            graph = get_graph1(7, edges8, 8);
            print_graph(graph);
            graph_bfs(graph, 5);
            mother_vertex(graph);
            break;
        case 9:
            graph=get_graph1(9, edges9, 14);
            print_graph(graph);
            mst_prim(graph, 0);
            break;
        case 10:
            graph=get_graph1(9, edges9, 14);
            print_graph(graph);
            mst_kruskal(graph);
            break;
        case 11:
            printf("%s calling practice_ads() \n", __FUNCTION__);
            argc = argc - 3;
            argv = argv + 3;
            if (argc) { 
                practice_ads(atoi(argv[0]), argc-1,argv+1); 
            }
            break;
        case 12: 
            test_floyd_warshall();
            break;
        case 13:
            graph = get_graph1(7, edges8, 8);
            transitive_closure(graph);
            break;
        case 14:
            test_k_cores();
            break;
        case 15: 
            graph = get_graph1(7, edges8, 8);
            test_iterative_DFS(graph);
            break;
        case 16:
            if (argc >=2) {
                test_find_path_in_maze(atoi(argv[0]), atoi(argv[1]));
            }
            break;
        case 17: // April 2019
            test_hamiltonian_cycle();
            break;
        case 18: 
            test_graph_cycle();
            break;
        case 19:
            test_tsp();
            break;
        case 20: 
            test_stl();
            break;
        case 21:
            graph = get_graph1(7, edges8, 8);
            print_graph(graph);
            cout << " New funtion \n";
            test_dfs_bfs(graph, atoi(argv[0]));
            break;
        case 22: 
            int res ; 
            graph = get_graph1(7, edges8, 9);
            res = test_bipatriate_graph(graph);
            cout << (res ? "BiPatriate Graph" : " NOt a Biaptriate Graph");
        case 23: 
            test_dikjstra(atoi(argv[0]), atoi(argv[1]));
            break;
        case 24: 
            test_snake_n_ladder(atoi(argv[0]));
            break;
        case 25:
            test_kahnAlgo();
            break;
        case 26:
            test_tc();
            break;
        case 27: 
            test_knight_moves(atoi(argv[0]), atoi(argv[1]));
            break;
        default :
            break;
    };
    printf("\n");
}
void mother_vertex(graph_t  *graph)
{
    listNode    *node = NULL;
    queue_t     *que =  init_queue();
    int         dest = 0;
    int count = 0;
    int i = 0, s = 0, y =0;

    for ( i = 0 ; i < graph->v; i++) {
        s = i;
        count = 0;
        if ( NULL == graph || graph->adj_list[i].head == NULL) {
            continue;
        }
        for ( y = 0 ; y < graph->v; y++) {
            graph->color[y] = WHITE;
        }
        graph->color[s] = GREY;
        graph->pred[s] = MINUS_INFINITY;
        do {
            node = graph->adj_list[s].head;
            while(node) {
                dest = node->int_data;
                if (graph->color[dest] == WHITE) {
                    graph->color[dest] = GREY;
                    graph->pred[dest] = s;
                    enqueue(que, dest);
                }
                node = node->next;
            }
            graph->color[s] = BLACK;
            count++;
            s = dequeue(que);
        } while(s != -1);
        if ( count == graph->v) {
            printf("%s is :%d\n", __FUNCTION__, i);
            return;
        }
    }
}

/*  Dec 26th, 2018 Minimum SPanning Tree */

int get_prim_mst_min_key(graph_t *g, int* keys, int *mst)
{
    int res = 0, i;
    int min = LINFINITY;
    for ( i = 0 ; i < g->v; i++) {
        if (mst[i] == 0 && keys[i] < min) {
            min = keys[i];
            res = i;
        }
    }
    return res;
}
void mst_prim(graph_t   *g, int root)
{
    int     *mst = (int*)malloc(sizeof(int) * g->v);  // set to maintain MST
    int     *keys = (int*)malloc(sizeof(int) * g->v); // vertex keys
    int     *parent = (int*)malloc(sizeof(int) * g->v);// minimum spanning tree
    int     i = 0 ; 
    int     tmp = -1;
    listNode    *node = NULL;
    int     prev_parent = NIL;
    
    printf("MInimum Spanning Tree: ");
    for ( i = 0 ; i < g->v; i++) {
        keys[i] = LINFINITY;
        parent[i] = NIL; 
        mst[i] = 0;     // minimum spanning tree set is empty
    }
    keys[root] = 0;
    mst[root] = 1;      // root is present in mst

    for ( i = 0 ; i < g->v; i++) {
        tmp = get_prim_mst_min_key(g, keys, mst); 
        mst[tmp] = 1;      // root is present in mst
        parent[tmp] = prev_parent;
        prev_parent = tmp;
        node = g->adj_list[tmp].head;    
        printf(" %d ", tmp);
        while(node) {
           if (keys[node->int_data] > node->g_weight) {
               keys[node->int_data] = node->g_weight;
           }
           node = node->next;
        }
    }
}
/*  MST kruskal */
/*  SEt union operation 
    set:    array represntation of set
    size:   size of set 
    e1:     element1 
    e2:     element2
    self_set:   constant indicating element is in its own set   */
void set_union(int *uset, int size, int e1, int e2, int self_set)
{
    int i = 0, tmp;
    if (uset[e1] == uset[e2]) {
        if (uset[e1] == self_set) {
            //  each elem in their own set, put them in one
            uset[e1] = e1;
            uset[e2] = e1;
        } else {
            // same set already nothing to do
            ;
        }
    } else {
        if (uset[e1] == self_set) uset[e1] = uset[e2];
        else if (uset[e2] == self_set) uset[e2] = uset[e1];
        else {
            tmp = uset[e2];
            for ( i = 0; i < size; i++) { 
            // search for all the elements in set e2 and move to e1
                if (uset[i] == tmp) uset[i] = uset[e1];
            }
        }
    }
}
/*  check if the given edge forms a cycle. dest is present in node*/
int graph_edge_cycle(listNode   *node, int *mst, int src)
{
    if (mst[src] == mst[node->int_data] && 
            mst[src] != MINUS_INFINITY) return true;
    return false;
}

listNode*   get_kruskal_min_key(graph_t *g, int *mst)
{
    int min = LINFINITY; 
    listNode    *node = NULL, *tmpNode = NULL;
    int i = 0, src = 0;
    for ( i = 0; i < g->v; i++) { 
        node = g->adj_list[i].head;
        while (node) { 
            if (!node->picked && !graph_edge_cycle(node, mst, i)) {
                if (node->g_weight <= min) {
                    min = node->g_weight; 
                    tmpNode = node;
                    src = i;
                }
            }
            node = node->next;
        }
    }
    if(tmpNode) {
        set_union(mst, g->v, src, tmpNode->int_data, MINUS_INFINITY);
        printf("%d->%d,  ", src, tmpNode->int_data);
        tmpNode->picked = 1;
    }
    return tmpNode;
}
void mst_kruskal(graph_t    *g)
{
    int *mst = (int*)malloc(sizeof(int) * g->v);
    int i = 0;
    listNode    *node = NULL;

    for ( i = 0 ; i < g->v; i++) { 
        mst[i] = MINUS_INFINITY;
    }
    printf("\nKruskal:mst: \n ");
    for ( i = 0 ; i < g->v-1; i++) { 
        node = get_kruskal_min_key(g, mst);
    }
    printf("\n ");
}
/*      Jan 25th 2019 
        input: graph weight matrix  
        */
void floyd_warshall(int g[][NOV])
{
    int i, j , k;
    int tmp;
    int path[NOV][NOV];
    for (i = 0; i < NOV; i++) { 
        for ( j=0; j< NOV; j++) {
            path[i][j] = i; 
        }
    }
    for (k = 1; k <=NOV; k++) {
        for ( i = 0 ; i < NOV; i++) {
            for (j = 0; j < NOV; j++) {
                if (g[i][k-1] + g[k-1][j] < g[i][j]) {
                    g[i][j] = g[i][k-1] + g[k-1][j];
                    path[i][j]=k-1;
                } 
            }
        }
    }

    printf("%s result\n", __FUNCTION__);
    for ( i = 0 ; i < NOV; i++) { 
        printf("%d\t%d\t%d\t%d\t%d \n", 
                g[i][0], g[i][1], g[i][2], g[i][3], g[i][4]);
    }
    print_shortest_path_matrix(path);
}
void test_floyd_warshall(void)
{
    int g[][NOV] = {   { 0,3,8,IN,-4},
        { IN, 0, IN, 1,7},
        { IN, 4, 0, IN, IN},
        { 2, IN, -5, 0, IN}, 
        { IN, IN, IN, 6, 0}
    };
    floyd_warshall(g);
}
/*  The argument p is treated as int(*)[NOV], which means a pointer to an array
    of ints. The same can be achieved using int (*p)[NOV] 
    void print_shortest_path_matrix(int (*p)[NOV])
 */
void print_shortest_path_matrix(int p[][NOV])
{
    int i, j;
    int src, dest, nsrc;
    for ( i = 0 ; i < NOV; i++) {
        for ( j=0; j < NOV; j++) {
            if ( i != j) {
                nsrc = i; dest = j;
                printf("\n path from %d to %d: ", i, j);
                do {
                    src = nsrc;
                    printf("%d -> ", src);
                    nsrc = p[src][dest];
                }while (src != nsrc);
            }
        }
    }
}
#define SEV 7   
void tc(graph_t *g, int src, int tcm[][SEV])
{
    int i = src;
    listNode    *node = g->adj_list[src].head;
    g->start[i] = gl_time++;
    g->color[i] = GREY;
    while (node) {
        i = node->int_data;
        if (g->color[node->int_data] == WHITE) {
            g->pred[i] = src;
            tc(g, i, tcm);
        }
        tcm[src][i] = 1;
        node = node->next;
    }
    g->color[src] = BLACK;
    printf("%d , ", src);
    g->finish[src] = gl_time++;
}
void print_array2d(int  arr[][SEV])
{
    int i = 0,j;
    for (i = 0; i < SEV; i++) {
        for (j = 0 ; j < SEV; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
void graph_compute_tc(graph_t *g, int arr[][SEV])
{
    int i = 0, j;
    for (i = 0;i < g->v; i++) {
        j = i;  // There is a path from each j's pred to i
        while(g->pred[j] != MINUS_INFINITY) {
            arr[g->pred[j]][i] = 1;
            j = g->pred[j];
        }
    }
}
void transitive_closure(graph_t *g)
{
    listNode    *node = NULL;
    int         nov = g->v;
    int         src = 0, i;
    int         tcm[SEV][SEV];

    memset(tcm, 0, sizeof(tcm));
    for ( i = 0 ; i < g->v; i++) { 
        g->color[i] = WHITE;
    }
    printf("\n");
    // iterate throuh all the vertices
    for ( i = 0; i < nov; i++) {
        node = g->adj_list[i].head;
        if (g->color[i] == WHITE) {// if a vertex not covered yet, do DFS
            tc(g, i,tcm);
        }
    }
    printf("\n");
    graph_compute_tc(g,tcm);
    print_array2d(tcm);
}
void graph_k_cores(graph_t  *g, int core)
{
    int i, j;
    //int *degree = malloc(sizeof(int) * g->v);
    int degree[9] = {0};
    listNode    *node = NULL, *prev = NULL;

    memset(degree, 0 , sizeof(int) * g->v);
    for ( i = 0; i< g->v; i++) {
        node = g->adj_list[i].head;
        while (node) {
            degree[i]++;
            node = node->next;
        }
    }
    i=0;
    while (i < g->v) {
        if (degree[i] >0 && degree[i] < core) {
            degree[i] = 0;
            g->adj_list[i].head = NULL;
            for ( j = 0; j < g->v; j++) {
                node = g->adj_list[j].head;
                while (node) {
                    if (node->int_data == i) {
                        degree[j]--;
                        if (g->adj_list[j].head == node) {
                            g->adj_list[j].head = delete_node(node);
                        } else {
                            prev->next = delete_node(node);
                        }
                        print_graph_list(g->adj_list[j].head);
                        printf("\n");
                        break;
                    }
                    prev = node;
                    node = node->next;
                }
            }
            i = -1;
        }
        i++;
    }
    print_graph(g);
}
/*  Feb 2019    */
void test_k_cores()
{
    int edges[][3] = {
        {0, 1, 1}, {0, 2, 2}, 
        {1, 0, 10}, {1, 2, 12} , {1, 5, 15},
        {2, 0, 20}, {2, 1, 21} , {2, 3, 23}, {2, 4, 24}, {2, 5, 25} , 
        {2, 6, 26},
        {3, 2, 32}, {3, 4, 34} , {3, 6, 36}, {3, 7, 37},
        {4, 2, 42}, {4, 3, 43} , {4, 6, 46}, {4, 7, 47},
        {5, 1, 51}, {5, 2, 52} , {5, 6, 56}, {5, 8, 58},
        {6, 2, 62}, {6, 3, 63} , {6, 4, 64}, {6, 5, 65}, {6, 7, 67} , 
        {6, 8, 68},
        {7, 3, 73}, {7, 4, 74} , {7, 6, 76},
        {8, 5, 85}, {8, 6, 86} 
    };
    graph_t *g = get_graph1(9, edges, 34);
    graph_k_cores(g, 3);
}
/*  Feb 21, 2019    */
void test_iterative_DFS(graph_t *g)
{
    listNode *node = NULL, *prev;
    int i = 0, src;

    for ( i = 0; i < g->v; i++) {
        src = i;
        if (g->color[src] == WHITE) {
            push(src);
            g->color[src] = GREY;
            g->start[src] = gl_time++;

            node = g->adj_list[src].head;
            while( src != -1) {
                if (node) {
                    src = node->int_data;
                    if (g->color[src] == WHITE) {
                        push(src);
                        g->color[src] = GREY;
                        g->start[src] = gl_time++;
                        prev = node->next;
                        node = g->adj_list[src].head;
                    } else {
                        node = node->next;
                    }
                } else {
                    src = pop();
                    g->color[src] = BLACK;
                    node = prev;
                    printf("%d, ", src);
                }
            }
        }
    }
}
/*  March 2019 */
bool find_path(graph_t   *g, int src, int dest)
{
    bool retval = false;
    listNode    *node = NULL;
    if (g->color[src] == WHITE) {
        g->color[src] = GREY;
        node = g->adj_list[src].head;
        while (node) {
            if (g->color[node->int_data] == WHITE) {
                g->pred[node->int_data] = src;
                if (node->int_data == dest) return true;
                retval = find_path(g, node->int_data, dest);
                if (retval) return retval;
            }
            node = node->next;
        }
        g->color[src] = BLACK;
    }
    return false;
}
/*   March 2019  */
graph_t*    get_graph_from_matrix(int a[][MSIZE])
{
    graph_t *g = NULL;
    int     i = 0, j = 0;
    /*  Each square in the maze represent a vertex in a graph
        if a square is 1 and the neighboring squaaes are 1, there is
        an edge from this vertex to that vertex.
        While creating the graph based on this logic, we can 
        always look for squares down and right of the current 
        vertex being evaluated.
        And we need to create a undirected graph 
     */
    g = create_graph(MSIZE*MSIZE);
    for ( i = 0; i < MSIZE; i++) {
        for ( j = 0; j < MSIZE; j++) {
            if (a[i][j]) {
                if ((i < MSIZE-1) && a[i+1][j]) {
                    add_edge(g, i*MSIZE+j,(i+1)*MSIZE+j, 0);
                    // add back edge
                    add_edge(g, (i+1)*MSIZE+j,(i)*MSIZE+j, 0);

                }
                if ((j < MSIZE-1) && a[i][j+1]) {
                    add_edge(g, i*MSIZE+j,(i)*MSIZE+j+1, 0);
                    add_edge(g, (i)*MSIZE+j+1, i*MSIZE+j, 0);
                }
            }
        }
    }
    return g;
}
void find_path_in_maze(int   maze[][MSIZE], int src, int dest)
{
    listNode    *node = NULL;
    graph_t *g = get_graph_from_matrix(maze);
    int         grid[MSIZE][MSIZE] = {0};
    //print_graph(g);
    printf("src:%d to dest:%d\n", src, dest);
    if (find_path(g, src, dest)) {
        print_path(g,dest);
        printf("\n");
        get_gridof_path_in_maze(g, grid, dest, MSIZE);
        print_grid(grid, MSIZE);
    } else {
        printf("No Path found\n");
    }
    return; 
}
/*  March 2019  */
void test_find_path_in_maze(int src, int dest)
{
    /*int maze[][MSIZE] = {
                             {1,0,1,1,1},
                             {1,1,1,0,1},
                             {0,0,0,0,1},
                             {1,1,1,1,1},
                             };
    */
    int maze[MSIZE][MSIZE] = {
                             {1,0,1,0},
                             {1,1,1,1},
                             {0,1,0,0},
                             {1,1,1,1},
                             };
    find_path_in_maze(maze, src, dest);
}
void get_gridof_path_in_maze(graph_t *g, int grid[][MSIZE], 
        int dest, int ncol)
{
    int i = 0, j = 0;
    if (MINUS_INFINITY != g->pred[dest]) {
        get_gridof_path_in_maze(g, grid, 
                g->pred[dest],ncol );
    }
    i = dest/ncol;
    j = dest%ncol;

    grid[i][j] = 1;
}
void print_grid(int grid[][MSIZE], int ncol) 
{
    int i =0, j = 0;
    for ( i = 0; i < ncol; i++) {
        for ( j = 0; j < MSIZE; j++) {
            if (grid[i][j]) {
                printf(" # ") ;
            } else {
                printf(" , ") ;
            }
        }
        printf("\n");
    }
}

#define HC 5
int find_cycle(int v, mgraph_t  *g, int mg[][HC])
{
    int j = 0;
    if (g->color[v] == ! WHITE) 
        return 0;
    g->color[v] = GREY;
    //  once a node has been picked check its adjacenies
    for ( j = 0; j < g->v; j++) {
        if (mg[v][j]) {
            // vertex I has an adjacency to vertex J
            if (g->color[j] == WHITE) {
                find_cycle(j, g, mg);
            } else if (g->color[j] == GREY) {
                printf("Cycle found\n");
                return 1;
            }
        }
    }
    // All the adjacencies for this node have ben resolved. 
    g->color[v] = BLACK;
    printf("%d, ", v);
}

/*  April 2019  */
int find_cycle_wrapper(mgraph_t *g, int mg[][HC])
{
    int i = 0;
    for (i = 0; i < g->v; i++) {
        //  Pick a node if it has not been processed already
        if (g->color[i] == WHITE) {
            find_cycle(i, g, mg); 
        }
    }
}
//  April 2019
void test_graph_cycle()
{
    mgraph_t    *mg = NULL;
    int g1[5][5] = {        //  Has hamiltonian cycle
                   { 0, 1, 0, 1, 0},
                   { 1, 0, 1, 1, 1},
                   { 1, 0, 0, 0, 1},
                   { 1, 1, 0, 0, 1},
                   { 0, 1, 1, 1, 0},
    };

    int g2[5][5] = {        // has cycle but not the hamiltonian one
                            /*      0---1---2
                                    |  / \  |
                                    | /   \ |
                                    3       4    
                             */
                   { 0, 1, 0, 1, 0},
                   { 1, 0, 1, 1, 1},
                   { 0, 1, 0, 0, 1},
                   { 1, 1, 0, 0, 0},
                   { 0, 1, 1, 0, 0},
    };
    
    mg = allocate_mgraph(HC);
    find_cycle_wrapper(mg, g1);
}
/*  
 *  inputs: g1 - graph in matrix notation
 *          cycle -     array to maintain the hamiltonian cycle
 *          node_index  - index of the cuurent node
 */
int find_next_node_hc(int g1[][HC], int *cycle, int node_index)
{
    // The next node should satisfy following criteria
    //  It shhould have an edge from the current node. 
    //  It should not already be there in cycle.
    //  There should be an edge from the last node to first node.
    
    int curr_node = cycle[node_index];
    int i = 0, j = 0;

    // Traverse the adjancies of curr_node

    for ( i = 0; i < HC; i++) {
        if (g1[curr_node][i]) {// found an edge from current node to i
            // if current node is last edge should go to start
            if (node_index == HC-1) {
                if ( 0 == i) return 1;
            }
            // check ith node shouldn't be in cycle already
            for (j = 0; j <= node_index; j++) {
                if (cycle[j] == i) {
                    break;
                } else { 
                    if ( j == node_index) return i;
                    continue;
                }
            }
        }
    }
    return 0;
}
int*    find_hamiltonian_cycle_wrapper(int g1[][HC], mgraph_t   *gs)
{
    int     *cycle = (int*)malloc(sizeof(int) * gs->v);
    int     i = 0, curr_node = 0;
    memset(cycle, 0, gs->v * sizeof(int)); 

    for ( i = 0; i < gs->v-1; i++) {
        cycle[i] = curr_node;
        curr_node = find_next_node_hc(g1, cycle, i);
    }
    if (curr_node) {
        printf("Hamiltonian Cycle:");
        cycle[i] = curr_node;
        for ( i = 0; i < gs->v; i++) {
            printf("%d, ", cycle[i]);
        }
    }else { 
        printf("Hamiltonian Cycle not Found\n");
    }
}
void test_hamiltonian_cycle()
{
    mgraph_t    *mg = NULL;
    int g1[5][5] = {        //  Has hamiltonian cycle
                   { 0, 1, 0, 1, 0},
                   { 1, 0, 1, 1, 1},
                   { 1, 0, 0, 0, 1},
                   { 1, 1, 0, 0, 1},
                   { 0, 1, 1, 1, 0},
    };

    int g2[5][5] = {        // has cycle but not the hamiltonian one
                            /*      0---1---2
                                    |  / \  |
                                    | /   \ |
                                    3       4    
                             */
                   { 0, 1, 0, 1, 0},
                   { 1, 0, 1, 1, 1},
                   { 0, 1, 0, 0, 1},
                   { 1, 1, 0, 0, 0},
                   { 0, 1, 1, 0, 0},
    };
    
    mg = allocate_mgraph(5);
    find_hamiltonian_cycle_wrapper(g1, mg);
}

mgraph_t*   allocate_mgraph(int num)
{
    int i;
    mgraph_t    *mg = (mgraph_t*)malloc(sizeof(mgraph_t));
    mg->v       = num;
    mg->color   = (int*)malloc(num* sizeof(int));
    mg->pred    = (int*)malloc(num* sizeof(int));
    mg->start   = (int*)malloc(num* sizeof(int));
    mg->finish  = (int*)malloc(num* sizeof(int));
    for (i = 0; i < num; i++) {
        mg->color[i] = WHITE;
    }
    return mg;
}

//  May 2019
#define TSP 4
void tsp_mst(int g[][TSP], int nodes)
{
    int mst[TSP] = {0}; // Store the edges
    int set[TSP] = {0};
    int keys[TSP] = { LINFINITY};
    int tmp = g[0][0];
    int i, j, nedges=TSP-1 ;
    int tmpi, tmpj;
    mst[0] = 0; 
    // assume the first vertex as 0

    set[0] = 1; // 0th vertex in MST
    
    tmpi = 0;
    for ( ; nedges >=0; nedges--) {
        tmp = 0;

        // compute keys from tmpith vertex
        for ( i = 0; i < TSP; i++) {
            if (g[tmpi][i] && (keys[i] == 0 || keys[i] > g[tmp][i])) {
                keys[i] = g[tmpi][i];
            }
        }
        // Get next egde
        for ( i = 0; i < nodes; i++) {
            if ( set[i] != 1 && 
                       ( tmp == 0 || keys[i] < tmp)) {
                tmp = keys[i]; 
                tmpi = i;
            }
        }
        mst[TSP-nedges] = tmpi;
        set[tmpi] = 1;
    }
    for ( i = 0; i < TSP; i++) {
        printf( "%d \n",  mst[i]);
    }
}

void find_tsp(int g[][TSP], int nodes)
{
    printf("Travelling sales man\n");
    int *path = (int*) malloc(nodes * sizeof(int)); 
    int i = 0, j = 0; 
    tsp_mst(g, nodes);
}
void test_tsp()
{
    int nodes = TSP;
    int g1[TSP][TSP] = {        //  Has hamiltonian cycle
                   { 0, 10, 8, 20}, 
                   { 5, 0, 9, 10 },
                   { 6, 13, 0, 12 },
                   { 8, 8, 9, 0 }
    };

    find_tsp(g1, nodes);
}

void test_stl()
{
    //map<int, int> n1(pair<int, int>(1,10));
    map<int, int> n1;
    n1.insert(pair<int, int> (200, 10));
    n1[100] = 5;
    cout << n1[100]<<", " << n1[200] << "\n";
}
//  Aug 2019
void dfs2(graph_t   *g, int v)
{
    int         n_vertex;
    listNode    *node = NULL;
    if (g->color[v] == WHITE) {
        g->color[v] = GREY;
        node = g->adj_list[v].head;
        while (node) {
            n_vertex = node->int_data;
            if (g->color[n_vertex] == WHITE) { 
                dfs2(g, n_vertex);
            }
            node = node->next;
        }
        g->color[v] = BLACK;
        cout << v << "," ;
    }
}
void test_dfs_bfs( graph_t  *g, int v)
{
    // dfs 
    int nv = g->v;
    int vertex = v, i;
    listNode    *node = NULL;
    queue<listNode*> que;
    cout << " Breadth First search is: ";
    cout << vertex << "," ;
    node = g->adj_list[vertex].head; 
    if ( NULL == node) return ;
    que.push(node);
    g->color[vertex] = GREY;
    while (1) { 
        while (node) { 
            if (g->color [node->int_data] == WHITE) { 
                que.push(node);
                g->color[node->int_data] = GREY;
                cout << node->int_data << "," ;
            }
            node = node->next;
        }
        g->color[vertex] = BLACK;
        if (!que.empty()) {
            node = que.front();
            que.pop();
            vertex = node->int_data;
            node = g->adj_list[vertex].head; 
        } else break;
    }

    for ( i = 0; i < g->v; i++) g->color[i] = WHITE;
    cout << " Depth First Search is : " ;

    for ( i = 0; i < g->v; i++) {
        if (g->color[i] == WHITE) { 
            dfs2(g, i);
        }
    }
}
int test_bipatriate_graph(graph_t *g)
{
    vector<int> set1;
    int i;
    listNode    *node = NULL;

    if ( NULL == g) return 0;

    set1.resize(g->v);

    for ( i = 0; i < g->v; i++) {
        node = g->adj_list[i].head;
        g->color[i] = GREY;
        if (set1[i] == 0) set1[i] = 1;
        while (node) {
            if (set1[node->int_data] == set1[i] ){
                return 0;
            } else {
                set1[node->int_data] = (set1[i] == 1 ? 2 : 1);
            }
            node = node->next;
        }
    }
}

/*
void test_bfs_new()
{
    vector<vector<int>> g;
    vector(int> e1;
    for ( i = 1; i < 95; i++) { 
    e1 = { i+1, i+2, i+3, i+4, i+5, i+6 };
    
    g.push_back(e1);

}
*/
void print_graph_stl(vector<vector<edges> > g)
{
    int i, j;
    int v = g.size();
    for ( i = 0; i < v; i++) {
        cout << i << "-> " ;
        for ( j = 0; j < g[i].size(); j++) {
            cout << g[i][j].dest << "," ;
        }
        cout << "\n";
    }
}
void relax_edge(vector<vector<edges> > g, vector<int> pred, vector<int> dist, int u, int v)
{
    if ((dist[u] + g[u][v].weight) < dist[v]) {
        dist[v] = dist[u] + g[u][v].weight;
        pred[v] = u;
    }
}
void print_path_stl(vector<int> pred , int dest)
{
    if (LINFINITY != pred[dest]) {
        print_path_stl(pred, pred[dest] );
    }
    printf("%d,  ",dest);
}
struct edgeCompare {
    bool operator()(const edges& e1, const edges& e2) const
    {
        if (e1.weight < e2.weight) {
            return false;
        } else { 
            return true;
        }
    }
};
void test_dikjstra(int s, int dest)
{
    int i = 0, j;
    int u , v = 5;
    edges qe, tmpEdge;
    vector<vector<edges> > graph;
    priority_queue< edges, vector<edges> , edgeCompare > pq;
    vector<int> pred, dist;
    edges e[] = {
                        {0, 1, 10}, {0, 4,5}, {1, 2, 1},{1,4,2},
                        {2,3,4},{3,2,6},{3,0,7},
                        {4,3,2},{4,2,9},{4,1,3}
                       };
    
    graph.resize(v);
    pred.resize(v);
    dist.resize(v);
    for ( j = 0; j < v; j++) { 
        pred[j] = LINFINITY;
        dist[j] = LINFINITY;
    }

    dist[s] = 0;
    tmpEdge.src = s;
    tmpEdge.dest = s;
    tmpEdge.weight = dist[s];

    pq.push(tmpEdge);

    for( ; i < sizeof(e) / sizeof(edges); i++ ) {
        graph[e[i].src].push_back(e[i]); 
    }
    print_graph_stl(graph);
    cout << "\n";
    while (!pq.empty()) {
        qe = pq.top();
        u = qe.src;
        pq.pop();
        for ( j = 0; j < graph[u].size(); j++) {
            if ( dist[graph[u][j].dest] > dist[u] + graph[u][j].weight) {
                dist[graph[u][j].dest] = dist[u] + graph[u][j].weight;
                pred[graph[u][j].dest] = u; 
                tmpEdge.src = graph[u][j].dest;
                tmpEdge.dest = graph[u][j].dest;
                tmpEdge.weight = dist[graph[u][j].dest];
                pq.push(tmpEdge);
            }
        }
    }
    print_path_stl( pred, dest);
}

void test_snake_n_ladder(int dest)
{
    int N = 101;
    vector<vector<edges> > snl;
    unordered_map<int,  int> ladder, snake;
    edges tmpEdge;
    int src;
    queue<int> q;
    vector<int> color;
    int moves = 0;

    ladder[1] = 38;
    ladder[4] = 14; 
    ladder[9] = 31; 
    ladder[21] = 42;
    ladder[28] = 84;
    ladder[51] = 67;
    ladder[72] = 91;
    ladder[80] = 99;

    snake[17] = 7;
    snake[54] = 34;
    snake[62] = 19;
    snake[64] = 60;
    snake[87] = 36;
    snake[93] = 73;
    snake[95] = 75;
    snake[98] = 79;

    snl.resize(N);
    int i, j; 

    for ( i = 0; i < N; i++) {
        tmpEdge.src = i;
        for ( j = i+1; j <=i+6; j++) {
            tmpEdge.dest = j;
            if (ladder[j] || snake [j] ) {
                tmpEdge.dest = ladder[j] + snake [j];
            }
            snl[i].push_back(tmpEdge);
        }
    }
    color.resize(N);
    for ( j = 0; j < N; j++) {
        color[j] = WHITE;
    }
    print_graph_stl(snl);
    src = 0;
    q.push(src);
    color[src] = GREY; // Grey pushed 
    while ( !q.empty()) {
        src = q.front(); q.pop();
        moves++;
        for ( j = 0; j < snl[src].size(); j++) {
            if (color[snl[src][j].dest] == WHITE) {
                if (snl[src][j].dest == dest) {
                    cout << "Reached 100 in " << moves << "  moves\n"; 
                }
                q.push(snl[src][j].dest);
                color[snl[src][j].dest] = GREY;
            }
        }
    }
}
/*
 Kahn Algo for determining the topological sort 
 Identify the vertex with 0 indegree and put them in a queue. 
 Walk through all the adjacent edges and reduce in degree by one.
 check till queue is empty. 
 Since in the queue only those vertices are present which have an indegree of
 0, there will be no adjacency to these vertices from any other vertex*/
void test_kahnAlgo()
{
    int v = 8, i, j;
    vector<vector<edges> > graph;
    queue<int> q;
    vector<int> indegree;

    edges e[] = { {0,6,0},{1,2,0}, {1,4,0}, {1,6,0},
              {3,0,0}, {3,4,0}, {5,1,0},
              {7,0,0}, {7,1,0}};
    graph.resize(v);
    indegree.resize(v);

    for ( i = 0; i < sizeof(e) / sizeof(edges); i++) {
        graph[e[i].src].push_back(e[i]);
    }
   print_graph_stl(graph); 
   for ( i = 0 ; i < v; i++) {
       indegree[i] = 0;
   }
   // Determine the indegree of all the edges
   for ( i = 0; i < v; i++) {
       for ( j = 0; j < graph[i].size(); j++) {
           indegree[graph[i][j].dest]++;
       }
   }
   // insert the vertices with indegree 0 in a queue.
   for ( i = 0; i < v; i++) {
       if (indegree[i] ==0 ) { 
           q.push(i);
       }
   }
   // Till the queue is not empty
   while ( !q.empty()) {
       i = q.front(); q.pop();
       cout << i << ", " ;
       for ( j = 0; j < graph[i].size(); j++) {
           indegree[graph[i][j].dest]--;
           if ( indegree[graph[i][j].dest] == 0) q.push(graph[i][j].dest);
       }
   }
}

void print_2d(vector<vector<int> > &d){
    int i, j ;
    for ( i = 0; i < d.size(); i++) {
        for ( j = 0; j < d[i].size(); j++) {
            cout << d[i][j] << ", " ; 
        }
        cout << "\n"; 
    }
}
// Floyd Warshalls
void test_tc()
{
    int v = 5, nd = 0;
    vector<vector <edges> > graph;
    edges e[] = { 
            { 0, 1, 3}, {0, 2, 8}, {0, 4, -4},
            {1,3, 1}, {1,4,7},
            {2, 1, 4}, 
            {3,0,2}, {3, 2, -5},
            {4, 3, 6}};
    int i, j, k; 
    vector<vector <int> > d; // 2d array of shortest paths between different vs
    vector<vector <int> > dk; // 2d array of shortest paths through k-1
    d.resize(v);
    dk.resize(v);
    graph.resize(v);
    for ( i = 0; i < v; i++) { d[i].resize(v, LINFINITY); } 

    for ( i = 0; i < v; i++) {
        for ( j = 0; j < v; j++) { 
            if ( i!=j) d[i][j] = LINFINITY;
        }
    }
    for ( i = 0; i < sizeof(e) / sizeof(edges); i++) { 
        graph[e[i].src].push_back(e[i]);
        d[e[i].src][e[i].dest] = 1;
    }

    // Find shorest path beween i, j passing through 0-kth vertices.
    for ( k = 0; k < v; k++) {
        dk = d;
        for ( i = 0; i < v; i++) {
            for ( j = 0; j < v; j++) {
                nd = dk[i][k]+dk[k][j];
                d[i][j] = nd > dk[i][j] ? dk[i][j] : nd;
            }
        }
    }
    print_2d(d);
}

void test_knight_moves(int x, int y)
{
    int N = 8;
    int i, j = 0;
    vector< vector<int> > color;
    vector < vector<int> > nmoves;

    queue<Cell> que;
    Cell start(0,0), finish(x,y);
    Cell tmp, node;
    int cx[8] = {2, 2, -2, -2, 1, 1, -1,-1};
    int cy[8] = {1,-1, 1,  -1, 2,-2, 2,-2};
    int tmpx, tmpy;
    
    color.resize(N);
    nmoves.resize(N);

    for ( i = 0; i < N; i++) {
        color[i].resize(N);
        nmoves[i].resize(N);
        for (j=0; j < N; j++) {
            color[i][j] = WHITE;
            nmoves[i][j] = 0;
        }
    }
    nmoves[start.x][start.y] = 0;

    if (start == finish) { 
        cout << "No of moves:" << nmoves[start.x][start.y] ;
        return ;
    }

    que.push(start);  
    color[start.x][start.y] = GREY;
    while (!que.empty()) {
        node = que.front();
        que.pop();
        // Loop to consider the edges
        for ( j = 0; j < 8; j++) {
            tmpx = node.x + cx[j];
            tmpy = node.y + cy[j];
            tmp = Cell(tmpx, tmpy);
            if (tmp == finish) { 
                nmoves[tmpx][tmpy] = nmoves[node.x][node.y]+1;
                cout << "No of moves:" << nmoves[finish.x][finish.y] ;
                return;
            }
            if ( tmpx < N && tmpy < N && tmpx > -1 && tmpy > -1) {
                if (color[tmpx][tmpy] == WHITE) {
                    que.push(Cell(tmpx, tmpy));
                    nmoves[tmpx][tmpy] = nmoves[node.x][node.y]+1;
                    color[tmpx][tmpy] = GREY;
                }
            }
        }
        color[node.x][node.y] = BLACK;
    }
    cout << "\n";
}
