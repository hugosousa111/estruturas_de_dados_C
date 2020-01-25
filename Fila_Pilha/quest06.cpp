#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Coisa{
	char carac;
	Coisa* prox;
};

typedef struct Coisa coisa;

coisa* inicio_fila = (coisa*) calloc(1, sizeof(coisa)); 
coisa* ultimo_fila = inicio_fila;

coisa* inicio_pilha_opera = (coisa*) calloc(1, sizeof(coisa)); 
coisa* ultimo_pilha_opera = inicio_pilha_opera;

coisa* inicio_fila_exp_final = (coisa*) calloc(1, sizeof(coisa)); 
coisa* ultimo_fila_exp_final = inicio_fila_exp_final;

void criar_fila_expressao(char caractere_exp){
	coisa* c1 = (coisa*) calloc(1, sizeof(coisa));
	c1->carac = caractere_exp;
	ultimo_fila->prox = c1;
	c1->prox = NULL;
	ultimo_fila = c1;
}

void criar_pilha_operacoes(char caractere_exp){
	coisa* c1 = (coisa*) calloc(1, sizeof(coisa));
	c1 -> prox = inicio_pilha_opera -> prox; 
	inicio_pilha_opera->prox = c1;	
	c1 -> carac = caractere_exp;  
}

void remove(coisa* inicio){
	if(inicio->prox != NULL){
		coisa* pt = inicio->prox;
		inicio->prox = pt->prox;
		free(pt);
	}else{
		printf("ERROR, LISTA VAZIA");
	}
}
void inserir_expressao_final(char letra_atual){
	coisa* c1 = (coisa*) calloc(1, sizeof(coisa));
	c1->carac = letra_atual;
	ultimo_fila_exp_final->prox = c1;
	c1->prox = NULL;
	ultimo_fila_exp_final = c1;
}

main(){
	int tamanho;
	char carac;
	printf("Insira a Quantidade de Caracteres de Sua Expressao :\n");
	scanf("%d", &tamanho);
	setbuf(stdin, NULL);
	printf("Insira a sua Expressao Parametrizada:\n");
	
	for(int i = 0; i < tamanho; i++){
		scanf("%c", &carac);
		criar_fila_expressao(carac);
	}
	
	coisa* obj = inicio_fila;
	char letra_atual;
	
	while(obj->prox != NULL){
		obj = obj->prox;
		letra_atual = obj->carac;
		if(letra_atual == '('){
			continue;
		}else{
			if((letra_atual == '+' )||(letra_atual == '-' )||(letra_atual == '/' )||(letra_atual == '*' )){
				criar_pilha_operacoes(letra_atual);
			}
			else{
				if(letra_atual == ')' ){
					inserir_expressao_final(inicio_pilha_opera->prox->carac);
					remove(inicio_pilha_opera);
				}else{
					inserir_expressao_final(letra_atual);
				}	
			}	
		}
	}
	int cont = 0;
	coisa* obj1 = inicio_fila_exp_final;
	printf("Expressao Polonesa Inversa Correspondente: ");
	while(obj1->prox !=NULL){
		obj1 = obj1->prox;
		printf("%c",obj1->carac);
		cont++;
	}
	//tentativa frustrada de inversão para polonesa normal 
	/*coisa* inicio_polonesa_normal; 
	coisa* inicio_inversa = inicio_fila_exp_final; 
	coisa* variante = inicio_polonesa_normal;
	
	int n = cont; 
	int i;
	printf("\nteste\n");
	while(inicio_inversa!= NULL){
		for(i = 0; i<n-1; i++){
			variante = variante->prox;
			variante->carac = inicio_inversa->prox->carac;
		}	
		inicio_inversa = inicio_inversa->prox;
		n--;	
		variante = inicio_polonesa_normal;
	}
	printf("\nteste\n");
	coisa* obj2 = inicio_polonesa_normal;
	while(obj2->prox !=NULL){
		obj2 = obj2->prox;
		printf("%c",obj2->carac);
	}*/
	printf("\n");
	system ("pause");
  	return 0;
}
