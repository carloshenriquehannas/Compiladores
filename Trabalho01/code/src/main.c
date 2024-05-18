#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../headers/automata.h"
#include "../headers/tokenization.h"

int main(int argc, char *argv[]){
	/*
	if(argv[1] == NULL){
		printf("\nErro: entrada incorreta.\nO arquivo deve ser executado da forma:\n./tokenizer (nome_do_arquivo)\n\n");
		exit(-1);
	}
	*/
	int **tTable = transition_table(NUM_STATES, MAX_CHAR_VAL);

	int _ret = 0;
	int _numLines = 0;
	char _nextToken[64], _tokenType[32];

	//FILE *_fileIn = fopen(argv[1], "r");
	FILE *_fileIn = fopen("teste.txt", "r");
	if(_fileIn == NULL){
		printf("\nErro na abertura do arquivo.\nCertifique-se de que o arquivo se encontra no diretirio.\n");
		fclose(_fileIn);
		exit(-1);
	}
	FILE *_fileOut = fopen("tokenOutput.txt", "w");
	if(_fileOut == NULL){
		printf("\nErro na abertura do arquivo de escrita.\nTente novamente.\n");
		fclose(_fileOut);
		exit(-1);
	}

	while(1){
		_ret = tokenization(_fileIn, _nextToken, _tokenType, tTable, &_numLines);
		switch(_ret){
			case -1:
				fputs("ERRO: fim inesperado de arquivo\n",_fileOut); 
				printf("\nErro: o arquivo foi terminado inseperadamente.\n");	

				free_table(tTable);
				fclose(_fileIn);
				fclose(_fileOut);
				
				exit(-1);
			case 0:
				// escreve o erro
				fputs(_nextToken, _fileOut);
				fputs(" , ", _fileOut);
				fputs(_tokenType, _fileOut);
				//fputs(" linha: %d",_fileOut);
				fputs("\n",_fileOut);
				break;
			case 1:
				// escreve o token e seu tipo
				fputs(_nextToken, _fileOut);
				fputs(" , ", _fileOut);
				fputs(_tokenType, _fileOut);
				fputs("\n",_fileOut);
				break;
			case 2:
				free_table(tTable);
				fclose(_fileIn);
				fclose(_fileOut);
				return 0;	
			}
	} 
}
