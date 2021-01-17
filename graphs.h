#ifndef GRAPHS_H_
#define GRAPHS_H_

#define EDGE 3        // edge structure, 3 elements src - dst, weight
#define WHITE 1
#define GREY    2
#define BLACK   3

#define CHAR_INDEX(c) ((c)-'a')
#define INDEX_CHAR(i) ((i)+'a')

#define NOV 5   // Number of vertices
#define TWO 2
#define MI MINUS_INFINITY
#define IN  0xFF

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

typedef struct mgraph_t_ {
    int v;
    int *color;
    int *pred;
    int *start;
    int *finish;
}mgraph_t;

typedef struct edges_ {
    int src, dest;
    int weight;
}edges;

class Cell {
    public: 
        int x, y;
    public: 
        Cell(int x, int y) : x(x), y(y){}
        Cell(): x(0), y(0) {}
        bool operator==(const Cell& to) { 
            if (this->x == to.x && this->y == to.y) 
                return true;
            return false;
        }
};
void practise_graphs(int tc, int argc, char * argv[]);
/*      Practice Problems   */
void mother_vertex(graph_t  *graph);
void mst_prim(graph_t   *g, int root);
void mst_kruskal(graph_t *graph);
void floyd_warshall(int graph[][NOV]);
void test_floyd_warshall(void);
void print_shortest_path_matrix(int p[][NOV]);
void transitive_closure(graph_t *);
void test_k_cores();
void test_iterative_DFS(graph_t *g);

#define     MSIZE 4
bool        find_path(graph_t   *g, int src, int dest);
graph_t*    get_graph_from_matrix(int a[][MSIZE]);
void        find_path_in_maze(int   maze[][MSIZE], int src, int dest);
void        test_find_path_in_maze(int src, int dest);
void        print_grid(int grid[][MSIZE], int ncol) ;
void        get_gridof_path_in_maze(graph_t *g, int grid[][MSIZE], 
        int dest, int ncol);

void        test_hamiltonian_cycle();
void        test_graph_cycle();
mgraph_t*   allocate_mgraph(int num);
void        test_stl();
void        test_dfs_bfs(graph_t   *g, int);

void        test_tsp();
int         test_bipatriate_graph(graph_t *g);
void        test_dikjstra(int s, int dest);
void        test_snake_n_ladder(int a);
void        test_kahnAlgo();
void        test_tc();
void        test_knight_moves(int x, int y);
#endif
