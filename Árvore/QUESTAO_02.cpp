#include <stdio.h>
#include <stdlib.h>

//estrutura da árvore, que vai ter um número, e dois ponteiros, os filhos
struct Arvore{
	int chave;
	int altura = 1;
	int balanco = 0;
	struct Arvore *filhoE;
	struct Arvore *filhoD;
};
typedef struct Arvore arvore;

#define MAXIMO(alt_e,alt_d) (alt_e > alt_d ? alt_e : alt_d)

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

void setar_altura_balanco(arvore *r){
	if(r != NULL){
		setar_altura_balanco(r->filhoD); //pra passar em todos os nós pos ordem 
		setar_altura_balanco(r->filhoE);
    	int alt_f_e = 0, alt_f_d = 0; 
		if(r->filhoD != NULL){
			//se o filho a direita não for nulo, a variavel auxiliar recebe a altura dela 
			alt_f_d = r->filhoD->altura;
		}
		if(r->filhoE != NULL){
			//se o filho a esquerda não for nulo, a variavel auxiliar recebe a altura dela 
			alt_f_e = r->filhoE->altura;
		}
		r->altura = MAXIMO(alt_f_e,alt_f_d) + 1; //a altura é o maximo das alturas dos filhos 
		r->balanco = alt_f_e - alt_f_d;	//balanço é a diferença das alturas dos filhos
		
	}
}

void exibir_simetrica_a_b(arvore* r){
	if(r != NULL){
		exibir_simetrica_a_b(r->filhoE);
		printf("%d-> Altura(%d), Balanco(%d)\n", r->chave, r->altura , r->balanco);
		exibir_simetrica_a_b(r->filhoD);
		
	}
}

void rotacao_esquerda(arvore * r){
		
}

void rotacao_direita(arvore * r){
	
}

void rotacao_dupla_direita(arvore * r){
	//pra rodar pra direita primeiro gira pra esquerda a subarvore, e dps a direita 
	rotacao_esquerda(r);
	rotacao_direita(r);
}

void rotacao_dupla_esquerda(arvore * r){
	//pra rodar pra esquerda primeiro gira pra dirieta a subarvore, e dps a esquerda
	rotacao_direita(r);
	rotacao_esquerda(r);
}

void balanciar(arvore *r){
	//baseado no que o professor passou em sala
	if(r != NULL){
		balanciar(r->filhoD);
		balanciar(r->filhoE);
		if (r->balanco == -2){
			if(r->filhoD->balanco >= 1){
				//rotação dupla a esquerda			
				rotacao_dupla_esquerda(r);
			}else{
				//rotação esquerda
				rotacao_esquerda(r);
			}
		}if(r->balanco == 2){
			if(r->filhoE->balanco >= 1){
				//rotação direita	
				rotacao_direita(r);		
			}else{
				//rotação dupla a direita
				rotacao_dupla_direita(r);
			}
		}
	}
}

arvore* busca(arvore* r, int numero){
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
		setar_altura_balanco(raiz_arvore); 
		balanciar(raiz_arvore);
	}
	setar_altura_balanco(raiz_arvore); 
	exibir_simetrica_a_b(raiz_arvore);
	
	exibir_pre_ordem(raiz_arvore);
	
	printf("\nInsira um numero para ser buscado e ser exibido sua subarvore: ");
	scanf("%d", &x);
	arvore * bus = Busca(raiz_arvore, x); 
	if(bus == NULL){
		printf("Numero nao encontrado");
	}else{
		printf("Numero encontrado %d\n" , bus->chave);	
	}	
		
	printf("SUB-ARVORE\n");
	exibir_pre_ordem(bus)	; //para exibir a sub arvore é só mandar exibir com o nó encontrado sendo a raiz
	
		
}
