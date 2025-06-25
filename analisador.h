#ifndef ANALISADOR_H
#define ANALISADOR_H

#include "Token.h"
#include "Fila.h"

// L� a express�o e gera tokens v�lidos
int tokenizar(const char *expr, Token tokens[], int *n);

// Verifica se a sequ�ncia de tokens est� corretamente estruturada
int sintaxe_valida(Token tokens[], int n);

// Converte de nota��o infixa para p�s-fixada (usando o algoritmo de Shunting Yard)
void infixa_para_posfixa(Token tokens[], int n, Fila *saida);

// Avalia a express�o em nota��o p�s-fixada, retornando o resultado
int avaliar_posfixa(Fila *posfixa, int *resultado);

#endif

