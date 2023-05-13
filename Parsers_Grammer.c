#include "mpc.h"

/*

//A parser 'Adjective' to recognise descriptions
mpc_parser_t* Adjective = mpc_or(4,
	mpc_sym("wow"), mpc_sym("many"),
	mpc_sym("so"), mpc_sym("such")
 );
 
//A parser 'noun' to recognise things
mpc_parser_t* Noun = mpc_or(5,
	mpc_sym("lisp"), mpc_sym("language"),
	mpc_sym("book"), mpc_sym("build")
);

mpc_parser_t* Phrase = mpc_and(2, mpcf_strfold, Adjective, Noun, free);

mpc_parser_t* Doge = mpc_many(mpcf_strfold, Phrase);

*/

/*

mpc_parser_t* Adjective = mpc_new("adjective");
mpc_parser_t* Noun = mpc_new("noun");
mpc_parser_t* Phrase = mpc_new("phrase");
mpc_parser_t* Doge = mpc_new("doge");

mpca_lang(MPCA_LANG_DEFAULT,
	"											\
		adjective : \"wow\" | \"many\"			\
				  | \"so\"	| \"such\";			\
		noun	  : \"lisp\" | \"language\"		\
				  | \"book\" | \"build\";		\
		phrase	  : <adjective> <noun>;			\
		doge	  : <phrase>*;					\
	", 
	Adjective, Noun, Phrase, Doge);			
	
mpc_cleanup(4, Adjective, Noun, Phrase, Doge);

*/

//THE POLISH NOTATION GRAMMER

mpc_parser_t* Number = mpc_new("number");
mpc_parser_t* Operator = mpc_new("operator");
mpc_parser_t* Expr	= mpc_new("expr");
mpc_parser_t* Lispy = mpc_new("lispy");

mpca_lang(MPCA_LANG_DEFAULT, 
	"															\
		number		: /-?[0-9]+/;								\
		operator 	: '+' | '-' | '*' | '/';					\
		expr		: <number> | '(' <operator> <expr>+ ')';	\
		lispy		: /^/ <operator> <expr>+ /$/;				\
	",
	Number, Operator, Expr, Lispy, NULL);
	
mpc_cleanup(4 Number, Operator, Expr, Lispy);