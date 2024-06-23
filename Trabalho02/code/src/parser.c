#include<string.h>
#include<stdlib.h>

#include "../headers/tokenization.h"
#include "../headers/automata.h"
#include "../headers/parser.h"
#include "../headers/hash.h"

// Os procedimentos para cada regra seguem basicamente um mesmo modelo:
//
// Eles comparam com terminais especificos, guardando a ultima linha onde uma atribuicao foi bem sucedida (para fins de relato de erro)
//
// ou
//
// Eles chamam algum outro procedimento


// O tratamento de erro tambem eh basicamente o mesmo, com excessao do ponto final

int last_correct_line = 1;

void parser(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de programa -> bloco .
	//
	// regras de bloco -> declaracao comando
	//
	//regras de declaracao -> constante variavel procedimento
	//

	tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
	constante(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
	variavel(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
	procedimento(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
	prim_comando(_fd, _nextToken, _tokenType, tTable, hTable, _numLines,  _fout, foTable, fiTable);

	if(!strcmp(_nextToken,".")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
	} else {
		if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, BLOCO, -1, "simb_pv")){
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "o arquivo terminou inesperadamente, faltando simbolo de fim do programa");
			fprintf(_fout,"\n");
			return;
		}
	}
}

void constante(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de constante
	if(!strcmp(_tokenType,"CONST")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		if(!strcmp(_tokenType,"id")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "identificador faltando em constante");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, CONSTANTE, -1, "simb_eq")) return;
		}
		if(!strcmp(_nextToken, "=")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "simbolo de atribuicao faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, CONSTANTE, -1, "int"))return;
		}
		if(!strcmp(_tokenType,"int")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "inteiro faltando em atribuicao");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, CONSTANTE, -1, "simb_pv"))return;
		}	
		mais_const(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		if(!strcmp(_nextToken, ";")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "ponto e virgula faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, CONSTANTE,-1, NULL))return;
		}
	}
}

void mais_const(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de mais_const
	while(!strcmp(_nextToken,",")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		if(!strcmp(_tokenType, "id")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "identificador faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, CONSTANTE, -1, "simb_eq"))return;
		}
		if(!strcmp(_nextToken, "=")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "simbolo de atribuicao faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, CONSTANTE, -1, "int"))return;
		}	
		if(!strcmp(_tokenType,"int")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "inteiro faltando em atribuicao");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, MAIS_CONST,-1, NULL))return;
		}
	}
}

