#include<stdlib.h>
#include<string.h>

#include "../headers/tokenization.h"
#include "../headers/automata.h"

//int tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines)

void parser(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	// constante(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	// variavel(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	// procedimento(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	// comando(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);

	if(!strcmp(_nextToken,".")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	} else {
		//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	}
}

void constante(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	if(!strcmp(_tokenType,"CONST")){
		// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	} else {
		//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	}
	if(!strcmp(_tokenType,"id")){
		// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	} else {
		//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	}
	if(!strcmp(_nextToken, "=")){
		// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	} else {
		//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	}
	if(!strcmp(_tokenType,"int")){
		// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	} else {
		//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	}	
	// mais_const(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	if(!strcmp(_nextToken, ";")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	} else {
		//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	}
}

void mais_const(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	while(!strcmp(_nextToken,",")){
		// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		if(!strcmp(_tokenType, "id")){
			// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
		if(!strcmp(_nextToken, "=")){
			// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}	
		if(!strcmp(_tokenType,"int")){
			// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);	
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
	}
}

void variavel(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	if(!strcmp(_tokenType,"VAR")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		if(!strcmp(_tokenType, "id")){
			//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else { 
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines)
		}	
		//mais_var(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		if(!strcmp(_nextToken, ";")){
			//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
	}
}

void mais_var(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	while(!strcmp(_nextToken,",")){
		// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		if(!strcmp(_tokenType, "id")){
			// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
	}
}

void procedimento(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	while(!strcmp(_tokenType,"PROCEDURE")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		if(!strcmp(_tokenType, "id")){
			//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
		if(!strcmp(_nextToken, ";")){
			//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
		// constante(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		// variavel(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		// procedimento(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		// comando(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	
		if(!strcmp(_nextToken, ";")){
			//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
	}
}

void comando(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	if(!strcmp(_tokenType,"id")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines)
		if(!strcmp(_nextToken, ":=")){
			// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
		// expressao(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);	
	} else if(!strcmp(_tokenType, "CALL")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		if(!strcmp(_tokenType, "id")){
			//tokenizatio(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
	} else if(!strcmp(_tokenType, "BEGIN")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		//comando(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		while(!strcmp(_nextToken, ";")){
			//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
			//comando(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
		if(!strcmp(_tokenType,"END")){
			//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
	} else if(!strcmp(_tokenType, "IF")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		//condicao(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		if(!strcmp(_tokenType,"DO")){
			//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
		//comando(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	} else if(!strcmp(_tokenType, "WHILE")){
		// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		// condicacao(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		if(!strcmp(_tokenType, "DO")){
			// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines)
		}
		// comando(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	}
	
	return;
}

void mais_cmd(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	while(!strcmp(_nextToken, ";")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		//comando(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	}
}

void expressao(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	// operador unario
	if(!strcmp(_nextToken, "+") || !strcmp(_nextToken, "-")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	}
	// termo(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);

	//mais_termos(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
}

void termo(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	if(!strcmp(_tokenType,"id") || !strcmp(_tokenType,"int")){
		// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		// mais_fatores(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);

	} else if(!strcmp(_nextToken, "(")){
		// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		// expressao(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		if(!strcmp(_nextToken,")")){
			//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
		// mais_fatores(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	} else {
		//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	}

}

void mais_fatores(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	while(!strcmp(_nextToken, "*") || !strcmp(_nextToken,"/")){
		if(!strcmp(_tokenType,"id") || !strcmp(_tokenType,"int")){
			// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);

		} else if(!strcmp(_nextToken, "(")){
			// tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
			// expressao(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
			if(!strcmp(_nextToken,")")){
				//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
			} else {
				//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
			}
		} else {
			//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		}
	}
}

void mais_termos(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	while(!strcmp(_nextToken, "+") || !strcmp(_nextToken, "-")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		// termo(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	}
}

void condicao(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines){
	if(!strcmp(_tokenType, "ODD")){
		//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		//expressao(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
	} else if(/*primeiro("expressao",_tokenType)*/){
		//expressao(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
		switch((int) *_nextToken){
			case '=':
				//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
				//expressao(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
				break;
			case '<':
				//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
				//expressao(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
				break;
			case '>':
				//tokenization(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
				//expressao(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
				break;	
			default:
				//error(*_fd, *_nextToken, *_tokenType, **tTable, **hTable, *_numLines);
				break;	
		}	
	}
}
