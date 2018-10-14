#include<stdio.h>
#include<stdlib.h>

#define MAX_ARGS_LEN 3

void check_input(int, char*[]);
int check_input_len(int, int);
int check_input_elements(char*[]);
int belongs_to_sigma(char);

int main(int argc, char *argv[]){
	//check_input(argc, argv);

	printf("salida: %c\n", belongs_to_sigma(argv[2][0]));

	return 0;
}

void check_input(int argc, char *argv[]){
	if(!check_input_len(argc, MAX_ARGS_LEN)){
		printf("ERROR: cantidad de argumentos no valida, saliendo...\n");
		exit(0);
	}
}
int check_input_len(int input_len, int max_input_len){
	if(input_len > max_input_len){ return 0; }
	return 1;
}

int check_input_elements(char *argv[]){

	return 1;
}

int belongs_to_sigma(char c){
	if((c>=48 && c<=57)||(c>=65 && c<=90)||(c>=97 && c<=122)) return 1;
	return 0;
}
