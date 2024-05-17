#include <stdio.h>
#include <stdlib.h>

// Cria estados em valores numéricos via enum
enum estados_automatos {
    q0 = 0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13,
    q14, q15, q16, q17, q18, q19, q20, q21, q22, q23, q24, q25, q26
} estados;

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
            if (i == 0) {
                token[i][j] = j;
            } else if (j == 0) {
                token[i][j] = i - 1;
            } else {
                token[i][j] = -1;
            }
        }
    }

    // Validando apenas os estados que serão utilizados
    for (i = 1; i < _numStates; i++) {
        for (j = 0; j < _numChars; j++) {
            if (((j >= 48) && (j <= 57)) || ((j >= 65) && (j <= 90)) || ((j >= 97) && (j <= 122))) {
                token[i][j] = 3;
            }
        }
    }

    // Caracteres unitários
    token[1][43] = 15;  // '+'
    token[1][45] = 11;  // '-'
    token[1][32] = 1;   // ' '
    token[1][60] = 17;  // '<'
    token[1][62] = 21;  // '>'
    token[1][61] = 16;  // '='
    token[1][123] = 1;  // '{'
    token[1][10] = 5;   // '\n'
    token[1][92] = 9;   // '\\'
    token[1][9] = 0;    // '\t'
    token[1][59] = 10;  // ';'
    token[1][46] = 12;  // '.'
    token[1][44] = 13;  // ','

    // Para q1
    token[2][125] = 4;  // '}'

    // Para q17
    token[19][125] = 20; // '}'
    token[19][62] = 19;  // '>'

    // Para q21
    token[23][125] = 23; // '}'

    // Para q24
    token[26][125] = 26; // '}'

    return token;
}

/*
int main() {
    int numStates = 28;
    int numChars = 129;

    // Chama a função para criar a tabela de transições
    int **token = transition_table(numStates, numChars);

    // Verifica o conteúdo da matriz
    int i, j;  // Declarando as variáveis i e j fora dos loops
    for (i = 0; i < numStates; i++) {
        for (j = 0; j < numChars; j++) {
            printf("%4d", token[i][j]);
        }
        printf("\n");
    }

    // Libera a memória alocada
    for (i = 0; i < numStates; i++) {
        free(token[i]);
    }
    free(token);

    return 0;
}
*/
