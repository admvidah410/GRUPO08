#include <stdio.h>
#include <stdlib.h>

#include "dstlib_include.h"
#include "analisador.h" // contém: tokenizar, sintaxe_valida, etc.

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s in.txt out.txt\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "w");

    if (!fin || !fout) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), fin)) {
        linha[strcspn(linha, "\n")] = '\0';

        Token tokens[MAX];
        int n = 0;
        int resultado;

        if (!tokenizar(linha, tokens, &n)) {
            fprintf(fout, "Erro: Caracteres invalidos\n");
            continue;
        }

        if (!sintaxe_valida(tokens, n)) {
            fprintf(fout, "Erro: Parenteses desbalanceados ou expressao malformada\n");
            continue;
        }

        Fila posfixa;
        initFila(&posfixa);
        infixa_para_posfixa(tokens, n, &posfixa);

        int status = avaliar_posfixa(&posfixa, &resultado);
        if (status == INT_MIN) {
            fprintf(fout, "Erro: Divisao por zero\n");
        } else if (!status) {
            fprintf(fout, "Erro: Avaliacao invalida\n");
        } else {
            fprintf(fout, "%d\n", resultado);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

