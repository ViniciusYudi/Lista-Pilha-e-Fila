#include <stdio.h>
#include <malloc.h>
#define ERRO -1
#define true 1
#define false 0
typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
  // outros campos...
} REGISTRO;

typedef struct aux {
  REGISTRO reg;
  struct aux* prox;
} ELEMENTO, *PONT;

typedef struct {
  PONT fim;
  PONT cabeca;
} FILA;

/* Inicialização da fila ligada (a fila jah esta criada e eh apontada 
pelo endereco em f) */
void inicializarFila(FILA* f){
  f->cabeca = (PONT) malloc(sizeof(ELEMENTO));
  f->cabeca->prox = NULL;
  f->fim = NULL;
} /* inicializarFila */

/* Retornar o tamanho da fila (numero de elementos) */
int tamanho(FILA* f) {
  PONT end = f->cabeca->prox;
  int tam = 0;
  while (end != NULL){
    tam++;
    end = end->prox;
  }
  return tam;
} /* tamanho */

/* Retornar o tamanho em bytes da fila. Neste caso, isto depende do numero
   de elementos que estao sendo usados.   */
int tamanhoEmBytes(FILA* f) {
  return (tamanho(f)*sizeof(ELEMENTO)) + sizeof(FILA);
} /* tamanhoEmBytes */

/* Destruição da fila 
   libera a memoria de todos os elementos da fila*/
void destruirFila(FILA* f) {
  PONT end = f->cabeca->prox;
  while (end != NULL){
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  f->cabeca->prox = NULL;
  f->fim = NULL;
} /* destruirFila */


/* retornarPrimeiro - retorna o endereco do primeiro elemento da fila e (caso
   a fila nao esteja vazia) retorna a chave desse elemento na memoria 
   apontada pelo ponteiro ch */
PONT retornarPrimeiro(FILA* f, TIPOCHAVE *ch){
  if (f->cabeca->prox != NULL) *ch = f->cabeca->prox->reg.chave;
  return f->cabeca->prox;
} /* retornarPrimeiro */

/* retornarUltimo - retorna o endereco do ultimo elemento da fila e (caso
   a fila nao esteja vazia) retorna a chave desse elemento na memoria 
   apontada pelo ponteiro ch */
PONT retornarUltimo(FILA* f, TIPOCHAVE* ch){
  if (f->cabeca->prox == NULL) return NULL;
  *ch = f->fim->reg.chave;
  return f->fim;
} /* retornarUltimo */


/* Inserção no fim da fila */
bool inserirNaFila(FILA* f,REGISTRO reg) {
  PONT novo = (PONT) malloc(sizeof(ELEMENTO));
  novo->reg = reg;
  novo->prox = NULL;
  if (f->cabeca->prox==NULL){ // se o proximo do no cabeça eh null (n tem elementos)
     f->cabeca->prox = novo;  // entao, o proximo do nó cabeça eh justamente o elemento inserido (1º elemento)
  }else{
     f->fim->prox = novo; // eh p inserir um novo depois do último elemento (próximo do até então final)
  }
  f->fim = novo; // agora o fim aponta para o novo fim
  return true;
} /* inserir */

/* Excluir  */
bool excluirDaFila(FILA* f, REGISTRO* reg) {
  if (f->cabeca->prox==NULL){ // se o próximo do nó cabeça eh nulo, retorna falso (não tem elementos válidos na fila)
    return false;                     
  }
  *reg = f->cabeca->prox->reg; // registro é alterado por ponteiro como o registro do próximo do nó cabeça (1º elemento)
  PONT apagar = f->cabeca->prox; // apagar é inicializado como o endereço do próximo do nó cabeça (1º elemento)
  f->cabeca->prox = f->cabeca->prox->prox; // o próximo do nó cabeça é inicializado como o próximo do próximo do nó cabeça (o 1º vira o 2º)
  free(apagar); // apaga o próximo ao nó cabeça
  if (f->cabeca->prox == NULL){ // se o próximo ao nó cabeça for null após da remoção, o final da fila eh null (apenas setando o ponteiro)
    f->fim = NULL;
  }
  return true;
} /* excluirDaFila */


/* Exibição da fila sequencial */
void exibirFila(FILA* f){
  PONT end = f->cabeca->prox;
  printf("Fila: \" ");
  while (end != NULL){
    printf("%d ", end->reg.chave); // soh lembrando TIPOCHAVE = int
    end = end->prox;
  }
  printf("\"\n");
} /* exibirFila */ 

/* Busca sequencial */
PONT buscaSeq(FILA* f,TIPOCHAVE ch){
  PONT pos = f->cabeca->prox;
  while (pos != NULL){
    if (pos->reg.chave == ch) return pos;
    pos = pos->prox;
  }
  return NULL;
} /* buscaSeq */

/* Busca sequencial com sentinela alocado dinamicamente */
PONT buscaSeqSent1(FILA* f,TIPOCHAVE ch){
  if (!f->cabeca->prox) return NULL;
  PONT sentinela = malloc(sizeof(ELEMENTO));
  sentinela->reg.chave = ch;
  f->fim->prox = sentinela;
  PONT pos = f->cabeca->prox;
  while (pos->reg.chave != ch) pos = pos->prox;
  free(sentinela);
  f->fim->prox = NULL;
  if (pos!=sentinela) return pos;
  return NULL;
} /* buscaSeqSent1 */

/* Busca sequencial com sentinela como variavel local */
PONT buscaSeqSent2(FILA* f,TIPOCHAVE ch){
  if (!f->cabeca->prox) return NULL;
  ELEMENTO sentinela;
  sentinela.reg.chave = ch;
  f->fim->prox = &sentinela;
  PONT pos = f->cabeca->prox;
  while (pos->reg.chave != ch) pos = pos->prox;
  f->fim->prox = NULL;
  if (pos!=&sentinela) return pos;
  return NULL;
} /* buscaSeqSent1 */

int main() {
  FILA fila;
  REGISTRO reg;

  inicializarFila(&fila);
  printf("Fila inicializada\n");

  printf("Inserindo elementos na fila\n");
  for (int i = 1; i <= 5; i++) {
      reg.chave = i * 10;
      inserirNaFila(&fila, reg);
      exibirFila(&fila);
  }

  printf("Tamanho da fila: %d\n", tamanho(&fila));
  printf("Tamanho em bytes: %d\n", tamanhoEmBytes(&fila));

  TIPOCHAVE chave;
  PONT primeiro = retornarPrimeiro(&fila, &chave);
  if (primeiro) printf("Primeiro elemento: %d\n", chave);

  PONT ultimo = retornarUltimo(&fila, &chave);
  if (ultimo) printf("Último elemento: %d\n", chave);

  printf("Removendo elementos da fila...\n");
  while (excluirDaFila(&fila, &reg)) {
      printf("Removido: %d\n", reg.chave);
      exibirFila(&fila);
  }

  printf("Tamanho da fila após remoções: %d\n", tamanho(&fila));
  exibirFila(&fila);

  printf("Teste de busca\n");
  for (int i = 1; i <= 3; i++) {
      reg.chave = i * 15;
      inserirNaFila(&fila, reg);
  }
  exibirFila(&fila);

  TIPOCHAVE chaveBusca = 30;
  printf("Buscando chave %d\n", chaveBusca);
  PONT encontrado = buscaSeq(&fila, chaveBusca);
  if (encontrado) printf("Chave %d encontrada\n", chaveBusca);
  else printf("Chave %d não encontrada\n", chaveBusca);

  destruirFila(&fila);
  printf("Fila destruida\n");

  return 0;
}
