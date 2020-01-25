#include <stdio.h>
#include <stdlib.h>

//estrutura da árvore, que vai ter um número, e dois ponteiros, os filhos
struct Arvore{
	int chave;
	struct Arvore *filhoE;
	struct Arvore *filhoD;
};
typedef struct Arvore arvore;

arvore* raiz_arvore = (arvore*)calloc(1, sizeof(arvore)); //alocando a memória para a arvore, no caso inicia com o ponteiro para a raiz

void Insercao(arvore* r, int numero){
	//passa uma raiz da arvore, ou da subarvore e o numero que quer adicionar 
	if(numero == r->chave){
		printf("NUMERO JA INSERIDO\n");
		//se o numero ja estiver inserido, ele avisa
	}else{
		if(numero > r->chave){
			//se o numero que o usuario adicionou for maior que o da raiz, ele vai pra direita
			if(r->filhoD == NULL){
				//se a raiz não tiver filhos a direita, ele adiciona o que o usuario digitou 
				arvore* temp =(arvore*) calloc(1, sizeof(arvore));
				r->filhoD = temp;
				temp->chave = numero;
			}else{
				/*se tiver filho a direita, então ele não adiciona naquele lugar, 
				e chama novamente o metodo, ate achar um lugar para adicionar o numero que o usuario digitou*/
				Insercao(r->filhoD, numero);
			}
		}else{
			//se o numero que o usuario adicionou for menor que o da raiz, ele vai pra esquerda
			if(r->filhoE == NULL){
				//se a raiz não tiver filhos a esquerda, ele adiciona o que o usuario digitou 
				arvore* temp =(arvore*) calloc(1, sizeof(arvore));
				r->filhoE  = temp;
				temp->chave = numero;
			}else{
				/*se tiver filho a esquerda, então ele não adiciona naquele lugar, 
				e chama novamente o metodo, ate achar um lugar para adicionar o numero que o usuario digitou*/
				Insercao(r->filhoE, numero);
			}
		}
	}
}

arvore* Busca(arvore* r, int numero){
	//uma busca binaria, que não é necessario passar por todos os numeros 
	//se ele achar o numero, retorna o ponteiro para aquela posição, se não achar retorna null
	if(r != NULL){
		if(r->chave == numero){
			//se for igual ao numero procurado, retorna a alocação do mesmo numero da arvore
			return r;
		}else{
			//se não for igual, verificamos se é maior ou menor
			if(numero > r->chave){
				//se for maior, o numero deve esta a direita, chama o metodo de novo, com a raiz sendo o filhoD
				return Busca(r->filhoD, numero);
			}else{
				//se for menor, o numero deve esta a esquerda, chama o metodo de novo, com a raiz sendo o filhoE
				return Busca(r->filhoE, numero);
			}
		}
	}else{
		//se ele entrar nesse else, é porque o numero não esta na arvore
		return NULL;
	}
}

void exibir_pre_ordem(arvore* r){
	if(r != NULL){
		printf("%d, ", r->chave);
		exibir_pre_ordem(r->filhoE);
		exibir_pre_ordem(r->filhoD);
	}
}

void exibir_pos_ordem(arvore* r){
	if(r != NULL){
		exibir_pos_ordem(r->filhoE);
		exibir_pos_ordem(r->filhoD);
		printf("%d, ", r->chave);
	}
}

void exibir_simetrica(arvore* r){
	if(r != NULL){
		exibir_simetrica(r->filhoE);
		printf("%d, ", r->chave);
		exibir_simetrica(r->filhoD);
	}
}



arvore* arvore_remove(arvore *r, int num){	

	if(r != NULL){
		if(r->chave > num){
			//se for maior é porque o numero esta a esquerda da raiz, então ele continua a busca 
			r->filhoE = arvore_remove(r->filhoE, num);
		}
		else if (r->chave < num){
			//se for maior é porque o numero esta a direita da raiz, então ele continua a busca 
			r->filhoD = arvore_remove(r->filhoD, num);
		}	
		else{
			arvore* t;
			if (r->filhoE == NULL){
				//se o filho a esquerda for nulo já pode apagar pois não vai ficar filhos sem pai
				t = r; 
				r = r->filhoD;
				free(t);
			}else if (r->filhoD == NULL){
				//se o filho a direita for nulo já pode apagar pois não vai ficar filhos sem pai
				t = r; 
				r = r->filhoE;
				free(t);
			}else{
				//caso tenha filhos ele procura um candidato para ser o pai e troca suas posições 
				t = r->filhoE;
				while(t->filhoD != NULL){
					t = t->filhoD;
				}
				r->chave = t->chave; 
				t->chave = num;
				//depois de trocado ele manda remover o num agora sendo filho, que é o caso simples
				r->filhoE = arvore_remove(r->filhoE, num);
			}
		}	
	}
	return r;
}


int main(){
	int x;
	printf("Insira os numeros da sua arvore(para finalizar insira '0'):\n");
	scanf("%d", &x);
	raiz_arvore->chave = x; //insere logo o primeiro valor na raiz
	while(1){
		scanf("%d", &x);
		if(x==0){ //condição de fim de inserção
			break;
		}
		Insercao(raiz_arvore,x);
	}
	printf("\nExibicao Pre-ordem: ");
	exibir_pre_ordem(raiz_arvore);	
	printf("\nExibicao Pos-ordem: ");
	exibir_pos_ordem(raiz_arvore);	
	printf("\nExibicao Simetrica: ");
	exibir_simetrica(raiz_arvore);	
	
	printf("\nInsira um numero para ser buscado: ");
	scanf("%d", &x);
	arvore * bus = Busca(raiz_arvore, x); 
	if(bus == NULL){
		printf("Numero nao encontrado");
	}else{
		printf("Numero encontrado %d" , bus->chave);	
	}
	
	printf("\nInsira um numero para ser removido: ");
	scanf("%d", &x);
	
	if(raiz_arvore == Busca(raiz_arvore,x) && (raiz_arvore->filhoD == NULL || raiz_arvore->filhoE == NULL)){
		//caso o usuario queira apagar a raiz e ela tenha um dos filhos sendo nulo 
		arvore * ax ;
		if (raiz_arvore->filhoE == NULL){
			//se o filho a esquerda for nulo já pode apagar pois não vai ficar filhos sem pai
			ax = raiz_arvore; 
			raiz_arvore = raiz_arvore->filhoD;
			free(ax);
		}else {
			//se o filho a direita for nulo já pode apagar pois não vai ficar filhos sem pai
			ax = raiz_arvore; 
			raiz_arvore = raiz_arvore->filhoE;
			free(ax);
		}
	}else{
		arvore * test = arvore_remove(raiz_arvore, x);
	}
	
	
	printf("\nExibicao Simetrica: ");
	exibir_simetrica(raiz_arvore);	
		
}
