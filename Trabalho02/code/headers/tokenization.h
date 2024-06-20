#ifndef __TOKENIZATION_H__
#define __TOKENIZATION_H__

#include<stdio.h>
#include "../headers/automata.h"
#include "../headers/hash.h"

#define MAX_TOKEN_SIZE 62

// Funcao que coordena a analise lexica
int tokenization(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines);

// Acoes tomadas pelos estados finais
void state_action(int _state, char *_nextToken, int _tokenSize, char *_tokenType, FILE *_fd, Node **hTable);

#endif
