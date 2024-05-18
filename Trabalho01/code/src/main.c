#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "../headers/automata.h"

int main(int argc, char *argv[]){

	int **tTable = transition_table(NUM_STATES, MAX_CHAR_VAL);

	int _ret = 0;
	char _nextToken[64], _tokenType[32];

	FILE *_fileIn = fopen(argv[1], "r");
	FILE *_fileOut = fopen("tokenOutput.txt", "w+");

	while(1){
		_ret = tokenization(_fileIn, _nextToken, _tokenType, tTable);
		// manipulacao escreve a saida no arquivo de saida

		//fwrite(_outputText, sizeof(char), strlen(_outputText) - 1, _fileOut);
	} 

	fclose(_fileIn);
	fclose(_fileOut);
}
