#ifndef LISTA_DIN_ENCAD_CIRC_H
#define LISTA_DIN_ENCAD_CIRC_H

/* Tipo do dado armazenado na lista. */
struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
};


typedef struct elemento* Lista;

int remove_lista_final(Lista* li);

int remove_lista_inicio(Lista* li);

int tamanho_lista(Lista* li);

void imprime_lista(Lista* li);

int conta_aprovados(Lista* li);

int busca_ciclica(Lista* li, int k, struct aluno *al);

int remove_lista_pos(Lista* li, int pos);

int rotaciona_lista(Lista* li, int k);

int concatena_listas(Lista* li1, Lista* li2);

int josephus(Lista* li, int k, int *sobrevivente);

#endif /* LISTA_DIN_ENCAD_CIRC_H */