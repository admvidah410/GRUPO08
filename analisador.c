#include "dstlib_include.h"
#include "Token.h"
#include "analisador.h"


// Função 1: Análise Lexical
int tokenizar(const char *expr, Token tokens[], int *n) {
    int i = 0, j = 0;
    while (expr[i] != '\0') {
        char c = expr[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        if (isdigit(c)) {
            tokens[j].value = c;
            tokens[j].type = NUMERO;
            tokens[j].peso = 3;
        } else if (c == '+' || c == '-') {
            tokens[j].value = c;
            tokens[j].type = OPERADOR;
            tokens[j].peso = 1;
        } else if (c == '*' || c == '/' || c == '%') {
            tokens[j].value = c;
            tokens[j].type = OPERADOR;
            tokens[j].peso = 2;
        } else if (c == '^') {
            tokens[j].value = c;
            tokens[j].type = OPERADOR;
            tokens[j].peso = 4;
        } else if (c == '(' || c == ')') {
            tokens[j].value = c;
            tokens[j].type = PARENTESES;
            tokens[j].peso = 0;
        } else {
            return 0; // caractere inválido
        }

        j++;
        i++;
    }

    *n = j;
    return 1;
}

// Função 2: Análise Sintática
int sintaxe_valida(Token tokens[], int n) {
    Pilha_int parenteses;
    initPilhaInt(&parenteses);

    for (int i = 0; i < n; i++) {
        Token atual = tokens[i];
        Token anterior = i > 0 ? tokens[i - 1] : (Token){'n', NONE, -1};

        if (atual.type == PARENTESES) {
            if (atual.value == '(') {
                push_int(&parenteses, 1);
            } else {
                if (vaziaPilhaInt(&parenteses)) return 0;
                pop_int(&parenteses);
            }
        }

        if (atual.type == OPERADOR && anterior.type == OPERADOR) return 0;
        if (atual.type == NUMERO && anterior.type == NUMERO) return 0;
        if (atual.value == '(' && anterior.type == NUMERO) return 0;
        if (anterior.value == ')' && atual.type == NUMERO) return 0;
        if ((i == 0 || i == n - 1) && atual.type == OPERADOR) return 0;
    }

    return vaziaPilhaInt(&parenteses);
}

// Função 3: Conversão Infixa para Pós-fixa (Shunting Yard)
void infixa_para_posfixa(Token tokens[], int n, Fila *saida) {
    Pilha operadores;
    initPilha(&operadores);

    for (int i = 0; i < n; i++) {
        Token tk = tokens[i];

        if (tk.type == NUMERO) {
            inserir(saida, tk);
        } else if (tk.type == OPERADOR) {
            while (!vaziaPilha(&operadores) &&
                   top(&operadores).type == OPERADOR &&
                   top(&operadores).peso >= tk.peso) {
                inserir(saida, top(&operadores));
                pop(&operadores);
            }
            push(&operadores, tk);
        } else if (tk.value == '(') {
            push(&operadores, tk);
        } else if (tk.value == ')') {
            while (!vaziaPilha(&operadores) && top(&operadores).value != '(') {
                inserir(saida, top(&operadores));
                pop(&operadores);
            }
            if (!vaziaPilha(&operadores)) pop(&operadores); // remove '('
        }
    }

    while (!vaziaPilha(&operadores)) {
        inserir(saida, top(&operadores));
        pop(&operadores);
    }
}

// Função 4: Avaliação da Pós-fixa
int avaliar_posfixa(Fila *posfixa, int *resultado) {
    Pilha_int numeros;
    initPilhaInt(&numeros);

    while (!vaziaFila(posfixa)) {
        Token tk = frente(posfixa);
        remover(posfixa);

        if (tk.type == NUMERO) {
            int valor = tk.value - '0';
            push_int(&numeros, valor);
        } else if (tk.type == OPERADOR) {
            if (vaziaPilhaInt(&numeros)) return 0;
            int b = top_int(&numeros); pop_int(&numeros);
            if (vaziaPilhaInt(&numeros)) return 0;
            int a = top_int(&numeros); pop_int(&numeros);

            int res = 0;
            switch (tk.value) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': if (b == 0) return INT_MIN; res = a / b; break;
                case '%': if (b == 0) return INT_MIN; res = a % b; break;
                case '^': {
                    res = 1;
                    for (int i = 0; i < b; i++) res *= a;
                    break;
                }
                default: return 0;
            }

            push_int(&numeros, res);
        }
    }

    if (vaziaPilhaInt(&numeros)) return 0;
    *resultado = top_int(&numeros);
    return 1;
}

