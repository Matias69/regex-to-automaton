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
    int s;
    int f;
} graph;

void initialize_graph(graph *g){
    int i;
    g -> nvertices = 0;
    g -> nedges = 0;
    g->s = 0;
    g->f = 0;
    for (i=1; i<=V_MAX; i++) g->out_degree[i] = 0;
    for (i=1; i<=V_MAX; i++) g->in_degree[i] = 0;
    for (i=1; i<=V_MAX; i++) g->edges[i] = NULL;
}

void insert_edge(graph *g, int x, char t, int y){
    edgenode* p;
    p = malloc(sizeof(edgenode));
    p->transition = t;
    p->y = y;
    p->next = NULL;

    edgenode* aux = g->edges[x];
    if(aux){
        while(aux->next)
            aux = aux->next;
        aux->next = p;
    }else{
        g->edges[x] = p;
    }

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

int next_state_available(graph* g, int except){
    for (int i=1; i<=V_MAX; i++)
        if(g->edges[i] == NULL && g->in_degree[i] == 0 && i!=except && i!=1)
            return i;
    return -1;
}

void refresh_final_state(graph* g){
    if(g->edges[1] == NULL) return;
    int s = g->s;
    printf("updating f: s = %d\n", s);
    edgenode* aux = g->edges[s];
    while(g->edges[aux->y]){
        printf("recorriendo... %d\n", aux->y);
        aux = g->edges[aux->y];
    }
    printf("final state? = %d\n", aux->y);
    g->f = aux->y;
}

void regex_to_afnd(graph *g,int from_state, int to_state, char* regex, int index, int* parenthesis, int par_num){
    char current = regex[index];


    if(current == '\0') return;

    int from = from_state;
    int to = to_state;

    if(g->s == 0){
        g->s = from;
        g->f = to;
    }else{
        refresh_final_state(g);
    }

    printf("current = %c\n", current);
    printf("from = %d\n", from);
    printf("to = %d\n", to);

    switch (current){
        case POINT:{
            int aux = next_state_available(g, to);

            show_graph(g);
            printf("---------------\n");

            regex_to_afnd(g, to, aux, regex, ++index, parenthesis, par_num);
            break;
        }
        case VBAR:
            show_graph(g);
            printf("---------------\n");

            regex_to_afnd(g, from, to, regex, ++index, parenthesis, par_num);
            break;
        case STAR:{
            int prev_index = index -1;
            if(regex[prev_index] == CL_PAR){
                printf("PREVIOUS = %c\n",regex[prev_index]);
                int cl = last_closed_parenthesis(parenthesis);
                int op = get_op_parenthesis(parenthesis, cl);

                printf("open = %d\nclose = %d\n", op, cl);

                insert_edge(g, op, UNDSCRE, cl);
                insert_edge(g, cl, UNDSCRE, op);
            }else{
                insert_edge(g, from, UNDSCRE, to);
                insert_edge(g, to, UNDSCRE, from);
            }
            //int aux = next_state_available(g, to);

            show_graph(g);
            printf("---------------\n");

            regex_to_afnd(g, from, to, regex, ++index, parenthesis, par_num);
            break;
        }
        case OP_PAR:{
            par_num++;
            parenthesis[from] = par_num;

            //int aux = next_state_available(g, to);

            show_graph(g);
            printf("---------------\n");

            regex_to_afnd(g, from, to, regex, ++index, parenthesis, par_num);
            break;
        }
        case CL_PAR:{
            parenthesis[to] = par_num;
            par_num--;
            //int aux = next_state_available(g, to);

            show_graph(g);
            printf("---------------\n");

            regex_to_afnd(g, from, to, regex, ++index, parenthesis, par_num);
            break;
        }
        default:{

            int aux = next_state_available(g, to);
            insert_edge(g, from, UNDSCRE, aux);
            int aux2 = next_state_available(g, to);
            insert_edge(g, aux, current, aux2);
            insert_edge(g, aux2, UNDSCRE, to);

            refresh_final_state(g);

            show_graph(g);
            printf("---------------\n");

            regex_to_afnd(g, from, to, regex, ++index, parenthesis, par_num);
        break;
        }
    }
}
int last_closed_parenthesis(int* p){
    int max_index = 0;

    for(int i=0; i<V_MAX; i++){
        printf("buscando cl_par = %d\n", p[i]);
        if(i>max_index && p[i]!=0)
            max_index = i;
    }
    printf("encontrado?? = %d\n", max_index);
    return max_index;
}

int get_op_parenthesis(int* p, int cl_par){
    for(int i=0; i<V_MAX; i++){
        if(p[i]==p[cl_par])
            return i;
    }
    return -1;
}
