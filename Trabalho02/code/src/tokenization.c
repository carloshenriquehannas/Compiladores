#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "../headers/automata.h"
#include "../headers/tokenization.h"
#include "../headers/hash.h"


const int _finalStates[NUM_STATES] = {0,0,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,0,0,0,0,1,1,1,1,1,0};


// Processo de tokenizacao
//
// _nextToken e _tokenType tem tamanhos predefinidos e retornam as informacoes da cadeia reconhecida
//
int tokenization(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable){
	int _state = q0;
	char _nextChar = 0;
	
	int _tokenSize = 0;

	while(!_finalStates[_state] && (_nextChar = fgetc(_fd)) != EOF){
		transition(&_state, _nextChar, _nextToken, &_tokenSize, _numLines, tTable);
		
		// checa se o estado eh valido, i.e., se o caractere lido eh valido
		if(_state == -1){
			//erro: caractere invalido
			_nextToken[_tokenSize] = '\0';
			fprintf(_fout,"Erro lexico na linha %d: caractere invalido %s\n", *_numLines, _nextToken);
			_state = q0;
			_nextChar = 0;
	
			_tokenSize = 0;
			continue;
		}

		// verifica o tamanho do token
		if(_tokenSize > MAX_TOKEN_SIZE){
			// erro: token excedeu o limite
			_nextToken[_tokenSize] = '\0';
			fprintf(_fout,"Erro lexico na linha %d: identificador %s ultrapassou o limite de caracteres %d\n", *_numLines, _nextToken,MAX_TOKEN_SIZE);
			_state = q0;
			_nextChar = 0;
	
			_tokenSize = 0;
			return 0;
		}

	}

	if(_finalStates[_state]){
		// acao do estado final
		_nextToken[_tokenSize++] = '\0';
		state_action(_state, _nextToken, _tokenSize, _tokenType, _fd, hTable, _nextChar, _numLines, _fout);
		return 1;
	} else if(_state == q0){
		// sucesso -> arquivo inteiro foi lido com sucesso
		_nextToken[0] = '\0';
		_tokenType[0] = '\0';
		return 2;
	} else {
		fprintf(_fout,"Erro: fim inesperado de arquivo. Confira se os comentarios sao em linha unica e se estao corretamente fechados, ou se o arquivo possui ponto final\n");
		//erro, fim inesperado de arquivo
		exit(-1);
	}
}

void state_action(int _state, char *_nextToken, int _tokenSize, char *_tokenType, FILE *_fd, Node **hTable, char _nextChar, int *_numLines, FILE *_fout){
	switch(_state){
		// reconheceu um id
		case q3:
			_nextToken[_tokenSize - 1] = '\0';
			
			// busca se a palavra eh reservada
			if(search(hTable, _nextToken)){
				strcpy(_tokenType,_nextToken);
			} else {
				strcpy(_tokenType,"id");
			}
			// corrige o cursor do arquivo -> caractere lookahead
			if(_nextChar == '\n') (*_numLines)--;
			fseek(_fd, -1,SEEK_CUR);
			break;

		// reconheceu um inteiro
		case q5:
			if(_tokenSize > 1) _nextToken[_tokenSize - 1] = '\0';
			strcpy(_tokenType,"int");
			// corrige o cursor do arquivo -> caractere lookahead (com excecao do zero)
			if(_nextChar == '\n') (*_numLines)--;
			fseek(_fd, -1,SEEK_CUR);
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

			// corrige o cursor do arquivo -> caractere lookahead
			if(_nextChar != '\n') (*_numLines)--;
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

			// corrige o cursor do arquivo -> caractere lookahead
			if(_nextChar == '\n') (*_numLines)--;
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
			fprintf(_fout,"Erro lexico na linha %d: caractere invalido %s\n", *_numLines, _nextToken);
			// corrige o cursor do arquivo -> caractere lookahead
			if(_nextChar == '\n') (*_numLines)--;
			fseek(_fd, -1,SEEK_CUR);
			break;
		
		// reconheceu numero real -> erro
		case q28:
			if(_tokenSize > 1) _nextToken[_tokenSize - 1] = '\0';
			strcpy(_tokenType,"erro_num_real");
			fprintf(_fout,"Erro lexico na linha %d: numeros reais %s nao sao aceitos pela linguagem \n", *_numLines, _nextToken);
			// corrige o cursor do arquivo -> caractere lookahead 
			if(_nextChar == '\n') (*_numLines)--;
			fseek(_fd, -1,SEEK_CUR);
			break;

		// reconheceu numero real mal formatado -> erro
		case q29:
			if(_tokenSize > 1) _nextToken[_tokenSize - 1] = '\0';
			strcpy(_tokenType,"erro_real_mal_format");
			fprintf(_fout,"Erro lexico na linha %d: numero real malformatado nao eh aceito pela linguagem %s\n", *_numLines, _nextToken);
			// corrige o cursor do arquivo -> caractere lookahead 
			if(_nextChar == '\n') (*_numLines)--;
			fseek(_fd, -1,SEEK_CUR);
			break;

		// reconheceu -> '('
		case q30:
			strcpy(_tokenType, "simb_ap");
			break;

		// reconheceu -> ')'
		case q31:
			strcpy(_tokenType, "simb_fp");
			break;
		
		// reconheceu -> '.'
		case q32:
			_nextToken[_tokenSize - 1] = '\0';
			strcpy(_tokenType,"simb_pf");

			// corrige o cursor do arquivo -> caractere lookahead
			if(_nextChar == '\n') (*_numLines)--;
			fseek(_fd, -1,SEEK_CUR);
			break;

	}
}	
