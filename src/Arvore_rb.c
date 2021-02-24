#include "Arvore_rb.h"


Tree* CreateTree()
{
	return NULL;
}

void showTreeInOrder(Tree *tree)
{
  if(!(tree == NULL)){
    showTreeInOrder(tree->esq); 
    printf("%d ", tree->record.key);
    showTreeInOrder(tree->dir); 
  }
}
void showTreePreOrder(Tree *tree)
{
  if(!(tree == NULL))
  {
    printf("%d ", tree->record.key);
    showTreePreOrder(tree->esq); 
    showTreePreOrder(tree->dir); 
  }
}
void showTreePosOrder(Tree *tree)
{
  if(!(tree == NULL)){
    showTreePosOrder(tree->esq); 
    showTreePosOrder(tree->dir); 
    printf("%d  ", tree->record.key);
  }
}
bool search(Tree **no, Tree **raiz, Record record)
{
    bool aux = true;
    if(*no == NULL)
    {
        printf("[ERROR]: Record not found!\n");
        return false;
    }
    if((*no)->record.key > record.key)
    {
        aux = search(&(*no)->esq, raiz, record);
        return aux;
    }
    if((*no)->record.key < record.key)
    {
        aux = search(&(*no)->dir, raiz, record);
        return aux;
    }
    *raiz = *no;
    return aux;
}
int cor(Tree *tree)
{
    if(tree==NULL)
    {
        return BLACK;
    }
    else
    {
        return tree->cor;
    }
}
void trocaCor(Tree *tree)
{
    tree->cor = !tree->cor;
    if(tree->esq != NULL)
        tree->esq->cor = !tree->esq->cor;
    if(tree->dir != NULL)
        tree->dir->cor = !tree->dir->cor;
}

Tree *rotacionaEsquerda(Tree *noA)
{
    Tree *noB = noA->dir;
    noA->dir = noB->esq;
    noB->esq = noA;
    noB->cor = noA->cor;
    noA->cor = RED;
    return noB;
}

Tree *rotacionaDireita(Tree *noA)
{
    Tree *noB = noA->esq;
    noA->esq = noB->dir;
    noB->dir = noA;
    noB->cor =  noA->cor;
    noA->cor = RED;
    return noB;
}

Tree *rotacionaEsquerdaRed(Tree *tree)
{
    trocaCor(tree);
    if(cor(tree->dir->esq) == RED)//filho esquerdo do filho direito é vermelho alinho a direita e depois rotaciono para esquerda
    {
        tree->dir = rotacionaDireita(tree->dir);
        tree = rotacionaEsquerda(tree);
        trocaCor(tree);
    }
    return tree;
}

Tree *rotacionaDireitaRed(Tree *tree)
{
    trocaCor(tree);
    if(cor(tree->esq->esq) == RED)// filho esquerdo do filho esquerdo do nó é vermelho rotaciono a direita o nó pai
    {
        tree = rotacionaDireita(tree);
        trocaCor(tree);
    }
    return tree;

}

Tree *balancear(Tree *tree)// serve para corrigir as 3 violaçoes das propriedades
{
    if(cor(tree->dir)==RED)// filho direito vermelho rotaçao a esquerda
    {
        tree = rotacionaEsquerda(tree);
    }
    if(tree->esq != NULL && cor(tree->esq)==RED && cor(tree->esq->esq)==RED)// filho esquerdo vermelho e pai vermelho rotaçao a direita
    {
        tree = rotacionaDireita(tree);
    }
    if(cor(tree->esq)==RED && cor(tree->dir)==RED)// filhos vermelhos troca de cores
    {
        trocaCor(tree);
    }
    return tree;
}

Tree *insereNo(Tree **tree,Record record,int *resp)
{
    if(*tree==NULL)
    {
        Tree *no;
        no = (Tree*)malloc(sizeof(Tree));
        if(no==NULL)
        {
            *resp = 0;   //ou seja inserção falhou
            return NULL;
        }    
        no->esq = NULL;
        no->dir = NULL;
        no->record = record;
        no->cor = RED;
        return no;
    }
    if(record.key == (*tree)->record.key)
        *resp = 0;
    else
    {
        if(record.key < (*tree)->record.key)
            (*tree)->esq = insereNo(&(*tree)->esq,record, resp);
        else
            (*tree)->dir = insereNo(&(*tree)->dir,record, resp);
    }
    if(cor((*tree)->dir) == RED && cor((*tree)->esq) == BLACK)
        *tree = rotacionaEsquerda(*tree);
    if(cor((*tree)->esq) == RED && cor((*tree)->esq->esq) == RED)
        *tree = rotacionaDireita(*tree);
    if(cor((*tree)->esq) == RED && cor((*tree)->dir) == RED)
        trocaCor(*tree);
    return *tree;
}
int insereArvRB(Tree **tree,Record record)
{
    int resp=1;
    *tree = insereNo(tree, record, &resp);
    if((*tree) != NULL)
        (*tree)->cor = BLACK;//raiz começa com a cor preta
    return resp;
}

Tree *procuraMenor(Tree *no)
{
    Tree *no1 = no;
    Tree *no2 = no->esq;
    while(no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

Tree *removeMenor(Tree *no)
{
    if(no->esq == NULL)
    {
        free(no);
        return NULL;
    }
    if(cor(no->esq) == BLACK && cor(no->esq->esq) == BLACK)
        no = rotacionaEsquerdaRed(no);
    no->esq = removeMenor(no->esq);
    return balancear(no);
}

Tree *removeNo(Tree *no, Record record)
{
    if(record.key < no->record.key)
    {
        if(cor(no->esq) == BLACK && cor(no->esq->esq) == BLACK)
            no = rotacionaEsquerdaRed(no);
        no->esq = removeNo(no->esq, record);
    }
    else{
        if(cor(no->esq) == RED)
            no = rotacionaDireita(no);
        if(record.key == no->record.key && (no->dir == NULL))
        {
            free(no);
            return NULL;
        }
        if(cor(no->dir) == BLACK && cor(no->dir->esq) == BLACK)
            no = rotacionaDireitaRed(no);
        if(record.key == no->record.key)
        {
            Tree *aux = procuraMenor(no->dir);
            no->record.key = aux->record.key;
            no->dir = removeMenor(no->dir);
        }
        else{
            no->dir = removeNo(no->dir, record);
        }
    }
    return balancear(no);
}

int removeArvRB(Tree **tree, Record record)
{
    Tree *aux = CreateTree();
    if(search(tree, &aux, record))
    {
        Tree *no = *tree;
        *tree = removeNo(no, record);
        if(*tree != NULL)
            (*tree)->cor = BLACK;
        return 1;
    }
    else    
        return 0;
}

