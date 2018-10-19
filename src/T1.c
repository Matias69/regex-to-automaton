#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a_graph.h"

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
	// check_input(argc, argv);
	// printf("todo ok!\n");

	graph *automaton;
	automaton = malloc(sizeof(graph));
	initialize_graph(automaton);
	insert_edge(automaton, 3,4);
	insert_edge(automaton, 2,4);
	insert_edge(automaton, 1,8);
	insert_edge(automaton, 7,3);

	print_graph(automaton);

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
