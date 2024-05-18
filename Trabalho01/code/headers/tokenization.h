#ifndef __TOKENIZATION_H__
#define __TOKENIZATION_H__

#include<stdio.h>

// Funcao que coordena a analise lexica
int tokenization(FILE *_fd, char *_nextToken, char *_tokenType, int **tTable);

// Acoes tomadas pelos estados finais
void state_action(int _state, char *_tokenType);

#endif
