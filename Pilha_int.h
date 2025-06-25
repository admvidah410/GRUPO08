#ifndef PILHA_INT_H
#define PILHA_INT_H
#include "Pilha_int.h"
typedef struct node {
  int valor;
  struct node *prox;
} Node;

typedef struct {
  Node *cabeca;
} Pilha_int;

void initPilhaInt(Pilha_int *P);
int vaziaPilhaInt(Pilha_int *P);
Node *getNOPilhaInt(int n);
int push_int(Pilha_int *P, int n);
int pop_int(Pilha_int *P);
int top_int(Pilha_int *P);

#endif

