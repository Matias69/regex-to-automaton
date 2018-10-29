#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a_graph.h"
#include "a_afd.h"

#define MAX_ARGS_LEN 3

#define OP_PAR 40
#define CL_PAR 41
#define STAR 42
#define POINT 46
#define UNDSCRE 95
#define VBAR 124
#define TILDE 126

void check_input(int, char*[]);
int check_input_len(int, int);
int check_input_elements(char*[]);
int check_regex_elements(char*[]);
int belongs_to_regex_symbol(char);
int belongs_to_sigma(char);

int main(int argc, char *argv[]){
	//check_input(argc, argv);
	printf("todo ok!\n");

	graph *automaton;
	graph *afd;
	//nodeSet *set = NULL, *set2 = NULL;

	automaton = malloc(sizeof(graph));
	afd = malloc(sizeof(graph));
	initialize_graph(afd);
	initialize_graph(automaton);

	insert_edge(automaton,1,'a',1);
	insert_edge(automaton,1,'b',1);
	insert_edge(automaton,1,'_',2);
	insert_edge(automaton,2,'a',3);
	insert_edge(automaton,3,'_',4);
	insert_edge(automaton,4,'b',5);
	insert_edge(automaton,5,'_',6);
	insert_edge(automaton,5,'_',2);
	insert_edge(automaton,6,'_',1);

	print_graph(automaton);

	/*
	addNodeSet(&set,1);
	addNodeSet(&set,2);
	addNodeSet(&set,3);
	addNodeSet(&set,4);

	addNodeSet(&set2,4);
	addNodeSet(&set2,3);
	addNodeSet(&set2,6);
	addNodeSet(&set2,1);

	printNodeSet(set);
	printf("\n");
	printNodeSet(set2);
	printf("\n");
	printf(stateInNodeSet(set,1)? "true" : "false");
	printf("\n");
	printf(stateInNodeSet(set2,10)? "true" : "false");
	printf("\n");
	printf(nodeSetComp(set,set2)? "true" : "false");
	printf("\n");
	//printf("%d\n", nodeSetSize(set));
	*/
	generate_afd(automaton);

	return 0;
}

void check_input(int argc, char *argv[]){
	if(!check_input_len(argc, MAX_ARGS_LEN)){
		printf("ERROR: cantidad de argumentos no valida, saliendo...\n");
		exit(0);
	}
	if(!check_input_elements(argv)){
		printf("ERROR: los elementos de la entrada no pertenecen a sigma, saliendo...\n");
		exit(0);
	}
	if(!check_regex_elements(argv)){
		printf("ERROR: los elementos de la regex no son correctos, saliendo...\n");
		exit(0);
	}
}

int check_input_len(int input_len, int max_input_len){
	if(input_len > max_input_len){ return 0; }
	return 1;
}

int check_input_elements(char *argv[]){
	char *input = argv[2];
	int len = strlen(input);
	for(int i=0; i<len; i++){	if(!belongs_to_sigma(input[i])) return 0;	}
	return 1;
}

int check_regex_elements(char *argv[]){
	char *regex = argv[1];
	int len = strlen(regex);
	for(int i=0; i<len; i++)
		if(!(belongs_to_sigma(regex[i]) || belongs_to_regex_symbol(regex[i])))
			return 0;
	return 1;
}

int belongs_to_regex_symbol(char c){
	if((c==POINT)||(c>=OP_PAR && c<=STAR)||(c==UNDSCRE)||(c==VBAR)||(c==TILDE)) return 1;
	return 0;
}

int belongs_to_sigma(char c){
	if((c>=48 && c<=57)||(c>=65 && c<=90)||(c>=97 && c<=122)) return 1;
	return 0;
}

void generate_afd(graph *g){
	 nodeSet *ns[V_MAX];
   int i = 0, j = 0;
   edgenode *en, *aux1;
	 alphabet *al = NULL, *aux2;


   for(i = 0; i < V_MAX; i++){
     ns[i] = NULL;
   }

   //-----------------------------------------------------------
	 for(i = 0; i < V_MAX; i++){
     en = g->edges[i];
		 while(en != NULL){
			 addLetter(&al,en->transition);
			 en = en->next;
		 }
	 }
	 pritnAlphabet(al);
   //-----------------------------------------------------------

	 for(i = 0; i < V_MAX; i++){
     en = g->edges[i];
     //while(en != NULL){

     //}
   }

}
