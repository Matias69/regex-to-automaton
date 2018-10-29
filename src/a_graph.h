#include <stdlib.h>
#include <stdbool.h>
#define V_MAX 100

typedef struct {
    int y;     /*adjancency info*/
    char transition;
    struct edgenode *next;
} edgenode;

typedef struct {
    edgenode *edges[V_MAX+1];
    int out_degree[V_MAX+1];
    int in_degree[V_MAX+1];
    int nvertices;
    int nedges;
} graph;

void initialize_graph(graph *g){
    int i;
    g -> nvertices = 0;
    g -> nedges = 0;
    for (i=1; i<=V_MAX; i++) g->out_degree[i] = 0;
    for (i=1; i<=V_MAX; i++) g->in_degree[i] = 0;
    for (i=1; i<=V_MAX; i++) g->edges[i] = NULL;
}

void insert_edge(graph *g, int x, char t, int y){
    edgenode *p;
    p = malloc(sizeof(edgenode));
    p->transition = t;
    p->y = y;
    p->next = g->edges[x];

    g->edges[x] = p;
    g->out_degree[x]++;
    g->in_degree[y]++;
    g->nedges++;
}

void print_graph(graph *g){
    edgenode *p;

    int n = g->nedges;
    printf("n = %d\n", n);

    for(int i=1; i<=V_MAX; i++){
        p = g->edges[i];
        while(p != NULL){
            printf("%d -> %d (%c)\n", i, p->y, p->transition);
            p = p->next;
        }
    }
}
