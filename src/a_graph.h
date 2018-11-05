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

struct edgenode{
    int y;
    char transition;
    struct edgenode *next;
};
typedef struct edgenode edgenode;

struct graph{
    edgenode *edges[V_MAX+1];
    int out_degree[V_MAX+1];
    int in_degree[V_MAX+1];
    int nvertices;      // sirve de algo??
    int nedges;
    int s;
    int f;
};

typedef struct graph graph;

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

int last_closed_parenthesis(int* p){
    int max_index = 0;

    for(int i=0; i<V_MAX; i++){
        //printf("buscando cl_par = %d\n", p[i]);
        if(i>max_index && p[i]!=0)
            max_index = i;
    }
    return max_index;
}

int get_op_parenthesis(int* p, int cl_par){
    for(int i=0; i<V_MAX; i++){
        if(p[i]==p[cl_par])
            return i;
    }
    return -1;
}

int next_state_available(graph* g, int except){
    for (int i=1; i<=V_MAX; i++)
        if(g->edges[i] == NULL && g->in_degree[i] == 0 && i!=except && i!=1)
            return i;
    return -1;
}

void initialize_array(int* arr, int len){
	for(int i=0; i<len; i++) arr[i] = 0;
}

void refresh_final_state(graph* g){
    if(g->edges[1] == NULL) return;
    int s = g->s;
    edgenode* aux = g->edges[s];
    int marked[V_MAX];
    initialize_array(marked, V_MAX);

    while(g->edges[aux->y]){
        edgenode* next = g->edges[aux->y];
        if(marked[next->y] == 1) break;
        marked[aux->y] = 1;
        aux = g->edges[aux->y];
    }
    g->f = aux->y;
}

// int search_state_of_previous(graph* g, int from, char previous){
// printf("from=%d     previous=%c\n", from, previous);
//
//     edgenode* aux = g->edges[from];
//     nodo* marked = NULL;
//     int state = from;
//     while(aux){
//         printf("TODO OK CON LAS COLAS???\n");
//         enqueue(state, &marked);
//         imprimirCola(marked);
//         printf("TODO OK !!!!\n");
//         if(aux->transition == previous) return state;
//
//         if(g->edges[aux->y] == NULL){
//             printf("ERROR???\n");
//             int backtracking = dequeue(&marked);
//             aux = g->edges[backtracking];
//             aux = aux->next;
//             printf("backtracking=%d\n", aux->y);
//             search_state_of_previous(g, aux->y, previous);
//         }
//         state = aux->y;
//         printf("->current_state=%d\n", state);
//         //printf("->next-edge=%d\n", g->edges[aux->y]->y);
//         show_graph(g);
//         aux = g->edges[aux->y];
//         printf("okk????\n");
//     }
//     printf("salió !!");
//     return -1;
// }

void regex_to_afnd(graph *g,int from, int to, char* regex, int index, int* parenthesis, int par_num){
    char current = regex[index];

    if(g->s == 0){
        g->s = from;
        g->f = to;
    }else{
        refresh_final_state(g);
    }

    if(current == '\0') return;

    switch (current){
        case POINT:{
            int aux = next_state_available(g, to);

            regex_to_afnd(g, to, aux, regex, ++index, parenthesis, par_num);
            break;
        }
        case VBAR:
            regex_to_afnd(g, from, to, regex, ++index, parenthesis, par_num);
            break;
        case STAR:{
            int prev_index = index - 1;
            if(regex[prev_index] == CL_PAR){
                int cl = last_closed_parenthesis(parenthesis);
                int op = get_op_parenthesis(parenthesis, cl);

                insert_edge(g, op, UNDSCRE, cl);
                insert_edge(g, cl, UNDSCRE, op);
            }else{
                insert_edge(g, from, UNDSCRE, to);
                insert_edge(g, to, UNDSCRE, from);
            }

            regex_to_afnd(g, from, to, regex, ++index, parenthesis, par_num);
            break;
        }
        case OP_PAR:{
            par_num++;
            parenthesis[from] = par_num;

            regex_to_afnd(g, from, to, regex, ++index, parenthesis, par_num);
            break;
        }
        case CL_PAR:{
            parenthesis[to] = par_num;
            par_num--;

            regex_to_afnd(g, from, to, regex, ++index, parenthesis, par_num);
            break;
        }
        default:{
            int aux = next_state_available(g, to);
            insert_edge(g, from, UNDSCRE, aux);
            int aux2 = next_state_available(g, to);
            insert_edge(g, aux, current, aux2);
            insert_edge(g, aux2, UNDSCRE, to);

            regex_to_afnd(g, from, to, regex, ++index, parenthesis, par_num);
        break;
        }
    }
}
