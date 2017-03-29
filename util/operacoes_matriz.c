#include "operacoes_matriz.h"

#include <stdlib.h>
#include <stdio.h>

Matriz * somarMatriz(Matriz * m1, Matriz * m2)
{
    if(m1->row != m2->row && m1->col != m2->col)
    {
        return NULL;
    }

    Matriz * matriz = (Matriz *)malloc(sizeof(Matriz *));

    matriz->row = m1->row;
    matriz->col = m1->col;
    matriz->dados = (Fracao ***)malloc(m1->row * sizeof(Fracao ***));

    alocarMemoriaDadosMatriz(matriz);

    int i, j;

    for(i = 0; i < m1->row; i++)
    {
        for(j = 0; j < m1->col; j++)
        {
            matriz->dados[i][j] = soma(m1->dados[i][j], m2->dados[i][j]);
        }
    }

    return matriz;
}

Matriz * multMatriz(Matriz * m1, Matriz * m2)
{
    if(m1->col != m2->row)
    {
        return NULL;
    }

    Matriz * matriz = (Matriz *)malloc(sizeof(Matriz *));

    matriz->row = m1->row;
    matriz->col = m2->col;

    matriz->dados = (Fracao ***)malloc(matriz->row * sizeof(Fracao ***));

    alocarMemoriaDadosMatriz(matriz);

    int i, j, k;

    for(i = 0; i < m1->row; i++)
    {
        Fracao * f;

        for(k = 0; k < m2->col; k++)
        {
            for(j = 0; j < m1->col; j++)
            {
                if(j == 0)
                {

                    f = mult(m1->dados[i][j], m2->dados[j][k]);

                }else{

                    f = soma(mult(m1->dados[i][j], m2->dados[j][k]), f);
                }
            }

            if(f->denominador != 1)
            {
                simplificarFracao(f);
            }

            matriz->dados[i][k] = f;
        }
    }

    return matriz;
}

Matriz * transporMatriz(Matriz * m)
{
    Matriz * matriz = (Matriz *)malloc(sizeof(Matriz *));

    matriz->row = m->col;
    matriz->col = m->row;

    alocarMemoriaDadosMatriz(matriz);

    int i, j;

    for(i = 0; i < m->row; i++)
    {
        for(j = 0; j < m->col; j++)
        {
            matriz->dados[j][i]  = (Fracao *)malloc(sizeof(Fracao *));
            *matriz->dados[j][i] = *m->dados[i][j];
        }
    }

    return matriz;
}

int isPermutavel(int row, int col, Matriz * m)
{
    int i;

    for(i = row + 1; i < m->row; i++)
    {
        if(!isZero(m->dados[i][col]))
        {
            return i;
        }
    }

    return -1;
}

void permutarLinhas(int row1, int row, Matriz * m)
{
    int j;
    Fracao * tmp = (Fracao *)malloc(sizeof(Fracao *));

    for(j = 0; j < m->col; j++)
    {
        tmp->numerador = m->dados[row][j]->numerador;
        tmp->denominador = m->dados[row][j]->denominador;

        *m->dados[row][j] = *m->dados[row1][j];
        *m->dados[row1][j] = *tmp;
    }
}

void multElementoLinha(int row, Fracao * fr, Matriz * m)
{
    int j;

    for(j = 0; j < m->col; j++)
    {
        m->dados[row][j] = mult(m->dados[row][j], fr);
        simplificarFracao(m->dados[row][j]);
    }
}

void somarLinhas(int row, int row1, Fracao * k, Matriz * m)
{
    int j;

    for(j = 0; j < m->col; j++)
    {
        Fracao * el1 = mult(m->dados[row1][j], k);
        Fracao * el  = soma(m->dados[row][j], el1);

        simplificarFracao(el);

        m->dados[row][j] = el;
    }
}

void zerarColuna(int row, int col, Matriz * m)
{
    int i = row + 1, j;

    Fracao * k = (Fracao *)malloc(sizeof(Fracao *));

    for(; i < m->row; i++)
    {
        k->denominador = m->dados[i][col]->denominador;
        k->numerador = m->dados[i][col]->numerador * (-1);

        for(j = 0; j < m->col; j++)
        {
            Fracao * l2 = m->dados[i][j];
            Fracao * l1 = mult(m->dados[row][j], k);

            m->dados[i][j] = soma(l1, l2);
            simplificarFracao(m->dados[i][j]);
        }
    }
}

