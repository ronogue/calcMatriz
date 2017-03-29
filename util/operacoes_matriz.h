/*
    Implementação das operações básicas de matrizes.
 */
#ifndef OPERACOES_MATRIZ_H
#define OPERACOES_MATRIZ_H

#include <stdlib.h>

#include "matriz.h"
#include "fracao.h"

/**
 * Função para realizar a soma de duas matrizes.
 *
 * @param  m1 - primeira matriz.
 * @param  m2 - segunda matriz.
 * @return    - a matriz resultante da soma m1 + m2 caso a opeção seja possível, NULL do contrário.
 */
Matriz * somarMatriz(Matriz * m1, Matriz * m2);

/**
 * Função para realizar a multiplicação de duas matrizes.
 *
 * @param  m1   - primeira matriz.
 * @param  m2   - segunda matriz.
 * @return      - retorna uma matriz (row1, col2) caso a operação seja possível, NULL do contrário.
 */
Matriz * multMatriz(Matriz * m1, Matriz * m2);

/**
 * Função para fazer a transposição de uma matriz.
 * @param  m   [description]
 * @return     [description]
 */
Matriz * transporMatriz(Matriz * m);

/**
 * Função para calcular a matriz inversa;
 * @param  m - matriz
 * @return   - a iversa da matriz m, do contrário
 * NULL caso não há inversa.
 */
Matriz * calcMatrizInversa(Matriz * m);

/**
 * Função para calcular o determinante de uma matriz usando o processo
 * de triangulação.
 * @param  m - matriz a qual será calculada o determinante.
 * @return Fracao - fração representando o determinante.
 */
Fracao * detProcessoTriangulacao(Matriz * m);

/**
 * Matriz para multiplicar a linha do pivô (Aij -> i == j) pelo
 * seu inverso.
 *
 * @param row - linha do pivô.
 * @param fr  - número a ser multiplicado.
 * @param m   - matriz.
 */
void multElementoLinha(int row, Fracao * fr, Matriz * m);

/**
 * Função que soma uma linha com o produto de uma constante
 * com outra linha.
 *
 * @param row  - linha em que se quer alterar os valores com estes
 * somados com o produto do elemento correspondente em outra linha
 * com uma constante.
 *
 * @param row1 - linha que será adicionada aos elementos da linha de indice row.
 * @param k    - constante que será multiplicada com a linha de indice row1.
 *
 */
void somarLinhas(int row, int row1, Fracao * k, Matriz * m);

/**
 * Método para zerar as colunas cujo i > j, usa-se operação elementar
 * para zerar a coluna, no caso a da soma de uma linha pela a outra
 * multiplicada por uma constante.
 *
 *
 * pivô é Aij -> i == j
 *
 * @param row - a linha do pivô.
 * @param col - coluna do pivô.
 * @param m   - Matriz.
 */
void zerarColuna(int row, int col, Matriz * m);

/**
 * Função para zerar as colunas de uma linha com base na constante
 * que é usada para zerar a coluna de uma matriz outra matriz, usa-se
 * operação elementar para zerar a coluna, no caso a da soma de uma linha pela a outra
 * multiplicada por uma constante.
 *
 * @param row - a linha do pivô
 * @param col - coluna do pivô.
 * @param m   - matriz que será zerada a coluna e que será usada a
 * constante que foi usada para zerar.
 * @param m1  [description]
 */
void zerarColunaIdentidade(int row, int col, Matriz * m, Matriz * m1);

/**
 * Função para verificar se é possível permutar uma linha pela outra
 * sendo esta ultmima com o lemento M->dados[i][j] diferente de zero.
 *
 * @param  row - linha que se deseja permutar.
 * @param  col - coluna da linha que se deseja permutar.
 * @param  m   - matriz a ser verificada se é possível permutar.
 *
 * @return int , index da linha que pode ser trocada com a linha row,
 * -1 caso não seja possível permutar.
 */
int isPermutavel(int row, int col, Matriz * m);

/**
 * Função para permutar duas linhas da matriz.
 *
 * @param row1 - linha a ser colocada no lugar da outra.
 * @param row  - linha em que há a necessidade de ser permutada.
 * @param m    - matriz a ser permutada.
 */
void permutarLinhas(int row1, int row, Matriz * m);


#endif
