#include <stdlib.h>
#include<stdio.h>
#include<ctype.h>

#include "../headers/automata.h"

// Funcao para criar a tabela de transicoees
Transition** transition_table(int _numStates, int _numChars) {

    // Aloca a matriz dinamicamente
    Transition **token = (Transition **)malloc(NUM_STATES * sizeof(Transition *));
    int i, j;  // Declarando as variaveis i e j fora dos loops
    for (i = 0; i < NUM_STATES; i++) {
        token[i] = (Transition *)malloc(MAX_CHAR_VAL * sizeof(Transition));
    }

    // Inicializa a matriz
    for (i = 0; i < NUM_STATES; i++) {
        for (j = 0; j < MAX_CHAR_VAL; j++) {
		// por definicao, todos os estados sao invalidos e todas as transicoes sao imprimiveis
        	token[i][j].state = -1;
		token[i][j].printable = 1;
        }
    }

    // define algumas transicoes mais gerais
    for (i = 0; i < MAX_CHAR_VAL; i++) {
	// define transicoes para inteiros
	if(isalpha(i)){
		// leitura de caracteres em q0, q2 e q33
		token[q0][i].state = q2;
		token[q2][i].state = q2;
	} else if(isdigit(i)){
		// leituras de digitos em q0, q2, q4, q26, q27 e q33 
		token[q0][i].state = q4;
    		token[q2][i].state = q2;
		token[q4][i].state = q4;
		token[q6][i].state = q27;
		token[q26][i].state = q27;
		token[q27][i].state = q27;
		token[q33][i].state = q33;

    	} else {
		// atribuicao do 'outro' em q2 e q4
		token[q2][i].state = q3;
		token[q2][i].printable = 0;
		token[q4][i].state = q5;
		token[q4][i].printable = 0;
		token[q6][i].state = q32;
		token[q6][i].printable = 0;
		token[q26][i].state = q29;
		token[q26][i].printable = 0;
		token[q27][i].state = q28;
		token[q27][i].printable = 0;
		token[q33][i].state = q29;
		token[q33][i].printable = 0;
	}


	// atribuicao do outro em q1, q14, q18 e q21
	token[q1][i].state = q1;
	token[q1][i].printable = 0;
	token[q14][i].state = q15;
	token[q14][i].printable = 0;
	token[q18][i].state = q20;
	token[q18][i].printable = 0;
	token[q21][i].state = q23;
	token[q21][i].printable = 0;
	token[q24][i].state = q24;
	token[q24][i].printable = 0;
	token[q25][i].state = q5;
	token[q25][i].printable = 0;
    }

    // Transicoes especificas

    // Para q0
    token[q0][43].state = q10;  // '+'
    token[q0][45].state = q11;  // '-'
    token[q0][32].state = q0;   // ' '
    token[q0][60].state = q14;  // '<'
    token[q0][62].state = q18;  // '>'
    token[q0][61].state = q13;  // '='
    token[q0][123].state = q1;  // '{'
    token[q0][10].state = q0;   // '\n'
    token[q0][47].state = q8;   // '/'
    token[q0][9].state = q0;    // '\t'
    token[q0][13].state = q0;   // '\r'
    token[q0][59].state = q12;  // ';'
    token[q0][58].state = q21;  // ':'
    token[q0][46].state = q6;  // '.'
    token[q0][44].state = q7;  // ','
    token[q0][48].state = q25;  // '0'
    token[q0][40].state = q30;  // '('
    token[q0][41].state = q31;  // ')'

    // Para q1
    token[q1][10].state = q24;
    token[q1][125].state = q0;  // '}'

    // Para esses ultimos, define tambem as transicoes imprimiveis
    // Para q4
    token[q4][46].state = q26; // '.'
    token[q4][46].printable = 1; // '.'
    token[q4][44].state = q33;  // ','
    token[q4][44].printable = 1; // ','

    // Para q14
    token[q14][61].state = q16; // '='
    token[q14][61].printable = 1; // '='
    token[q14][62].state = q17;  // '>'
    token[q14][62].printable = 1;  // '>'

    // Para q18
    token[q18][61].state = q19; // '='
    token[q18][61].printable = 1; // '='

    // Para q21
    token[q21][61].state = q22; // '='
    token[q21][61].printable = 1; // '='
				  
    // Para q25
    token[q25][46].state = q26; // '.'
    token[q25][46].printable = 1; // '.'
    token[q25][44].state = q33;  // ','
    token[q25][44].printable = 1; // ','


    return token;
}

void free_table(Transition **table){
	for(int i = 0; i < NUM_STATES; i++){
		free(table[i]);
	}
	free(table);
}


void transition(int *_state, char _nextChar, char *_nextToken,int *_tokenSize, int *_numLines, Transition **tTable){
		if(_nextChar > 127 || _nextChar < 0){
			// erro -> caractere invalido
			// como o caractere 0 eh sempre invalido, todas as transicoes funcionarao da mesma forma
			// i.e., ele nao afetara o reconhecimento de uma cadeia e ainda sera detectado como um caractere invalido
			*_state = tTable[*_state][0].state;
		} else {
			int _pastState = *_state;
	
			*_state = tTable[*_state][(int)_nextChar].state;	

			// verifica se o caractere eh comentario/char nao imprimivel
			if(!tTable[_pastState][(int)_nextChar].printable  || !isprint(_nextChar)|| _nextChar == ' ' || _nextChar == '}' || _nextChar == '{'){
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







