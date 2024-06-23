#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../headers/automata.h"
#include "../headers/hash.h"
#include "../headers/parser.h"

#define NUM_NAO_TERMINAIS 17

int main(int argc, char *argv[]){

	if(argv[1] == NULL){
		printf("\nErro: entrada incorreta.\nO arquivo deve ser executado da forma:\n./parser (nome_do_arquivo)\n\n");
		exit(-1);
	}

	Transition **tTable = transition_table(NUM_STATES, MAX_CHAR_VAL);

	Node **hTable = init_table();

	Node ***_foTable = init_followers();	

	Node ***_fiTable = init_firsts();

	int _numLines = 1;
	char _nextToken[64], _tokenType[32];

	// Abre os arquivos a serem utilizados

	FILE *_fileIn = fopen(argv[1], "r");
	//FILE *_fileIn = fopen("teste_a.txt", "r");
	if(_fileIn == NULL){
		printf("\nErro na abertura do arquivo.\nCertifique-se de que o arquivo se encontra no diretirio.\n");
		fclose(_fileIn);
		exit(-1);
	}
	FILE *_fileOut = fopen("output.txt", "w");
	if(_fileOut == NULL){
		printf("\nErro na abertura do arquivo de escrita.\nTente novamente.\n");
		fclose(_fileOut);
		exit(-1);
	}


	// Analisador Sintatico
	parser(_fileIn, _nextToken,_tokenType, tTable, hTable, &_numLines, _fileOut, _foTable, _fiTable);


	free_table(tTable);
	free_htable(hTable);
	fclose(_fileIn);
	fclose(_fileOut);
}
