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
int remove_lista_inicio(Lista* li) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *atual = *li;
    while (atual->prox != (*li))  /* procura o ultimo */
        atual = atual->prox;
    Elem *no = *li;
    atual->prox = no->prox;       /* o ultimo passa a apontar para o segundo */
    *li = no->prox;               /* o segundo passa a ser o inicio */
    free(no);
    return 1;
}
///////////////////////////////////////////////////////////
int remove_lista_final(Lista* li) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *ant = NULL, *no = *li;
    while (no->prox != (*li)) {   /* procura o ultimo, guardando o no */
        ant = no;
        no = no->prox;
    }


    if (no->prox == *li)
        return remove_lista_final(li);

    ant->prox = no->prox;         /* o penultimo passa a apontar para o inicio */
    free(no);
    return 1;
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

int remove_lista_pos(Lista* li, int pos){
    if (li == NULL || *li == NULL || pos <= 0) return 0;

    Elem *no = *li, *rem;

    if (pos == 1){
        return remove_lista_inicio(li);
    }

    int i = 1;

    while(i < pos - 1 && no->prox != *li){
        no = no->prox;
        i++;
    }

     if (no->prox == *li)
        return 0;

    Elem* removido = no->prox;
    no->prox = removido->prox;
    free(removido);

    return 1;
}

// 6
// r1: 
/*
Do jeito que está, o custo é O(N), porque o código primeiro percorre a lista inteira só pra descobrir o tamanho, mesmo quando o k é pequeno. 
Pra ficar O(k), a gente teria que simplesmente andar k nós com o ponteiro de início, sem calcular o tamanho antes. 
*/

// r2: 
/*
Numa lista encadeada que não é circular, dá pra ter o mesmo efeito sem mexer nos campos prox: é só mudar o ponteiro de início pro nó que está na posição k + 1. 
Então, pra manter todos os elementos na sequência rotacionada, a gente precisa ligar o último nó ao início antigo (deixando a lista circular). 
Pra isso é preciso percorrer a lista até o fim, então o custo é O(N).
*/
int rotaciona_lista(Lista* li, int k){
    if (li == NULL || *li == NULL || k < 0) return 0;

    Elem *no = *li;

    int tamanho = 1;

    Elem *final = no;

    while (final->prox != no){
        final = final->prox;
        tamanho++;
    }

    k%= tamanho;

    while (k > 0) {
        *li = (*li)->prox;
        k--;
    }

    return 1;
}

// 7 
int concatena_listas(Lista* li1, Lista* li2) {
    if (li1 == NULL || li2 == NULL)
        return 0;

    if (*li2 == NULL)
        return 1;

    if (*li1 == NULL) {
        *li1 = *li2;
        *li2 = NULL;
        return 1;
    }

    Elem* inicio1 = *li1;
    Elem* inicio2 = *li2;

    Elem* fim1 = inicio1;
    while (fim1->prox != inicio1)
        fim1 = fim1->prox;

    Elem* fim2 = inicio2;
    while (fim2->prox != inicio2)
        fim2 = fim2->prox;

    fim1->prox = inicio2;
    fim2->prox = inicio1;

    *li2 = NULL;

    return 1;
}

// 8 
int josephus(Lista* li, int k, int* sobrevivente) {
    if (li == NULL || *li == NULL || k <= 0 || sobrevivente == NULL)
        return 0;

    Elem* corrente = *li;
    Elem* ant = *li;

    while (ant->prox != *li)
        ant = ant->prox;

    while (corrente != ant) {
        int contagem;

        for (contagem = 1; contagem < k; contagem++) {
            ant = corrente;
            corrente = corrente->prox;
        }

        ant->prox = corrente->prox;

        if (corrente == *li)
            *li = corrente->prox;

        free(corrente);
        corrente = ant->prox;
    }

    *sobrevivente = corrente->dados.matricula;
    free(corrente);
    *li = NULL;

    return 1;
}