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

//Função de hash para a tabela de seguidores e primeiros 
unsigned long hash2(char *str);

//Inicializacao da tabela hash
Node **init_table();

//Inicializacao das tabelas de seguidores
Node ***init_followers();

//Inicializacao das tabelas de primeiros
Node ***init_firsts();

//Insere uma palavra na tabela hash
void insert(Node **table, char *word);

//Insere uma palavra na tabela de seguidores e primeiros
void insert2(Node **table, char *word);

//Verifica se uma palavra esta na tabela hash
int search(Node **table, char *word);

// Libera a memoria alocada para a tabela hash
void free_htable(Node **table);

#endif
