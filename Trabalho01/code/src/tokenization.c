#include<stdio.h>
#include<string.h>

#include "../headers/automata.h"
#include "../headers/tokenization.h"

#define MAX_TOKEN_SIZE 64

const int _finalStates[24] = {0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1};


// Processo de tokenizacao
//
// _nextToken e _tokenType tem tamanhos predefinidos e retornam as informacoes da cadeia reconhecida
//
int tokenization(FILE *_fd, char *_nextToken, char *_tokenType, int **tTable){
	int _state = q0; // mudar para q0
	int _numLines = 1;	
	char _nextChar; 
	fread(&_nextChar, sizeof(char), 1, _fd);
	
	int _tokenSize = 0;

	while(_nextChar != EOF && !_finalStates[_state]){
		//_state = transition(&_state, _nextChar, _nextToken, &_tokenSize, &_numLines, tTable);
		
		// checa se o estado eh valido, i.e., se o caractere lido eh valido
		if(_state == -1){
			
			//error_procedure()
			return 0;
		}

		// guarda o caractere lido
		_nextToken[_tokenSize] = _nextChar;
		_tokenSize++;
		
		// verifica o tamanho do token
		if(_tokenSize > MAX_TOKEN_SIZE){
			// erro: token excedeu o limite
			return 0;
		}

		// le o proximo caractere
		fread(&_nextChar, sizeof(char), 1, _fd);
	}
	_nextToken[_tokenSize + 1] = '\0';

	if(_finalStates[_state]){
		// acao do estado final
		state_action(_state, _tokenType);
		return 0;
	} else {
		//erro, fim inesperado de arquivo
		return -1;
	}
}

void state_action(int _state, char *_tokenType){
	switch(_state){
		// reconheceu um id
		case q3:
			strcpy(_tokenType,"id");
			break;

		// reconheceu um inteiro
		case q5:
			strcpy(_tokenType,"int");
			break;

		// reconheceu '.'
		case q6:
			strcpy(_tokenType,"simb_pf");
			break;

		// reconheceu ','
		case q7:
			strcpy(_tokenType,"simb_virg");
			break;

		// reconheceu '/'
		case q8:
			strcpy(_tokenType,"simb_div");
			break;
		
		// reconheceu '*'
		case q9:
			strcpy(_tokenType,"simb_mult");
			break;

		// reconheceu '+'
		case q10:
			strcpy(_tokenType,"simb_add");
			break;

		// reconheceu '-'
		case q11:
			strcpy(_tokenType,"simb_sub");
			break;

		// reconheceu ';'
		case q12:
			strcpy(_tokenType,"simb_pv");
			break;

		// reconheceu '='
		case q13:
			strcpy(_tokenType,"simb_eq");
			break;

		// reconheceu '<'
		case q15:
			strcpy(_tokenType,"simb_men");
			break;
		
		// reconheceu "<="
		case q16:
			strcpy(_tokenType,"simb_meneq");
			break;
	
		// reconheceu "<>"
		case q17:
			strcpy(_tokenType,"simb_dif");
			break;

		// reconheceu ">="
		case q19:
			strcpy(_tokenType,"simb_maieq");
			break;
	
		// reconheceu '>'
		case q20:
			strcpy(_tokenType,"simb_mai");
			break;
		
		// reconheceu ":="
		case q22:
			strcpy(_tokenType,"simb_atr");
			break;

		// reconheceu ':' -> erro
		case q23:
			strcpy(_tokenType,"erro_simb_estranho");
			break;
	}
}	
