#include "ConsultaLivros.h"

Tree *pesquisa_CodigoISBN(Tree **tree,Tree **aux, Record record)
{
	if(*tree == NULL){
		return NULL; // retorna NULL ou seja nao achou o nó ou o nó foi deletado
	}

	if((*tree)->record.key > record.key){ return pesquisa_CodigoISBN(&(*tree)->esq, aux, record); }
	if((*tree)->record.key < record.key){ return pesquisa_CodigoISBN(&(*tree)->dir, aux, record); }

	*aux = *tree;
	return *aux;
}

void imprimeLivro(Tree *tree)
{
	if(tree == NULL)
	{
		printf("Livro não encontrado ou está alugado!\n");
	}
	else
	{
		printf("Livro encontrado e disponível para alugar: %s\n", tree->record.value);
	}
}
