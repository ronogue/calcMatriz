#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"
#include "fracao.h"

Matriz * gerarMatriz(int row, int col)
{
    int i, j;

    Matriz * matriz = (Matriz *)malloc(sizeof(Matriz *));

    matriz->row = row;
    matriz->col = col;

    alocarMemoriaDadosMatriz(matriz);

    for(i = 0; i < row; i++)
    {
        printf("L-> %d | ", i + 1);

        for(j = 0; j < matriz->col; j++)
        {
            matriz->dados[i][j] = pegarFracaoDoUsuario();

            if(j == col - 1)
            {
                printf("\n");
            }
        }
    }

    return matriz;
}

Matriz * gerarMatrizQuadrada(int ordem)
{
    return gerarMatriz(ordem, ordem);
}

Matriz * gerarMatrizIdentidade(int ordem)
{
    int i, j;

    Matriz * m = (Matriz *)malloc(sizeof(Matriz *));

    m->row = ordem;
    m->col = ordem;

    alocarMemoriaDadosMatriz(m);

    for(i = 0; i < ordem; i++)
    {
        for(j = 0; j < ordem; j++)
        {
            Fracao * fr = (Fracao *)malloc(sizeof(Fracao *));

            if(i == j)
            {
                fr->numerador = 1;
                fr->denominador = 1;
            }
            else{
                fr->numerador = 0;
                fr->denominador = 1;
            }

            m->dados[i][j] = fr;
        }
    }

    return m;
}

void imprimirMatriz(Matriz * m)
{
    int i, j;

    fflush(stdout);

    for(i = 0; i < m->row; i++)
    {
        for(j = 0; j < m->col; j++)
        {
            imprimirFracao(m->dados[i][j]);

            if(j == m->col - 1)
            {
                printf("\n");
            }
        }

        printf("\n\n");
    }
}

void alocarMemoriaDadosMatriz(Matriz * m)
{
    int i;
    m->dados = (Fracao ***)malloc(m->row * sizeof(Fracao ***));

    for(i = 0; i < m->row; i++)
    {
        m->dados[i] = (Fracao **)malloc(m->col * sizeof(Fracao **));
    }
}

void desalocarMemoriaMatriz(Matriz * m)
{
    if(m != NULL)
    {
        int i, j;

        for(i = 0; i < m->row; i++)
        {
            for(j = 0; j < m->col; j++)
            {
                free(m->dados[i][j]);
                m->dados[i][j] = NULL;
            }
        }

        free(m);
        m = NULL;
    }
}
