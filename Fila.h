#ifndef FILA_H
#define FILA_H

#include "Token.h"

typedef struct nof {
  Token tk;
  struct nof *prox;
} NO;

typedef struct {
  NO *fim, *inicio;
} Fila;

// Apenas as declarações:
void initFila(Fila *F);
int vaziaFila(Fila *F);
NO *getNOFila(Token tk);
int inserir(Fila *F, Token tk);
int remover(Fila *F);
Token frente(Fila *F);

#endif

