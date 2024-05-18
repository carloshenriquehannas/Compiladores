#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>

#include "../headers/automata.h"

// Função para criar a tabela de transições
int** transition_table(int _numStates, int _numChars) {
    // Aloca a matriz dinamicamente
    int **token = (int **)malloc(_numStates * sizeof(int *));
    int i, j;  // Declarando as variáveis i e j fora dos loops
    for (i = 0; i < _numStates; i++) {
        token[i] = (int *)malloc(_numChars * sizeof(int));
    }

    // Inicializa a matriz
    for (i = 0; i < _numStates; i++) {
        for (j = 0; j < _numChars; j++) {
        	token[i][j] = -1;
        }
    }

    // define algumas transicoes mais gerais
    for (i = 0; i < _numStates; i++) {
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
    token[q0][46] = q6;  // '.'
    token[q0][44] = q7;  // ','
    token[q0][48] = q5;  // '0'

    // Para q1
    token[q0][125] = q0;  // '}'

    // Para q14
    token[q14][61] = q16; // '='
    token[q14][62] = q17;  // '>'

    // Para q18
    token[q18][61] = q19; // '='

    // Para q21
    token[q21][61] = q23; // '='

    return token;
}

int *valid_chars(){
	int *list = malloc(sizeof(char)*MAX_CHAR_VAL);
	for(int i = 0; i < 128; i++){
	}
}

void transition(int *_state, char _nextChar, char *_nextToken,int *_tokenSize, int *_numLines, int **tTable){
		

}

























