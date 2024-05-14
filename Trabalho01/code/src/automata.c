#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Cria a tabela de transicoes

char **transition_table(int _numStates, int _numChars){
	// cria a tabela de transicoes
	char **table = malloc(sizeof(char*)*_numStates);
	for(int i = 0; i < _numStates; i++){
		table[i] = malloc(sizeof(char)*_numChars);
		for(int j = 0; j < _numChars; j++){
			// inicializa todas as transicoes como invalidas
			table[i][j] = -127; 
		}
	}	

	return table;	
}

// Inicializa a tabela de transicao segundo a modelagem lexica  da linguagem

int init_table(char **transitionTable){
	// estado inicial
	
	// Estado q1
	
	// Estado q2

}
