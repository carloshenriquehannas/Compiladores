#ifndef __AUTOMATA_H__
#define __AUTOMATA_H__

#define MAX_CHAR_VAL 128
#define MAX_TOKEN_SIZE 64
#define NUM_STATES 24

enum estados_automatos {
    q0 = 0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13,
    q14, q15, q16, q17, q18, q19, q20, q21, q22, q23, q24, q25, q26
};

// Função para criar a tabela de transições
int** transition_table(int _numStates, int _numChars);

#endif 
