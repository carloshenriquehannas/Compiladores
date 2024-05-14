#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){

	int _ret = 0;
	char *_outputText;
	char _nextToken[64], _tokenType[32];

	FILE *_fileIn = fopen(argv[1], "r");
	FILE *_fileOut = fopen("tokenOutput.txt", "w+");

	while((_ret = tokenization(_fileIn, _nextToken, _tokenType)) != -1){
		// falta processar a string _outputText	
		fwrite(_outputText, sizeof(char), strlen(_outputText) - 1, _fileOut);
	} 

}
