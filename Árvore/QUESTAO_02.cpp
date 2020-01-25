#include <stdio.h>
#include <stdlib.h>

//estrutura da �rvore, que vai ter um n�mero, e dois ponteiros, os filhos
struct Arvore{
	int chave;
	int altura = 1;
	int balanco = 0;
	struct Arvore *filhoE;
	struct Arvore *filhoD;
};
typedef struct Arvore arvore;

#define MAXIMO(alt_e,alt_d) (alt_e > alt_d ? alt_e : alt_d)

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

arvore* Busca(arvore* r, int numero){
	
	//uma busca binaria, que n�o � necessario passar por todos os numeros 
	//se ele achar o numero, retorna o ponteiro para aquela posi��o, se n�o achar retorna null
	if(r != NULL){
		if(r->chave == numero){
			//se for igual ao numero procurado, retorna a aloca��o do mesmo numero da arvore
			return r;
		}else{
			//se n�o for igual, verificamos se � maior ou menor
			if(numero > r->chave){
				//se for maior, o numero deve esta a direita, chama o metodo de novo, com a raiz sendo o filhoD
				return Busca(r->filhoD, numero);
			}else{
				//se for menor, o numero deve esta a esquerda, chama o metodo de novo, com a raiz sendo o filhoE
				return Busca(r->filhoE, numero);
			}
		}
	}else{
		//se ele entrar nesse else, � porque o numero n�o esta na arvore
		return NULL;
	}
}

arvore* arvore_remove(arvore *r, int num){	

	if(r != NULL){
		if(r->chave > num){
			//se for maior � porque o numero esta a esquerda da raiz, ent�o ele continua a busca 
			r->filhoE = arvore_remove(r->filhoE, num);
		}
		else if (r->chave < num){
			//se for maior � porque o numero esta a direita da raiz, ent�o ele continua a busca 
			r->filhoD = arvore_remove(r->filhoD, num);
		}	
		else{
			arvore* t;
			if (r->filhoE == NULL){
				//se o filho a esquerda for nulo j� pode apagar pois n�o vai ficar filhos sem pai
				t = r; 
				r = r->filhoD;
				free(t);
			}else if (r->filhoD == NULL){
				//se o filho a direita for nulo j� pode apagar pois n�o vai ficar filhos sem pai
				t = r; 
				r = r->filhoE;
				free(t);
			}else{
				//caso tenha filhos ele procura um candidato para ser o pai e troca suas posi��es 
				t = r->filhoE;
				while(t->filhoD != NULL){
					t = t->filhoD;
				}
				r->chave = t->chave; 
				t->chave = num;
				//depois de trocado ele manda remover o num agora sendo filho, que � o caso simples
				r->filhoE = arvore_remove(r->filhoE, num);
			}
		}	
	}
	return r;
}

void setar_altura_balanco(arvore *r){
	if(r != NULL){
		setar_altura_balanco(r->filhoD); //pra passar em todos os n�s pos ordem 
		setar_altura_balanco(r->filhoE);
    	int alt_f_e = 0, alt_f_d = 0; 
		if(r->filhoD != NULL){
			//se o filho a direita n�o for nulo, a variavel auxiliar recebe a altura dela 
			alt_f_d = r->filhoD->altura;
		}
		if(r->filhoE != NULL){
			//se o filho a esquerda n�o for nulo, a variavel auxiliar recebe a altura dela 
			alt_f_e = r->filhoE->altura;
		}
		r->altura = MAXIMO(alt_f_e,alt_f_d) + 1; //a altura � o maximo das alturas dos filhos 
		r->balanco = alt_f_e - alt_f_d;	//balan�o � a diferen�a das alturas dos filhos
		
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
				//rota��o dupla a esquerda			
				rotacao_dupla_esquerda(r);
			}else{
				//rota��o esquerda
				rotacao_esquerda(r);
			}
		}if(r->balanco == 2){
			if(r->filhoE->balanco >= 1){
				//rota��o direita	
				rotacao_direita(r);		
			}else{
				//rota��o dupla a direita
				rotacao_dupla_direita(r);
			}
		}
	}
}

arvore* busca(arvore* r, int numero){
	//uma busca binaria, que n�o � necessario passar por todos os numeros 
	//se ele achar o numero, retorna o ponteiro para aquela posi��o, se n�o achar retorna null
	if(r != NULL){
		if(r->chave == numero){
			//se for igual ao numero procurado, retorna a aloca��o do mesmo numero da arvore
			return r;
		}else{
			//se n�o for igual, verificamos se � maior ou menor
			if(numero > r->chave){
				//se for maior, o numero deve esta a direita, chama o metodo de novo, com a raiz sendo o filhoD
				return Busca(r->filhoD, numero);
			}else{
				//se for menor, o numero deve esta a esquerda, chama o metodo de novo, com a raiz sendo o filhoE
				return Busca(r->filhoE, numero);
			}
		}
	}else{
		//se ele entrar nesse else, � porque o numero n�o esta na arvore
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
		if(x==0){ //condi��o de fim de inser��o
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
	exibir_pre_ordem(bus)	; //para exibir a sub arvore � s� mandar exibir com o n� encontrado sendo a raiz
	
		
}
