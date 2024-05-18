#include<stdio.h>
#include<string.h>

#include "../headers/automata.h"
#include "../headers/tokenization.h"


const int _finalStates[24] = {0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1};


// Processo de tokenizacao
//
// _nextToken e _tokenType tem tamanhos predefinidos e retornam as informacoes da cadeia reconhecida
//
int tokenization(FILE *_fd, char *_nextToken, char *_tokenType, int **tTable, int *_numLines){
	int _state = q0;
	char _nextChar = 0;
	
	int _tokenSize = 0;

	while(!_finalStates[_state] && (_nextChar = fgetc(_fd)) != EOF){
		transition(&_state, _nextChar, _nextToken, &_tokenSize, _numLines, tTable);
		
		// checa se o estado eh valido, i.e., se o caractere lido eh valido
		if(_state == -1){
			//erro: caractere invalido
			_nextToken[_tokenSize] = '\0';
			strcpy(_tokenType, "erro_char_desconhecido");
			return 0;
		}

		// verifica o tamanho do token
		if(_tokenSize > MAX_TOKEN_SIZE){
			// erro: token excedeu o limite
			_nextToken[_tokenSize] = '\0';
			strcpy(_tokenType, "erro_max_token_size");
			return 0;
		}

	}

	if(_finalStates[_state]){
		// acao do estado final
		_nextToken[_tokenSize++] = '\0';
		state_action(_state, _nextToken, _tokenSize, _tokenType, _fd);
		return 1;
	} else if(_state == q0){
		// sucesso -> arquivo inteiro foi lido com sucesso
		return 2;
	} else {
		//erro, fim inesperado de arquivo
		return -1;
	}
}

void state_action(int _state, char *_nextToken, int _tokenSize, char *_tokenType, FILE *_fd){
	switch(_state){
		// reconheceu um id
		case q3:
			_nextToken[_tokenSize - 1] = '\0';
			strcpy(_tokenType,"id");
			fseek(_fd, -1,SEEK_CUR);
			break;

		// reconheceu um inteiro
		case q5:
			if(_tokenSize > 1) _nextToken[_tokenSize - 1] = '\0';
			strcpy(_tokenType,"int");
			fseek(_fd, -1,SEEK_CUR);
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
			_nextToken[_tokenSize - 1] = '\0';
			strcpy(_tokenType,"simb_men");
			fseek(_fd, -1,SEEK_CUR);
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
			_nextToken[_tokenSize - 1] = '\0';
			strcpy(_tokenType,"simb_mai");
			fseek(_fd, -1,SEEK_CUR);
			break;
		
		// reconheceu ":="
		case q22:
			strcpy(_tokenType,"simb_atr");
			break;

		// reconheceu ':' -> erro
		case q23:
			_nextToken[_tokenSize - 1] = '\0';
			strcpy(_tokenType,"erro_simb_estranho");
			fseek(_fd, -1,SEEK_CUR);
			break;
	}
}	
