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

    //Insere a palavra reservada na tabela hash
    for (int i = 0; i < sizeof(key_word) / sizeof(key_word[0]); i++) {
        insert(table, key_word[i]);
    }

    return table;
}

// Cria a lista de seguidores de cada nao terminal
Node ***init_followers(){
    Node ***table = (Node ***)malloc(17 * sizeof(Node **));
    for(int i = 0; i < 17; i++){
    	table[i] = (Node **)malloc(TABLE_SIZE * sizeof(Node *));
    } 

    FILE *file = fopen("./src/followers.csv", "r"); 

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
	exit(-1);
    }

    char line[256];
    int line_count = 0;

    while(fgets(line, 256, file) != NULL){
    	    char *token = strtok(line, ",");	    
	    while(token){
		insert(table[line_count],token);
		token = strtok(NULL, ",");
	    }
	    line_count++;
    }
    fclose(file);

    return table;
}

// Cria a lista de primeiros de cada nao terminal
Node ***init_firsts(){
    Node ***table = (Node ***)malloc(17 * sizeof(Node **));
    for(int i = 0; i < 17; i++){
    	table[i] = (Node **)malloc(TABLE_SIZE * sizeof(Node *));
    } 

    FILE *file = fopen("./src/firsts.csv", "r"); 

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
	exit(-1);
    }

    char line[256];
    int line_count = 0;

    while(fgets(line, 256, file) != NULL){
    	    char *token = strtok(line, ",");	    
	    while(token){
		insert(table[line_count],token);
		token = strtok(NULL, ",");
	    }
	    line_count++;
    }
    fclose(file);

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
            free(temp);
        }
    }
    free(table);
}

  

