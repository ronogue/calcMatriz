#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "fracao.h"
#include "util.h"

Fracao * soma(Fracao * f1, Fracao * f2)
{
    Fracao * resultado = (Fracao *) malloc(sizeof (Fracao *));

    if(f1->denominador == f2->denominador)
    {

        resultado->denominador  = f1->denominador;
        resultado->numerador    = f1->numerador + f2->numerador;

        return resultado;
    }
    else if(f1->denominador % 2 == 0 && f2->denominador % 2 == 0)
    {
        resultado->denominador = max(f1->denominador, f2->denominador);

    }else{
        resultado->denominador = f1->denominador * f2->denominador;
    }

    int numerador = ((resultado->denominador / f1->denominador) * f1->numerador) +
                    ((resultado->denominador / f2->denominador) * f2->numerador);

    resultado->numerador = numerador;

    return resultado;
}

Fracao * mult(Fracao * f1, Fracao * f2)
{
    Fracao * resultado = (Fracao *) malloc(sizeof (Fracao *));

    if(f1->numerador == f2->denominador)
    {
        resultado->numerador = f2->numerador;
        resultado->denominador = f1->denominador;

        return resultado;
    }
    else if(f2->numerador == f1->denominador)
    {
        resultado->numerador = f1->numerador;
        resultado->denominador = f2->denominador;

        return resultado;
    }

    resultado->numerador = f1->numerador * f2->numerador;
    resultado->denominador = f1->denominador * f2->denominador;

    return resultado;
}


Fracao * pegarFracaoDoUsuario()
{
    fflush(stdin);

    char c = 'a';
    char numerador[30];
    char denominador[30];

    int i = 0;
    int isNumerador = 1;
    int is_rei_contagem = 0;
    int _denominador;

    Fracao * f = (Fracao *) malloc(sizeof (Fracao *));

    while(c != 32 && c != 8 && c != 127)
    {
        system("stty raw");

        scanf("%c", &c);

        system("stty cooked");

        if(c == '/' || c == '-' || (c >= '0' && c <= '9'))
        {
            if(isNumerador && c != '/')
            {
                numerador[i] = c;

            } else {

                if(isNumerador){

                    isNumerador  = 0;
                    is_rei_contagem = 1;

                    numerador[i] = '\0';
                }

                if(c != '/')
                {
                    if(is_rei_contagem)
                    {
                        i = 0;
                        is_rei_contagem = 0;
                    }
                    denominador[i] = c;
                }
            }

            i++;
        }
    }

    system( "stty echo" );

    denominador[i] = '\0';

    f->numerador    = atoi(numerador);
    _denominador    = atoi(denominador);

    if(_denominador != 0)
    {
        f->denominador = _denominador;
    } else{
        f->denominador = 1;
    }

    memset(numerador,'\0',sizeof(numerador));
    memset(denominador,'\0',sizeof(denominador));

    return f;
}

void inversa(Fracao * f)
{
    if(f->numerador != 0)
    {
        int tmp = f->numerador;

        f->numerador = f->denominador;
        f->denominador = tmp;

        if(tmp < 0)
        {
            f->numerador *= -1;
            f->denominador *= -1;
        }

    } else{
        f->numerador = 0;
        f->denominador = 1;
    }
}

void desalocarMemoriaMemoriaFracao(int args, ...)
{
    va_list list;
    int i;

    va_start(list, args);

    for(i = 0; i < args; i++)
    {
        Fracao * fr = va_arg(list, Fracao *);
        free(fr);
        fr = NULL;

        //Fracao * f = va_arg(list, Fracao *);
        //printf("%d -> %d\n", f->numerador, f->denominador);
    }

    va_end(list);
}

void simplificarFracao(Fracao * f)
{
    int m_d_c = mdc(abs(f->numerador), abs(f->denominador));

    if(m_d_c != 1)
    {
        f->numerador = f->numerador / m_d_c;
        f->denominador = f->denominador / m_d_c;
    }
}


void imprimirFracao(Fracao * f)
{
    fflush(stdout);

	if(f->numerador == f->denominador)
	{
		printf("%5d\t", 1);
	}
	else if(f->denominador == 1)
	{
		printf("%5d\t", f->numerador);
	}
    else if(f->numerador == 0)
    {
        printf("%5d\t", 0);
    }
	else
	{
		printf("%5d/%d\t", f->numerador, f->denominador);
	}
}

int isZero(Fracao * f)
{
    return (f->numerador == 0) ? 1 : 0;
}
