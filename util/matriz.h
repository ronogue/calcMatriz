/*
    Implementação de funções para criar e exibir matrizes
    de números fracionários.
 */
#ifndef MATRIZ_H
#define MATRIZ_H

#include "fracao.h"

struct matriz{

    int row;
    int col;

    Fracao *** dados;
};

typedef struct matriz Matriz;

/**
 * Função para gerar uma matriz.
 * @param  row - quantidade de linhas.
 * @param  col - quantidade de colunas.
 * @return     - Matriz de Fracao.
 */
Matriz * gerarMatriz(int row, int col);

/**
 * Função para gerar uma matriz quadrada.
 * @param  ordem - ordem da matriz.
 * @return       - Matriz quadrada de Fracao.
 */
Matriz * gerarMatrizQuadrada(int ordem);

/**
 * Função para gerar uma matriz identidade.
 *
 * @param  ordem - ordem da matriz.
 * @return       - retorna uma matriz identidade.
 */
Matriz * gerarMatrizIdentidade(int ordem);

/**
 * Função para imprimir uma matriz qualquer.
 * @param matriz - Matriz de Fracao.
 */
void imprimirMatriz(Matriz * m);

/**
 * Função para desalocar memória usada para criar a matriz.
 *
 * @param matriz - Matriz de Fracao.
 */
void desalocarMemoriaMatriz(Matriz * m);

/**
 * Função para alocar memória para as linhas da matriz;
 * A quantidade de linha da matriz deve ser fornecida ao ponteiro desta.
 * @param m - ponteiro da matriz.
 */
void alocarMemoriaDadosMatriz(Matriz * m);

#endif
