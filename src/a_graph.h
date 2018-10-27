#include <stdlib.h>
#include <stdbool.h>

#define V_MAX 100

#define OP_PAR 40
#define CL_PAR 41
#define STAR 42
#define POINT 46
#define UNDSCRE 95
#define VBAR 124
#define TILDE 126

typedef struct {
    int y;
    char transition;
    struct edgenode *next;
} edgenode;

typedef struct {
    edgenode *edges[V_MAX+1];
    int out_degree[V_MAX+1];
    int in_degree[V_MAX+1];
    int nvertices;      // sirve de algo??
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

void show_graph(graph *g){
    edgenode *p;
    for(int i=1; i<=V_MAX; i++){
        p = g->edges[i];
        while(p != NULL){
            printf("%d -%c-> %d\n", i, p->transition, p->y);
            p = p->next;
        }
    }
}

void cat_exp(graph *g, int last_state, char exp, char symbol){
    switch (symbol){
        case POINT:
            insert_edge(g, last_state, exp, ++last_state);
            break;
        case VBAR: break;
        case STAR: break;

    }

}
