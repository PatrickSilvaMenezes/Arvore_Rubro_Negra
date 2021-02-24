#include "stdio.h"
#include "stdlib.h"
#include "Arvore_rb.h"
#include "ConsultaLivros.h"

int main(){
	int ISBN[] = {100500,80000,100200,75000,90500,100110,100300};
	char *livros[] = {"Harry Potter"," Codigo da Vinci","Game of Thrones"," Senhor dos Anéis"," Star Wars","Cálculo","Sapiens"};// se usa um ponteiro para um vetor de char para ter uma referencia de onde começa 
	// os dados da indexaçao
	// ponteiros da minha struct Tree inicializados pelo método CreateTree
	Tree *raiz = CreateTree();
	Tree *aux = CreateTree();
	Tree *found = CreateTree();
	
	//Estrutura r da struct Record instanciada para uso posterior
	Record r;
	//variavel option para escolha de funçoes disponiveis no menu 
	int option = 9;
	//variavel code para alugar um livro
	int code=0;
	//variavel para verificar disponibilidade do livro
	int  verification=0;

	// preenchendo minha arvore RB
	for(int i=0; i< 7; i++){
		r.key = ISBN[i];
		r.value = livros[i];
		insereArvRB(&raiz, r);
	}
	
	while(option!=0)
	{
		printf("\nBem vindo a biblioteca Arvore RB digite a seguir o que deseja fazer!\n\n");
		printf("[0]- sair\n");
		printf("[1]- ver o menu de livros com seus respectivos códigos ISBN\n");
		printf("[2]- alugar livro(remover)\n");
		printf("[3]- ver árvore RB pelo método Preorder\n");
		printf("[4]- ver árvore RB pelo método Inorder\n");
		printf("[5]- ver árvore RB pelo método Pósorder\n");
		printf("[6]- verificar disponibilidade do livro na biblioteca\n");
		printf("Opção-->   ");
		scanf("%d",&option);

		if(option==0)
		{
			printf("\n[---Saindo do sistema da biblioteca!---]\n\n");
			break;
		}
		else if(option == 1)
		{
			printf("\nMenu de livros da biblioteca Arvore RB com seus respectivos códigos ISBN\n\n");
			printf("\t Código ISBN     Título do Livro\n");
			printf("\n");
			for (int i = 0; i < 7; i++)
			{
				printf("\t %d           %s\n",ISBN[i],livros[i]);
			}
		}

		else if(option==2)
		{
			printf("Digite o código ISBN do livro que deseja alugar:\n");
			scanf("%d",&code);
			r.key = code;
			removeArvRB(&raiz, r);
			printf("Livro de código %d alugado com sucesso\n",r.key);
			printf("\n");
		}
		else if(option == 3)
		{
			printf("\nArvore RB impressa pelo método PreOrder\n");
			printf("{ ");
			showTreePreOrder(raiz);
			printf("}\n");
			printf("\n");
		}
		else if(option == 4)
		{
			printf("\nArvore RB impressa pelo método InOrder\n");
			printf("{ ");
			showTreeInOrder(raiz);
			printf("}\n");
			printf("\n");
		}
		else if(option == 5)
		{
			printf("\nArvore RB impressa pelo método PosOrder\n");
			printf("{ ");
			showTreePosOrder(raiz);
			printf("}\n");
			printf("\n");
		}
		else if(option == 6)
		{
			printf("\nDigite o código ISBN do livro que deseja verificar disponibilidade:\n");
			scanf("%d",&verification);
			printf("\n");
			r.key= verification;
			found = pesquisa_CodigoISBN(&raiz,&aux,r);
			imprimeLivro(found);
			printf("\n");
		}
		else
		{
			printf("\n[---Opção digitada inválida, tente novamente com uma opção válida!---]\n");
		}

	}

	return 0;

}
