#ifndef __PARSER_H__
#define __PARSER_H__

#include "../headers/tokenization.h"
#include "../headers/automata.h"
#include "../headers/hash.h"

enum {PROGRAMA = 0,
	BLOCO,
	DECLARACAO,
	CONSTANTE,
	MAIS_CONST,
	VARIAVEL,
	MAIS_VAR,
	PROCEDIMENTO,
	COMANDO,
	MAIS_CMD,
	EXPRESSAO,
	TERMO,
	MAIS_TERMO,
	FATOR,
	MAIS_FATORES,
	CONDICAO,
	RELACIONAL	
};

void parser(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void constante(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void mais_const(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void variavel(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void mais_var(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void procedimento(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void prim_comando(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void comando(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void mais_cmd(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void expressao(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void termo(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void mais_fatores(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void mais_termos(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

void condicao(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable);

int error(FILE *_fd, char *_nextToken, char *_tokenType, Transition **tTable, Node **hTable, int *_numLines, FILE *_fout, Node ***foTable, Node ***fiTable, int pai, int seguidor, char *_followerType);

#endif
