#ifndef __ARVORE_RB
#define __ARVORE_RB

#define RED 1
#define BLACK 0

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct Record Record;
typedef struct Tree Tree;

struct Record{
    int key;
    char *value;
};

struct Tree{
    Record record;
    Tree *esq, *dir;
    int cor;
};


Tree* CreateTree();
//funçoes de caminhamento
void showTreeInOrder(Tree *tree);
void showTreePreOrder(Tree *tree);
void showTreePosOrder(Tree *tree);
//funçao de pesquisa 
bool search(Tree **no, Tree **raiz, Record record);

//funçoes auxiliares
int cor(Tree *tree);
void trocaCor(Tree *tree);

//rotações
Tree *rotacionaEsquerda(Tree *noA);
Tree *rotacionaDireita(Tree *noA);
// rotaciona os nós vermelhos consecutivos 
Tree *rotacionaEsquerdaRed(Tree *tree);
Tree *rotacionaDireitaRed(Tree *tree);
Tree *balancear(Tree *tree);

//inserir nó funçao que busca o local exato aonde inserir e balancear 
Tree *insereNo(Tree **tree,Record record,int *resp);
int insereArvRB(Tree **tree,Record record);

//achar e remover nó 
Tree *procuraMenor(Tree *no);
Tree *removeMenor(Tree *no);
Tree *removeNo(Tree *no,Record record);
int removeArvRB(Tree **tree,Record);

#endif
