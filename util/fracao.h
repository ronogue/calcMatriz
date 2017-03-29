/*
	Implementção de números fracionários e as operações
	de soma e multiplicação.
 */
#ifndef FRACAO_H
#define FRACAO_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

struct fracao {

    int numerador;
    int denominador;

};

typedef struct fracao Fracao;

/**
 * Função para realizar a soma de duas frações.
 *
 * @param  f1 - Fracao 1
 * @param  f2 - Fracao 2
 * @return    - ponteiro para Fracao.
 */
Fracao * soma(Fracao * f1, Fracao * f2);

/**
 * Função para realizar a multiplicação de duas frações.
 *
 * @param  f1 - Fracao 1
 * @param  f2 - Fracao 2
 * @return    - ponteiro para Fracao.
 */
Fracao * mult(Fracao * f1, Fracao * f2);

/**
 * Função que cria a inversa de uma fração.
 *
 * @param  f - fração a ser invertida.
 */
void inversa(Fracao * f);

/**
 * Função para pegar a fração de um usuário.
 * @return - matriz de Fracao.
 */
Fracao * pegarFracaoDoUsuario();

/**
 * Função para desalocar memória de uma Fracao.
 * @param args    - Quantidade de argumentos
 * @param VARARGS - poneteiro de Fracao
 */
void desalocarMemoriaMemoriaFracao(int args, ...);

/**
 * Função para imprimir uma fração.
 * @param f - Ponteiro para uma fração.
 */
void imprimirFracao(Fracao * f);

/**
 * Método para simplificar uma fração quando possível.
 *
 * @param  f - ponteiro para uma fração.
 */
void simplificarFracao(Fracao * f);

/**
 * Função para verificar se uma fração é zero.
 * @param  f - fração a ser verificada.
 * @return int, 1 caso seja zero, 0 do contrário.
 */
int isZero(Fracao * f);

#endif
