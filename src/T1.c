#include<stdio.h>
#include<stdlib.h>

#MAX_ARGS_LEN 2

boolean check_input(int, int);

int main(int argc, char *argv[]){
	if(check_input(argc, MAX_ARGS_LEN)){
		printf("True!\n");
	}else{
		printf("False!!\n");
	}

	return 0;
}

boolean check_input(int input_len, int max_input_len){
	if(input_len > max_input_len){ return false; }
	return true;
}
