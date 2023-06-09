#include <stdio.h>
#include "mpc.h"

#ifdef _WIN32   //ensures the code runs on multiple systems
static char buffer[2048];
//static char input[2048];	//this is a buffer of size 2048 that is to take the user input
char* readline(char* prompt){
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	
	char* cpy = malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1] ="\0";
	return cpy;	
}

void add_history(char* unused){}

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main (int argc, char** argv){
	
	//The Polish Notaion
	/* create the parsers */
	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr	= mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");
	
	/* and then define the parsers with the following language */
	mpca_lang(MPCA_LANG_DEFAULT, 
		"															\
			number		: /-?[0-9]+/;								\
			operator 	: '+' | '-' | '*' | '/';					\
			expr		: <number> | '(' <operator> <expr>+ ')';	\
			lispy		: /^/ <operator> <expr>+ /$/;				\
		",
		Number, Operator, Expr, Lispy);
	
	puts("Lispy version 0.0.0.0.1");
	puts("Press Ctrl+C to exit.");
	
	while(1){
		char* input = readline("Lispy> ");
		add_history(input);
		
		/* this will attempt to parse the user input */
		mpc_result_t r;
		if(mpc_parse("<stdin>", input, Lispy, &r)){
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);		
		}else{
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		
		free(input);
		
	}
	
/*	
	while(1){ // this is an infinite while loop
		fputs("Lispy> ", stdout);
		fgets(input, 2048, stdin);
		
		printf("No you are a %s", input);
		
		
	}
*/	
	mpc_cleanup(4, Number, Operator, Expr, Lispy); //undefine and delete the parsers
	
	return 0;
	
}