void zerarColunaIdentidade(int row, int col, Matriz * m, Matriz * m_ident)
{
    int i = row + 1, j;

    Fracao * k = (Fracao *)malloc(sizeof(Fracao *));

    for(; i < m->row; i++)
    {
        k->denominador = m->dados[i][col]->denominador;
        k->numerador = m->dados[i][col]->numerador * (-1);

        for(j = 0; j < m->col; j++)
        {
            Fracao * l2 = m->dados[i][j];

            Fracao * l1 = mult(m->dados[row][j], k);

            Fracao * m_ident_l1 = mult(m_ident->dados[row][j], k);
            Fracao * m_ident_l2 = m_ident->dados[i][j];

            m_ident->dados[i][j] = soma(m_ident_l1, m_ident_l2);
            m->dados[i][j] = soma(l1, l2);

            simplificarFracao(m->dados[i][j]);
            simplificarFracao(m_ident->dados[i][j]);
        }
    }
}


Fracao * detProcessoTriangulacao(Matriz * m)
{
    if(m->row != m->col)
    {
        return NULL;
    }

    int i, j;

    Fracao * det = NULL;
    Fracao * fr = (Fracao *)malloc(sizeof(Fracao *));

    for(i = 0; i < m->row; i++)
    {
        for(j = 0; j < m->col; j++)
        {
            if(i == j)
            {
                fr->numerador = m->dados[i][j]->numerador;
                fr->denominador = m->dados[i][j]->denominador;

                if(isZero(fr))
                {
                    int index = isPermutavel(i, j, m);

                    if(index >= 0)
                    {
                        permutarLinhas(index, i, m);

                        if(det == NULL)
                        {
                            det = (Fracao *)malloc(sizeof(Fracao *));

                            det->numerador = -1;
                            det->denominador = 1;

                        } else{

                            fr->numerador = -1;
                            fr->denominador = 1;

                            *det = *mult(fr, det);
                        }

                        fr->numerador = m->dados[i][j]->numerador;
                        fr->denominador = m->dados[i][j]->denominador;

                    } else{

                        free(det);
                        det = (Fracao *)malloc(sizeof(Fracao *));

                        det->numerador = 0;
                        det->denominador = 1;

                        return det;
                    }
                }

                if(det == NULL)
                {
                    det = (Fracao *)malloc(sizeof(Fracao *));

                    *det = *fr;

                } else{

                    *det = *mult(fr, det);
                }

                if(i < (m->row - 1))
                {
                    inversa(fr);
                    multElementoLinha(i, fr, m);
                    zerarColuna(i, j, m);
                }
            }
        }
    }

    free(fr);
    simplificarFracao(det);

    return det;
}

Matriz * calcMatrizInversa(Matriz * m)
{
    Matriz * inv = gerarMatrizIdentidade(m->row);
    Fracao * fr = (Fracao *)malloc(sizeof(Fracao *));

    int i, j;

    for(i = 0; i < m->row; i++)
    {
        for(j = 0; j < m->col; j++)
        {
            if(i == j)
            {
                fr->numerador = m->dados[i][j]->numerador;
                fr->denominador = m->dados[i][j]->denominador;

                if(isZero(fr))
                {
                    int index = isPermutavel(i, j, m);

                    if(index >= 0)
                    {
                        permutarLinhas(index, i, m);
                        permutarLinhas(index, i, inv);

                        fr->numerador = m->dados[i][j]->numerador;
                        fr->denominador = m->dados[i][j]->denominador;

                    } else{

                        return NULL;
                    }
                }

                inversa(fr);

                multElementoLinha(i, fr, m);
                multElementoLinha(i, fr, inv);

                if(i < m->row - 1)
                {
                    zerarColunaIdentidade(i, j, m, inv);
                }

                int r, c;

                for(r = i - 1; r >= 0; r--)
                {
                    for(c = 0; c < m->col; c++)
                    {
                        fr->numerador = m->dados[r][j]->numerador;
                        fr->denominador = m->dados[r][j]->denominador;

                        fr->numerador *= -1;

                        if(!isZero(fr))
                        {
                            somarLinhas(r, i, fr, m);
                            somarLinhas(r, i, fr, inv);
                        }
                    }
                }
            }
        }
    }

    free(fr);

    return inv;
}
