#ifndef __CONSULTALIVROS_
#define __CONSULTALIVROS_

#include "stdio.h"
#include "stdlib.h"
#include "Arvore_rb.h"

Tree *pesquisa_CodigoISBN(Tree **tree,Tree **aux, Record record);
void imprimeLivro(Tree *tree);


#endif
