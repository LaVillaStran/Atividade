#ifndef LISTA_DIN_ENCAD_CIRC_H
#define LISTA_DIN_ENCAD_CIRC_H

/* Tipo do dado armazenado na lista. */
struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
};


typedef struct elemento* Lista;

int tamanho_lista(Lista* li);

void imprime_lista(Lista* li);

int conta_aprovados(Lista* li);

int busca_ciclica(Lista* li, int k, struct aluno *al);

#endif /* LISTA_DIN_ENCAD_CIRC_H */