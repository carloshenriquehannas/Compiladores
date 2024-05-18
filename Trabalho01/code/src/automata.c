#include <stdlib.h>
#include<stdio.h>
#include<ctype.h>

#include "../headers/automata.h"

	
// Função para criar a tabela de transições
int** transition_table(int _numStates, int _numChars) {

    // Aloca a matriz dinamicamente
    int **token = (int **)malloc(NUM_STATES * sizeof(int *));
    int i, j;  // Declarando as variáveis i e j fora dos loops
    for (i = 0; i < NUM_STATES; i++) {
        token[i] = (int *)malloc(MAX_CHAR_VAL * sizeof(int));
    }

    // Inicializa a matriz
    for (i = 0; i < NUM_STATES; i++) {
        for (j = 0; j < MAX_CHAR_VAL; j++) {
        	token[i][j] = -1;
        }
    }

    // define algumas transicoes mais gerais
    for (i = 0; i < MAX_CHAR_VAL; i++) {
	// define transicoes para inteiros
	if(isalpha(i)){
		// leitura de caracteres em q0 e q2	
		token[q0][i] = q2;
		token[q2][i] = q2;
	} else if(isdigit(i)){
		// leituras de digitos em q0, q2 e q4
		token[q0][i] = q4;
    		token[q2][i] = q2;
		token[q4][i] = q4;
	} else {
		// atribuicao do 'outro' em q2 e q4
		token[q2][i] = q3;
		token[q4][i] = q5;
	}

	// atribuicao do outro em q1, q14, q18 e q21
	token[q1][i] = q1;
	token[q14][i] = q15;
	token[q18][i] = q20;
	token[q21][i] = q23;
    }

    // Transicoes especificas

    // Para q0
    token[q0][43] = q10;  // '+'
    token[q0][45] = q11;  // '-'
    token[q0][32] = q0;   // ' '
    token[q0][60] = q14;  // '<'
    token[q0][62] = q18;  // '>'
    token[q0][61] = q13;  // '='
    token[q0][123] = q1;  // '{'
    token[q0][10] = q0;   // '\n'
    token[q0][47] = q8;   // '/'
    token[q0][9] = q0;    // '\t'
    token[q0][59] = q12;  // ';'
    token[q0][58] = q21;  // ':'
    token[q0][46] = q6;  // '.'
    token[q0][44] = q7;  // ','
    token[q0][48] = q5;  // '0'

    // Para q1
    token[q1][125] = q0;  // '}'

    // Para q14
    token[q14][61] = q16; // '='
    token[q14][62] = q17;  // '>'

    // Para q18
    token[q18][61] = q19; // '='

    // Para q21
    token[q21][61] = q22; // '='

    return token;
}

void free_table(int **table){
	for(int i = 0; i < NUM_STATES; i++){
		free(table[i]);
	}
	free(table);
}


void transition(int *_state, char _nextChar, char *_nextToken,int *_tokenSize, int *_numLines, int **tTable){
		if(_nextChar > 127){
			// erro -> caractere invalido
			// como o caractere 0 eh sempre invalido, todas as transicoes funcionarao da mesma forma
			// i.e., ele nao afetara o reconhecimento de uma cadeia e ainda sera detectado como um caractere invalido
			*_state = tTable[*_state][0];
		} else {
	
			*_state = tTable[*_state][(int)_nextChar];	

			// verifica se o caractere eh comentario/char nao imprimivel
			if(*_state == q1  || !isprint(_nextChar)|| _nextChar == ' ' || _nextChar == '}' || _nextChar == '{'){
				if(_nextChar == '\n'){
				       	(*_numLines)++;
				}
				return;
			}
			
			_nextToken[*_tokenSize] = _nextChar;
			(*_tokenSize)++;

			return;
		}
}

























