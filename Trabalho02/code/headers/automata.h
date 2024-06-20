#ifndef __AUTOMATA_H__
#define __AUTOMATA_H__


#define MAX_CHAR_VAL 128
#define MAX_TOKEN_SIZE 62
#define NUM_STATES 30

enum estados_automatos {
    q0 = 0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13,
    q14, q15, q16, q17, q18, q19, q20, q21, q22, q23, q24, q25, q26,
    q27, q28, q29
};

// Representacao de uma transicao
// Contem o proximo estado e se essa transicao eh imprimivel ou nao
typedef struct {
	int state;
	char printable;
} Transition;

// Funcao para criar a tabela de transicoes
Transition** transition_table(int _numStates, int _numChars);

// Libera a tabela
void free_table(Transition **table);

// Funcao para fazer as transicoes entre estados
void transition(int *_state, char _nextChar, char *_nextToken,int *_tokenSize, int *_numLines, Transition **tTable);

#endif 
