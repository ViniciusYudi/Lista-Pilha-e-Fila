#ifndef LISTADUPLAMENTELIGADA_H
#define LISTADUPLAMENTELIGADA_H

#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
  // outros campos...
} REGISTRO;

typedef struct aux {
  REGISTRO reg;
  struct aux *ant, *prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
  PONT inicio;
} LISTA;

void inicializarLista(LISTA* l);
void exibirLista(LISTA* l);
int tamanho(LISTA* l);
int tamanhoEmBytes(LISTA* l);
PONT buscaSequencial(LISTA* l, TIPOCHAVE ch);
PONT buscaSeqOrd(LISTA* l, TIPOCHAVE ch);
PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant);
bool excluirElemLista(LISTA* l, TIPOCHAVE ch);
void reinicializarLista(LISTA* l);
bool inserirElemListaOrd(LISTA* l, REGISTRO reg);
PONT retornarPrimeiro(LISTA* l, TIPOCHAVE *ch);
PONT retornarUltimo(LISTA* l, TIPOCHAVE *ch);

#endif
