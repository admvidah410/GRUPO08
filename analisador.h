#ifndef ANALISADOR_H
#define ANALISADOR_H

#include "Token.h"
#include "Fila.h"

// Lê a expressão e gera tokens válidos
int tokenizar(const char *expr, Token tokens[], int *n);

// Verifica se a sequência de tokens está corretamente estruturada
int sintaxe_valida(Token tokens[], int n);

// Converte de notação infixa para pós-fixada (usando o algoritmo de Shunting Yard)
void infixa_para_posfixa(Token tokens[], int n, Fila *saida);

// Avalia a expressão em notação pós-fixada, retornando o resultado
int avaliar_posfixa(Fila *posfixa, int *resultado);

#endif

