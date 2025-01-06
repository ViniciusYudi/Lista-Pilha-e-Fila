#include "listaDuplamenteLigada.h"
#include <stdio.h>

int main() {
  LISTA lista;
  inicializarLista(&lista);

  printf("Inserindo elementos na lista:\n");
  REGISTRO r1 = {10};
  REGISTRO r2 = {20};
  REGISTRO r3 = {15};

  inserirElemListaOrd(&lista, r1);
  inserirElemListaOrd(&lista, r2);
  inserirElemListaOrd(&lista, r3);

  exibirLista(&lista);

  printf("\nTamanho da lista: %d elementos\n", tamanho(&lista));
  printf("Tamanho em bytes: %d bytes\n", tamanhoEmBytes(&lista));

  printf("\nBuscando elemento 15:\n");
  PONT encontrado = buscaSequencial(&lista, 15);
  if (encontrado != NULL)
    printf("Elemento encontrado: %d\n", encontrado->reg.chave);
  else
    printf("Elemento 15 nao encontrado\n");

  printf("Buscando elemento 25:\n");
  encontrado = buscaSequencial(&lista, 25);
  if (encontrado != NULL)
    printf("Elemento encontrado: %d\n", encontrado->reg.chave);
  else
    printf("Elemento 25 nao encontrado\n");

  printf("\nExcluindo elemento 15:\n");
  if (excluirElemLista(&lista, 15))
    printf("Elemento 15 removido com sucesso\n");
  else
    printf("Falha ao remover elemento 15\n");

  exibirLista(&lista);

  TIPOCHAVE chave;
  PONT primeiro = retornarPrimeiro(&lista, &chave);
  if (primeiro != NULL)
    printf("\nPrimeiro elemento: %d\n", chave);
  else
    printf("Lista vazia\n");

  PONT ultimo = retornarUltimo(&lista, &chave);
  if (ultimo != NULL)
    printf("Ultimo elemento: %d\n", chave);
  else
    printf("Lista vazia\n");

  printf("\nReinicializando lista\n");
  reinicializarLista(&lista);
  exibirLista(&lista);

  printf("\nLista reinicializada e liberada\n");

  return 0;
}

