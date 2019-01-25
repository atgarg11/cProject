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
// Creat an edge from src to dest. c if the graphs is for alphabets
void add_edge(graph_t   *g, int src, int dest, int weight)
{
    listNode    *tmp = NULL;
    /* the src and dest specified are not the vertices of the graph  */
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
    time = time+1;
    graph->dist[s] = time;
    graph->start[s] = time;
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
    graph->finish[s] = ++time;
    graph->color[s] = BLACK;
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
void practise_graphs(int tc, int argc, char * argv[])
{
    graph_t *graph = NULL, *cgraph = NULL;
    graph_t *wgraph = NULL, *w2cgraph = NULL;
    int paths = 0;
    int edges8[][3] = 
    {{0,1, 11}, {0,2, 12}, {1, 3, 13},{4,1, 14}, {6,4, 15},
        {6,0, 16}, {5,2, 17},{5,6, 18} };
    int edges9[][3] = 
    {{0, 1, 4}, {1, 2, 8}, {2, 3, 7}, {3,4, 9}, {4, 5, 10},
     {5, 6, 2}, {6, 7, 1}, {7, 0, 8}, {1, 7, 11},{2, 8, 2},
     {8, 6, 6}, {3, 5, 14}, {7, 8, 7}, {2, 5, 4}};
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
            dfs(graph, 5);
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
    int min = INFINITY;
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
    int     *mst = malloc(sizeof(int) * g->v);  // set to maintain MST
    int     *keys = malloc(sizeof(int) * g->v); // vertex keys
    int     *parent = malloc(sizeof(int) * g->v);// minimum spanning tree
    int     i = 0 ; 
    int     tmp = -1;
    listNode    *node = NULL;
    int     prev_parent = NIL;
    
    printf("MInimum Spanning Tree: ");
    for ( i = 0 ; i < g->v; i++) {
        keys[i] = INFINITY;
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
    int min = INFINITY; 
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
    int *mst = malloc(sizeof(int) * g->v);
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
    for (k = 1; k <=NOV; k++) {
        for ( i = 0 ; i < NOV; i++) {
            for (j = 0; j < NOV; j++) {
                g[i][j] = min(g[i][k-1] + g[k-1][j], g[i][j]);
            }
        }
    }
    printf("%s result\n", __FUNCTION__);
    for ( i = 0 ; i < NOV; i++) { 
        printf("%d\t%d\t%d\t%d\t%d \n", 
                g[i][0], g[i][1], g[i][2], g[i][3], g[i][4]);
        }
}
void test_floyd_warshall(void)
{
    int g[][NOV] = {   { 0,3,8,IN,-4},
        { IN, 0, IN, 1,7},
        { IN, 4, -5, 0, IN},
        { 2, IN, -5, 0, IN}, 
        { IN, IN, IN, 6, 0}
    };
    floyd_warshall(g);
}
