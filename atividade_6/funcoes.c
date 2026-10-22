#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

struct elemento {
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;
///////////////////////////////////////////////////////////
// extras: recursos que usarei durante as questões

int tamanho_lista(Lista* li) {
    if (li == NULL || (*li) == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    do {         
        cont++;
        no = no->prox;
    } while (no != (*li));
    return cont;
}
///////////////////////////////////////////////////////////
// 1


int imprimir_lista(Lista* li){
    if(li == NULL)  return 0;
    Elem *no = li;
    if (no == NULL) return 0;
    do{
        printf("%d ", &no->dados.matricula);
        no = no->prox;
    }
    while(no != li);
    return 1;
}

//2

int maior_matricula(Lista* li, int *mat){
    if(li == NULL || *li == NULL || mat == NULL)  return 0;
    Elem *no = li;

    int maior = no->dados.matricula;
    do{
        if (maior < no->dados.matricula) maior = no->dados.matricula;
        no = no->prox;
    }
    while(no != li);
    *mat = maior;
    return 1;
}

// 3 

/// Com defeito

/*
int conta_aprovados(Lista* li){
int cont = 0;
Elem *no = *li;
while(no != NULL){
float media = (no->dados.n1 + no->dados.n2 + no->dados.n3) / 3;
if(media >= 7.0)
cont++;
no = no->prox;
}
return cont;
}*/

/// Corrigido

int conta_aprovados(Lista* li){
int cont = 0;
Elem *no = *li;
do{ 
    /*
     O uso da função "do ... while ... faz sentido dado que como 'no' começa com *li
     e se começássemos com a condição de inicio, que DEVE SER (no != *li).
    */
    float media = (no->dados.n1 + no->dados.n2 + no->dados.n3) / 3;
        if(media >= 7.0){
            cont++;
        }
        no = no->prox;
}
while(no != *li);

// A mudança de no != NULL para li é mais recomendável, pois a condição de parada nesses
// casas de lista encadeada circular deve ser no != *li que seria o nosso 'primeiro termo' 

return cont;
}

// 4

int busca_ciclica(Lista* li, int k, struct aluno *al){
 if (li == NULL || *li == NULL || k <= 0 || al == NULL) return 0;

 Elem *no = *li;
 
 int tamanho = tamanho_lista(li);

 tamanho = ((k - 1)%tamanho) + 1;

 if (tamanho == 1) {
    *al = no->dados;
    return 1;
 }

 int i = 1;

 do{
  i++;
  no = no->prox;
 }

 while(i < tamanho);

 *al = no->dados;
 return 1;
}

// 5