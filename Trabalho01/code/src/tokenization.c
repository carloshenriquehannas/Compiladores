#include<stdio.h>

#define MAX_TOKEN_SIZE 64

int _finalStates[26] = {0,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1};

// Processo de tokenizacao
//
// _nextToken e _tokenType tem tamanhos predefinidos e retornam as informacoes da cadeia reconhecida
//
int tokenization(FILE *_fd, char *_nextToken, char *_tokenType){
	int _state = 0; // mudar para q0	
	char _nextChar; 
	fread(&_nextChar, sizeof(char), 1, _fd);
	
	int _tokenSize = 0;

	while(_nextChar != EOF && !_finalStates[_state]){
		//_state = transition(_state, _nextChar);
		if(_state == -1){
			//error_procedure()
			return -1;
		}

		// guarda o caractere lido
		_nextToken[_tokenSize] = _nextChar;
		_tokenSize++;
		
		// verifica o tamanho do token
		if(_tokenSize > MAX_TOKEN_SIZE){
			// erro: token excedeu o limite
			return -1;
		}

		// le o proximo caractere
		fread(&_nextChar, sizeof(char), 1, _fd);
	}
	_nextToken[_tokenSize + 1] = '\0';

	if(_finalStates[_state]){
		// acao do estado final
		return 0;
	} else {
		//erro, fim inesperado de arquivo
		return -1;
	}
}

void state_action(int _state, char *_tokenType){
	switch(_state){
	
	
	
	}
}	
