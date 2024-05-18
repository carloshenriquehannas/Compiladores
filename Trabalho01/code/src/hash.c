#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/hash.h"

//Lista de palavras reservadas
    char *key_word[] = {
            "CALL", "BEGIN", "END", "IF", "THEN", "WHILE", "DO", "ODD", "CONST", "VAR", "PROCEDURE"
    };

//Função de hash 
unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

//Inicializacao da tabela hash
Node **init_table() {
    Node **table = (Node **)malloc(TABLE_SIZE * sizeof(Node *));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }

    //Insere a palavra servada na tabela hash
    for (int i = 0; i < sizeof(key_word) / sizeof(key_word[0]); i++) {
        insert(table, key_word[i]);
    }

    return table;
}

//Insere uma palavra na tabela hash
void insert(Node **table, char *word) {
    unsigned long index = hash(word);
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->word = strdup(word);
    new_node->next = table[index];
    table[index] = new_node;
}

//Verifica se uma palavra esta na tabela hash
int search(Node **table, char *word) {
    unsigned long index = hash(word);
    Node *current = table[index];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return 1; //Palavra encontrada
        }
        current = current->next;
    }
    return 0; //Palavra não encontrada
}

// Libera a memoria alocada para a tabela hash
void free_htable(Node **table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = table[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp->word);
            free(temp);
        }
    }
    free(table);
}

  

