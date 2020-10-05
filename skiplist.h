//Inclusão das biblitecas utilizadas no programa
#include <stdio.h>
#include <stdlib.h>
//---------------------------------------------------------------------------------------------------------------------------
//Definição da quantidade máxima de níveis da Skip List
#define MAXLEVELS 1000
//---------------------------------------------------------------------------------------------------------------------------
//Definição da estrutura dos nós da Skip List
typedef struct tnode{
    struct tnode *next[MAXLEVELS];
    int value;
}node;
//---------------------------------------------------------------------------------------------------------------------------
//Definição da estrutura da cabeça da Skip List;
typedef struct{
    node *head[MAXLEVELS];
    int size[MAXLEVELS];
}SkipList;
