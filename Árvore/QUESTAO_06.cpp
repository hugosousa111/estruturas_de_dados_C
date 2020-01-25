#include <stdio.h>
#include <stdlib.h>

//estrutura da �rvore, que vai ter um n�mero, e dois ponteiros, os filhos
struct Arvore{
	int chave;
	struct Arvore *filhoE;
	struct Arvore *filhoD;
};
typedef struct Arvore arvore;

arvore* raiz_arvore = (arvore*)calloc(1, sizeof(arvore)); //alocando a mem�ria para a arvore, no caso inicia com o ponteiro para a raiz

void Insercao(arvore* r, int numero){
	//passa uma raiz da arvore, ou da subarvore e o numero que quer adicionar 
	if(numero == r->chave){
		printf("NUMERO JA INSERIDO\n");
		//se o numero ja estiver inserido, ele avisa
	}else{
		if(numero > r->chave){
			//se o numero que o usuario adicionou for maior que o da raiz, ele vai pra direita
			if(r->filhoD == NULL){
				//se a raiz n�o tiver filhos a direita, ele adiciona o que o usuario digitou 
				arvore* temp =(arvore*) calloc(1, sizeof(arvore));
				r->filhoD = temp;
				temp->chave = numero;
			}else{
				/*se tiver filho a direita, ent�o ele n�o adiciona naquele lugar, 
				e chama novamente o metodo, ate achar um lugar para adicionar o numero que o usuario digitou*/
				Insercao(r->filhoD, numero);
			}
		}else{
			//se o numero que o usuario adicionou for menor que o da raiz, ele vai pra esquerda
			if(r->filhoE == NULL){
				//se a raiz n�o tiver filhos a esquerda, ele adiciona o que o usuario digitou 
				arvore* temp =(arvore*) calloc(1, sizeof(arvore));
				r->filhoE  = temp;
				temp->chave = numero;
			}else{
				/*se tiver filho a esquerda, ent�o ele n�o adiciona naquele lugar, 
				e chama novamente o metodo, ate achar um lugar para adicionar o numero que o usuario digitou*/
				Insercao(r->filhoE, numero);
			}
		}
	}
}

int contador_de_nos = 0 ;
int cont_soma = 0 ;

void contador_recursivo(arvore*raiz){
	//funciona da mesma forma que o exibir pre-ordem, toda vez que passa em um n� ele adiciona um no contador
	if(raiz != NULL){
		contador_de_nos++;
		contador_recursivo(raiz->filhoE);
		contador_recursivo(raiz->filhoD);
	}
}

void soma_recursiva(arvore*raiz){
	if(raiz != NULL){
		cont_soma = cont_soma + raiz->chave;
		//como o contador, passa em todos os n�s, adicionando o valor do n� em uma variavel soma
		soma_recursiva(raiz->filhoE);
		soma_recursiva(raiz->filhoD);
	}	
}

int aux_con, aux_ra = 0; //variaves auxiliares para saber as posi��es do vetor
arvore * vetor[100]; //um vetor de arvores que ira auxiliar na contagem de  n�s e na soma dos valores

void contador_iterativo(arvore * r){
	vetor[aux_con++] = r; //primeira posi��o do vetor recebe a raiz, e j� incrementa o aux_con que � o lugar da proxima posi��o
	do{
		if(r->filhoE != NULL){
			vetor[aux_con++] = r->filhoE;	
			//se tiver filho a esquerda ele adiciona no vetor 
		}if(r->filhoD != NULL){
			vetor[aux_con++] = r->filhoD;
			//se tiver filho a direita ele adiciona no vetor 
		}
		r = vetor[++aux_ra]; //agora a raiz passa a ser a proxima posi��o do vetor, pra testar se ele tem filhos, para adicionar no vetor
	}while(r != NULL && aux_con != aux_ra);
	 /*fica no enquanto at� a raiz ser nula(n�o tem mais filhos) ou o 
	 aux_con ser igual ao aux_ra quer dizer que j� testou todas as posi��es do vetor(todos os n�s)*/
	 
	 //no final o aux_con � o numero de n�s da arvore
}

int soma_i = 0;

void soma_iterativa(arvore * r){
	vetor[aux_con++] = r; //primeira posi��o do vetor recebe a raiz, e j� incrementa o aux_con que � o lugar da proxima posi��o
	do{
		if(r->filhoE != NULL){
			vetor[aux_con++] = r->filhoE;	
			//se tiver filho a esquerda ele adiciona no vetor 
		}if(r->filhoD != NULL){
			vetor[aux_con++] = r->filhoD;
			//se tiver filho a direita ele adiciona no vetor 
		}
		r = vetor[++aux_ra]; //agora a raiz passa a ser a proxima posi��o do vetor, pra testar se ele tem filhos, para adicionar no vetor
	}while(r != NULL && aux_con != aux_ra);
	 /*fica no enquanto at� a raiz ser nula(n�o tem mais filhos) ou o 
	 aux_con ser igual ao aux_ra quer dizer que j� testou todas as posi��es do vetor(todos os n�s)*/
	 
	for(int aux = 0; aux < aux_con; aux++){ 
		//passa em todas as posi��es do vetor, e soma as chaves dentro de soma_i
		soma_i = soma_i + vetor[aux]->chave;
	}
	soma_i = soma_i/2; //corre��o 
}


int main(){
	int x;
	printf("Insira os numeros da sua arvore(para finalizar insira '0'):\n");
	scanf("%d", &x);
	raiz_arvore->chave = x; //o primeiro valor digitado ser� a raiz
	//o 1 significa verdadeiro , ou seja , um enuqnato infinito
	while(1){
		scanf("%d", &x);
		if(x==0){
			break; //quando o usuario digitar 0 ele para
		}
		Insercao(raiz_arvore,x); //ele vai pro m�todo inserir	
	}
	
	contador_recursivo(raiz_arvore);
	soma_recursiva(raiz_arvore);
	printf("\nRECURSIVO");
	printf("\nNumero de nos: %d\n",contador_de_nos);
	printf("\nSoma dos numeros: %d\n",cont_soma);
	
	printf("\nITERATIVO");
	contador_iterativo(raiz_arvore);
	printf("\nNumero de nos: %d\n",aux_con);
	soma_iterativa(raiz_arvore);
	printf("\nSoma dos numeros: %d\n",soma_i);
	
	return(0);
}