void variavel(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de variavel
	if(!strcmp(_tokenType,"VAR")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		if(!strcmp(_tokenType, "id")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else { 
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "identificador faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, VARIAVEL, MAIS_VAR, NULL))return;
		}	
		mais_var(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		if(!strcmp(_nextToken, ";")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "simbolo de ponto e virgula faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, VARIAVEL, -1, NULL))return;
		}
	}
}

void mais_var(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de mais_var
	while(!strcmp(_nextToken,",")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		if(!strcmp(_tokenType, "id")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "identificador faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, MAIS_VAR, -1, NULL))return;
		}
	}
}

void procedimento(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de procedimento
	while(!strcmp(_tokenType,"PROCEDURE")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		if(!strcmp(_tokenType, "id")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "identificador faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, PROCEDIMENTO, -1, "simb_pv"))return;
		}

		if(!strcmp(_nextToken, ";")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "simbolo de ponto e virgula faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable,PROCEDIMENTO, BLOCO, NULL))return;
		}
		
		// regras de bloco -> declaracao comando -> constante variavel procedimento comando
		constante(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		variavel(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		procedimento(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		prim_comando(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
	
		if(!strcmp(_nextToken, ";")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "simbolo de ponto e virgula faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, PROCEDIMENTO, -1, NULL))return;
		}
	}
}


void prim_comando(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras do primeiro comando
	if(!strcmp(_tokenType, "BEGIN")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		comando(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		mais_cmd(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		if(!strcmp(_tokenType,"END")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "identificador faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, COMANDO, -1, NULL))return;
		}
	} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "a seção de comandos deve ser iniciada pela estrutura BEGIN ... END. Se você não estava escrevendo um comando, certifique-se de que os delimitadores das regiões de declaração estão corretos (VAR, CONST, PROCEDURE)");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, COMANDO, -1, NULL))return;
	
	}
}

void comando(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de comando
	if(!strcmp(_tokenType,"id")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		if(!strcmp(_nextToken, ":=")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "simbolo de atribuicao faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, COMANDO, EXPRESSAO, NULL))return;
		}

		expressao(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);	

		if(!strcmp(_nextToken, ";")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "simbolo de ponto e virgula faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, COMANDO, -1, NULL))return;
		}

	} else if(!strcmp(_tokenType, "CALL")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		if(!strcmp(_tokenType, "id")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "identificador faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, COMANDO,-1,NULL))return;
		}

		if(!strcmp(_nextToken, ";")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "simbolo de ponto e virgula faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, COMANDO, -1, NULL))return;
		}

	} else if(!strcmp(_tokenType, "BEGIN")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		comando(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		mais_cmd(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		if(!strcmp(_tokenType,"END")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "identificador faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, COMANDO, -1, NULL))return;
		}

	} else if(!strcmp(_tokenType, "IF")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		condicao(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		if(!strcmp(_tokenType,"THEN")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "comando 'THEN' faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, COMANDO, COMANDO, NULL))return;
		}

		comando(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

	} else if(!strcmp(_tokenType, "WHILE")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		condicao(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		if(!strcmp(_tokenType, "DO")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "comando 'DO' faltando");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, COMANDO, COMANDO, NULL))return;
		}

		comando(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
	}
	
	return;
}

void mais_cmd(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de mais_cmd
	while(search(fiTable[COMANDO],_tokenType)){
		comando(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
	}
}

void expressao(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de expressao

	// operador unario
	if(!strcmp(_nextToken, "+") || !strcmp(_nextToken, "-")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
	}

	termo(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

	mais_termos(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
}

void termo(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de termo -> fator mais_fatores
	if(!strcmp(_tokenType,"id") || !strcmp(_tokenType,"int")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		mais_fatores(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

	} else if(!strcmp(_nextToken, "(")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		expressao(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		if(!strcmp(_nextToken,")")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "')' esperado");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, TERMO, MAIS_FATORES, NULL))return;
		}

		mais_fatores(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

	} else {
		fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
		fprintf(_fout, "expressao esperada faltando (inteiro, identificador, '(expressao)')");
		fprintf(_fout,"\n");
		error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, TERMO, MAIS_FATORES, NULL);
	}

}

void mais_fatores(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de mais_fatores
	while(!strcmp(_nextToken, "*") || !strcmp(_nextToken,"/")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
		// regras de fator
		if(!strcmp(_tokenType,"id") || !strcmp(_tokenType,"int")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		} else if(!strcmp(_nextToken, "(")){
			last_correct_line = *_numLines;
			tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

			expressao(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

			if(!strcmp(_nextToken,")")){
				last_correct_line = *_numLines;
				tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
			} else {
				fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
				fprintf(_fout, "')' esperado");
				fprintf(_fout,"\n");
				if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, FATOR, MAIS_FATORES, NULL))return;
			}

		} else {
			fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
			fprintf(_fout, "expressao esperada faltando (inteiro, identificador, '(expressao)')");
			fprintf(_fout,"\n");
			if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, MAIS_FATORES, FATOR, NULL))return;
		}
	}
}

void mais_termos(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de mais_termos
	while(!strcmp(_nextToken, "+") || !strcmp(_nextToken, "-")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		termo(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);
	}
}

void condicao(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	// regras de condicao 
	//
	// condicao -> ODD expressao
	// condicao -> expressao relacional expressao
	//
	// relacional -> simbolos terminais relacionais
	//
	
	if(!strcmp(_tokenType, "ODD")){
		last_correct_line = *_numLines;
		tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		expressao(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

	} else if(search(fiTable[EXPRESSAO], _tokenType)){

		expressao(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

		switch((int) _nextToken[0]){
			case '=':
				last_correct_line = *_numLines;
				tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

				expressao(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

				break;
			case '<':
				last_correct_line = *_numLines;
				tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

				expressao(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

				break;
			case '>':
				last_correct_line = *_numLines;
				tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

				expressao(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable);

				break;	
			default:
				fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
				fprintf(_fout, "esperava operador relacional");
				fprintf(_fout,"\n");
				if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, CONDICAO, EXPRESSAO, NULL))return;
				break;	
		}	
	} else {
		fprintf(_fout,"Erro sintatico na linha %d: ", last_correct_line);
		fprintf(_fout, "esperava operador condicao");
		fprintf(_fout,"\n");
		if(error(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable, CONDICAO, -1, NULL))return;
	}
}

int error(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable, int pai, int seguidor, char *_followerType){
	while(1){
		if(_followerType != NULL && strcmp(_tokenType,_followerType)){ 
			return 0;
		} else if (seguidor != -1 && search(fiTable[seguidor], _tokenType)){
			return 0;
		} else if (pai != -1 && search(foTable[pai], _tokenType)){
			return 1;
		}else{ 
			if(tokenization(_fd, _nextToken, _tokenType, tTable, hTable, _numLines, _fout, foTable, fiTable)== 2){
				fprintf(_fout, "O compilador encontrou um erro do qual nao conseguiu se recuperar\n");
				exit(-1);				
			}
		}

	}
	if((_followerType != NULL && !strcmp(_tokenType,_followerType))|| (seguidor != -1 && search(fiTable[seguidor], _tokenType))){
		return 0;
	} else {
		return 1;
	}
}
