#include <stdlib.h>
#include <stdbool.h>
#define V_MAX 10

typedef struct {
    int y;     /*adjancency info*/
    int weight;
    struct edgenode *next;
} edgenode;

typedef struct {
    edgenode *edges[V_MAX+1];
    int degree[V_MAX+1];
    int nvertices;
    int nedges;
    bool directed;
} graph;

void initialize_graph(graph *g, bool directed){
    int i;                          /* contador */
    g -> nvertices = 0;
    g -> nedges = 0;
    g -> directed = directed;
    for (i=1; i<=V_MAX; i++) g->degree[i] = 0;
    for (i=1; i<=V_MAX; i++) g->edges[i] = NULL;
}

void insert_edge(graph *g, int x, int y, bool directed){
    edgenode *p;
    p = malloc(sizeof(edgenode));

    p->weight = 0;
    p->y = y;
    p->next = g->edges[x];

    g->edges[x] = p;

    g->degree[x] ++;

    if(directed == false)
        insert_edge(g, y, x, true);
    else
        g->nedges++;
}

void print_graph(graph *g){
    edgenode *p;

    for(int i=1; i<=g->nvertices; i++){
        printf("%d: ", i);
        p = g->edges[i];
        while(p != NULL){
            printf(" %d", p->y);
            p = p->next;
        }
        printf("\n");
    }
}
