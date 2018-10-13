#include<stdio.h>
#include<stdlib.h>

#define MAX_ARGS_LEN 3

int check_input(int, int);

int main(int argc, char *argv[]){
	if(check_input(argc, MAX_ARGS_LEN)){
		printf("True!\n");
	}else{
		printf("False!!\n");
	}

	return 0;
}

int check_input(int input_len, int max_input_len){
	if(input_len > max_input_len){ return 0; }
	return 1;
}
