#ifndef __HASH_H__
#define __HASH_H__

//Tamanho da tabela
#define TABLE_SIZE 50

//Define estrutura do no da lista
typedef struct Node {
    char *word;
    struct Node *next;
} Node;

//Função de hash 
unsigned long hash(char *str);

//Inicializacao da tabela hash
Node **init_table();

//Insere uma palavra na tabela hash
void insert(Node **table, char *word);

//Verifica se uma palavra esta na tabela hash
int search(Node **table, char *word);

// Libera a memoria alocada para a tabela hash
void free_htable(Node **table);

#endif
